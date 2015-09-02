//
//  GameViewController.swift
//  AiMubo
//
//  Created by Max Bilbow on 30/08/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

import Cocoa
import MetalKit

let MaxBuffers = 3
let ConstantBufferSize = 1024*1024

//let vertexData = ShapeData.cube()

let cube = ShapeData.cube()


let vertexColorData:[Float] =
[
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    
    0.0, 0.0, 1.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0,
    
    0.0, 0.0, 1.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0,
    
    0.0, 0.0, 1.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0,
    
    0.0, 0.0, 1.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0
]

class GameViewController: NSViewController, MTKViewDelegate {
    
    private static var _instance: GameViewController!
    static var instance: GameViewController {
        return _instance
    }

    
    let device: MTLDevice = MTLCreateSystemDefaultDevice()!
    
    var commandQueue: MTLCommandQueue! = nil
    var pipelineState: MTLRenderPipelineState! = nil
    var vertexBuffer: MTLBuffer! = nil
    var vertexColorBuffer: MTLBuffer! = nil
    var uniformsBuffers: [MTLBuffer] = []
//    var bufferProvider: BufferProvider!
    
    let inflightSemaphore = dispatch_semaphore_create(MaxBuffers)
    var bufferIndex = 0
    
    // offsets used in animation
    var xOffset:[Float] = [ -1.0, 1.0, -1.0 ]
    var yOffset:[Float] = [ 1.0, 0.0, -1.0 ]
    var xDelta:[Float] = [ 0.002, -0.001, 0.003 ]
    var yDelta:[Float] = [ 0.001,  0.002, -0.001 ]

    override func viewDidLoad() {
        GameViewController._instance = self
        CppBridge.setupScene()
        
        super.viewDidLoad()
        
        
        // setup view properties
        let view = self.view as! MTKView
        view.delegate = self
        view.device = device
        view.sampleCount = 4
        
        loadAssets()
    }
    
    func loadAssets() {
        
        // load any resources required for rendering
        let view = self.view as! MTKView
        commandQueue = device.newCommandQueue()
        commandQueue.label = "main command queue"
        
        let defaultLibrary = device.newDefaultLibrary()!
        let fragmentProgram = defaultLibrary.newFunctionWithName("basic_fragment")!
        let vertexProgram = defaultLibrary.newFunctionWithName("basic_vertex")!
        
        let pipelineStateDescriptor = MTLRenderPipelineDescriptor()
        pipelineStateDescriptor.vertexFunction = vertexProgram
        pipelineStateDescriptor.fragmentFunction = fragmentProgram
        pipelineStateDescriptor.colorAttachments[0].pixelFormat = view.colorPixelFormat
        pipelineStateDescriptor.sampleCount = view.sampleCount
        
        do {
            try pipelineState = device.newRenderPipelineStateWithDescriptor(pipelineStateDescriptor)
        } catch let error {
            print("Failed to create pipeline state, error \(error)")
        }
        
        // generate a large enough buffer to allow streaming vertices for 3 semaphore controlled frames
        vertexBuffer = device.newBufferWithLength(ConstantBufferSize, options: [])
        vertexBuffer.label = "vertices"
        
        let vertexColorSize = cubeDataSize//.count * sizeofValue(vertexData[0])
        vertexColorBuffer = device.newBufferWithBytes(vertexColorData, length: vertexColorSize, options: [])
        vertexColorBuffer.label = "colors"
        
        let geometries = CppBridge.geometries()
//        self.bufferProvider = BufferProvider(device: self.device, inflightBuffersCount: geometries.count, sizeOfUniformsBuffer: 32)
        
        for shape in geometries.shapeData {
            let uniformBufferSize = sizeof(Float) * 16
            let uniformBuffer = device.newBufferWithLength(uniformBufferSize, options: [])
            uniformBuffer.label = (shape as! ShapeData).uniqueName
            uniformsBuffers.append(uniformBuffer)
        }
        

    }
    
    func update() {
        
        // vData is pointer to the MTLBuffer's Float data contents
        let pData = vertexBuffer.contents()
        let vData = UnsafeMutablePointer<Float>(pData + 256*bufferIndex)
        
        // reset the vertices to default before adding animated offsets
        vData.initializeFrom(cube.vertexData, count: cube.count)// vertexData)
        
        // Animate triangle offsets
        let lastTriVertex = 24
        let vertexSize = 4
        for j in 0..<MaxBuffers {
            // update the animation offsets
            xOffset[j] += xDelta[j]
            
            if(xOffset[j] >= 1.0 || xOffset[j] <= -1.0) {
                xDelta[j] = -xDelta[j]
                xOffset[j] += xDelta[j]
            }
            
            yOffset[j] += yDelta[j]
            
            if(yOffset[j] >= 1.0 || yOffset[j] <= -1.0) {
                yDelta[j] = -yDelta[j]
                yOffset[j] += yDelta[j]
            }
            
            // Update last triangle position with updated animated offsets
            let pos = lastTriVertex + j*vertexSize
            vData[pos] = xOffset[j]
            vData[pos+1] = yOffset[j]
        }
    }
    
    var aspect: Float {
        return Float(self.view.bounds.size.width / self.view.bounds.size.height)
    }
//    struct Uniforms {
//        var pm: UnsafeMutablePointer<Float>
//        var mvm: UnsafeMutablePointer<Float>
//    }
   
    func drawInMTKView(view: MTKView) {
        CppBridge.updateSceneLogic()
        
//        RMXMobileInput.instance.update();
        // use semaphore to encode 3 frames ahead
        dispatch_semaphore_wait(inflightSemaphore, DISPATCH_TIME_FOREVER)
        
//        self.update()
        
        let commandBuffer = commandQueue.commandBuffer()
        commandBuffer.label = "Frame command buffer"
        
        guard let renderPassDescriptor = view.currentRenderPassDescriptor else {
            return
        }

        let renderEncoder = commandBuffer.renderCommandEncoderWithDescriptor(renderPassDescriptor)
        renderEncoder.label = "render encoder"
        

        let projectionMatrix = CppBridge.rawProjectionMatrixWithAspect(aspect)
        ///Load Geometries
        let geometries = CppBridge.geometries().shapeData;
        
        for shape in geometries {
            
            let vertexData = shape as! ShapeData
                if let uniformBuffer = uniformsBuffers.first {
            //            var uniforms = CppBridge.getUniformWithModelViewMatrix(vertexData.modelViewMatrix, withAspect: aspect)
                    let bufferPointer = uniformBuffer.contents()
                    // 4
                    memcpy(bufferPointer, vertexData.modelViewMatrixRaw, sizeof(Float)*16)
                    //            memcpy(bufferPointer!, &uniforms, sizeof(Float)*16*2)
                    memcpy(bufferPointer + sizeof(Float)*16, projectionMatrix, sizeof(Float)*16)
                    // 5
                    renderEncoder.setVertexBuffer(uniformBuffer, offset: 0, atIndex: 1)
                    //            return;
                    
                    renderEncoder.pushDebugGroup("draw \(shape.uniqueName)")
                    renderEncoder.setRenderPipelineState(pipelineState)
                    renderEncoder.setVertexBuffer(vertexBuffer, offset: 256*bufferIndex, atIndex: 0)
                    renderEncoder.setVertexBuffer(vertexColorBuffer, offset:3 , atIndex: 0)
                    renderEncoder.setVertexBuffer(uniformBuffer, offset: 0, atIndex: 1)
                    renderEncoder.drawPrimitives(.TriangleStrip, vertexStart: 0, vertexCount: vertexData.vertexCount, instanceCount: 1)
            
            }

        }

        
               renderEncoder.popDebugGroup()
        renderEncoder.endEncoding()
        
        // use completion handler to signal the semaphore when this frame is completed allowing the encoding of the next frame to proceed
        // use capture list to avoid any retain cycles if the command buffer gets retained anywhere besides this stack frame
        commandBuffer.addCompletedHandler{ [weak self] commandBuffer in
            if let strongSelf = self {
                dispatch_semaphore_signal(strongSelf.inflightSemaphore)
            }
            return
        }
        
        // bufferIndex matches the current semaphore controled frame index to ensure writing occurs at the correct region in the vertex buffer
        bufferIndex = (bufferIndex + 1) % MaxBuffers
        
        commandBuffer.presentDrawable(view.currentDrawable!)
        commandBuffer.commit()
    }
    
   
    
    func mtkView(view: MTKView, drawableSizeWillChange size: CGSize) {
        
    }
    
    override func keyDown(theEvent: NSEvent) {
        NSLog(theEvent.description)
    }
    
    
    let mvSpeed:Float = 1;
    override func keyUp(theEvent: NSEvent) {
        if let key = theEvent.characters {
            switch key {
            case "w":
                CppBridge.moveWithDirection("forward", withForce: mvSpeed)
                break
            case "s":
                CppBridge.moveWithDirection("forward", withForce: -mvSpeed)
                break
            case "a":
                CppBridge.moveWithDirection("left", withForce: mvSpeed)
                break
            case "d":
                CppBridge.moveWithDirection("left", withForce: -mvSpeed)
                break
            case "e":
                CppBridge.moveWithDirection("up", withForce: mvSpeed)
                break
            case "q":
                CppBridge.moveWithDirection("up", withForce: -mvSpeed)
                break
            default:
                break;
            }
        }
        NSLog("\(theEvent.characters)")
    }
}

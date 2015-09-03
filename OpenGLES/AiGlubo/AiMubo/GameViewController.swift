//
//  GameViewController.swift
//  AiMubo
//
//  Created by Max Bilbow on 30/08/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#if iOS
    import UIKit
    typealias ViewController = UIViewController
    typealias NSEvent = UIEvent
    typealias uint16 = UInt16
    #else
import Cocoa
    typealias ViewController = NSViewController
    #endif
import Metal
import MetalKit

let MaxBuffers = 2
let ConstantBufferSize = 1024*1024

//let vertexData = ShapeData.cube()

//let cube = ShapeData.cube()

class GameViewController: ViewController, MTKViewDelegate {
    
    var window: NSWindow! {
        return self.view.window
    }
    
    private static var _instance: GameViewController!
    static var instance: GameViewController {
        return _instance
    }

    
    let device: MTLDevice = MTLCreateSystemDefaultDevice()!
    
    var commandQueue: MTLCommandQueue! = nil
    var pipelineState: MTLRenderPipelineState! = nil
    var vertexBuffer: MTLBuffer! = nil
    var indexBuffer: MTLBuffer! = nil
    var uniformsBuffer: MTLBuffer!// = []
//    var bufferProvider: BufferProvider!
    
    let inflightSemaphore = dispatch_semaphore_create(MaxBuffers)
//    var bufferIndex = 0
    
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
//        let size = sizeof(Int32) * 6 * 3 * 6 
        vertexBuffer = device.newBufferWithLength(ConstantBufferSize, options: [])
        vertexBuffer.label = "vertices"

        let uniformBufferSize = sizeof(Float) * (16 + 16 + 3 + 4)
        self.uniformsBuffer = device.newBufferWithLength(uniformBufferSize, options: [])
        uniformsBuffer.label = "uniforms"
        
        let indexBufferSize = sizeof(Int32) * 6 * 6
        self.indexBuffer = device.newBufferWithLength(indexBufferSize, options: [])
        indexBuffer.label = "indicies"
        
      

    }
    
    
    var aspect: Float {
        return Float(self.view.bounds.size.width / self.view.bounds.size.height)
    }

   
    func drawInMTKView(view: MTKView) {
        CppBridge.updateSceneLogic()
        
//        RMXMobileInput.instance.update();
        // use semaphore to encode 3 frames ahead
        dispatch_semaphore_wait(inflightSemaphore, DISPATCH_TIME_FOREVER)
        

        
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
            
        if let vertexData = shape as? ShapeData {
//            let pData = vertexBuffer.contents()
//            let vData = UnsafeMutablePointer<Float>(pData)// + 256*bufferIndex)
//        
//        // reset the vertices to default before adding animated offsets
//            vData.initializeFrom(shape.vertexData, count: shape.vertexDataSize)
//            
        vertexBuffer.contents().initializeFrom(shape.vertexData, count: shape.vertexDataSize)

            indexBuffer.contents().initializeFrom(shape.indexData, count: shape.indexDataSize)
            let iData = UnsafeMutablePointer<uint16>(indexBuffer.contents())
        
            iData.initializeFrom(shape.indexData, count: shape.indexDataSize)
            let bufferPointer = uniformsBuffer.contents()
            // 4
            memcpy(bufferPointer, vertexData.modelMatrixRaw, sizeof(Float32)*16)
            //            memcpy(bufferPointer!, &uniforms, sizeof(Float)*16*2)
            memcpy(bufferPointer + sizeof(Float32)*16, projectionMatrix, sizeof(Float32)*16)
        
            memcpy(bufferPointer + sizeof(Float32)*35, vertexData.scaleVectorRaw, sizeof(Float32)*16)
            // 5
            memcpy(bufferPointer + sizeof(Float32)*39, vertexData.colorVectorRaw, sizeof(Float32)*16)
        
            renderEncoder.setVertexBuffer(uniformsBuffer, offset: 0, atIndex: 1)
            //            return;
            
            renderEncoder.pushDebugGroup("draw \(shape.uniqueName)")
            renderEncoder.setRenderPipelineState(pipelineState)
            renderEncoder.setVertexBuffer(vertexBuffer, offset: 0, atIndex: 0)// 256*bufferIndex, atIndex: 0)
//            renderEncoder.setVertexBuffer(indexBuffer, offset: 0, atIndex: 0)
            renderEncoder.setVertexBuffer(uniformsBuffer, offset: 0, atIndex: 1)
            renderEncoder.drawIndexedPrimitives(.Triangle, indexCount: vertexData.indexDataSize, indexType: MTLIndexType.UInt16, indexBuffer: indexBuffer, indexBufferOffset: 0)
//                    renderEncoder.drawPrimitives(.Triangle, vertexStart: 0, vertexCount: vertexData.vertexDataSize, instanceCount: 1)
            
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
//        bufferIndex = (bufferIndex + 1) % MaxBuffers
        
        commandBuffer.presentDrawable(view.currentDrawable!)
        commandBuffer.commit()
    }
    
   
    
    func mtkView(view: MTKView, drawableSizeWillChange size: CGSize) {
        
    }
    

    #if !iOS
    
    override func keyDown(theEvent: NSEvent) {
        print(theEvent)
    }
    
    
    let mvSpeed:Float = 1;
    override func keyUp(theEvent: NSEvent) {
        print(theEvent)
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
    
  
    override func mouseMoved(theEvent: NSEvent) {
        
        let dx:Float = Float(theEvent.deltaX)
        let dy:Float = Float(theEvent.deltaY)
        print("\(dx), \(dy)")
        CppBridge.turnAboutAxis(UserAction.MOVE_PITCH.description, withForce: dy)
        CppBridge.turnAboutAxis(UserAction.MOVE_YAW.description, withForce: dx)
    }
    
    override func mouseDragged(theEvent: NSEvent) {
        let dx:Float = Float(theEvent.deltaX)
        let dy:Float = Float(theEvent.deltaY)
        print("\(dx), \(dy)")
        CppBridge.turnAboutAxis(UserAction.MOVE_PITCH.description, withForce: dy)
        CppBridge.turnAboutAxis(UserAction.MOVE_YAW.description, withForce: dx)
    }
    override func mouseDown(theEvent: NSEvent) {
        print(theEvent)
    }
    
    #endif
}

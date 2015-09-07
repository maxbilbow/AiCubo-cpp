//
//  GameViewController.swift
//  ShaderFun
//
//  Created by Max Bilbow on 07/09/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

import Cocoa
import MetalKit
import GLKit

let MaxBuffers = 3
let ConstantBufferSize = 1024*1024

var modelMatrix: GLKMatrix4 = GLKMatrix4Identity
let scaleVector = GLKVector3Make(1,1,1)

let vertexData:[Float] =
[

    //Front
    -1.0, -1.0, 1.0, 1.0,
    1.0, -1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0,
    -1.0, 1.0, 1.0, 1.0,
    
    //back
    1.0, 1.0, -1.0, 1.0,
    1.0, -1.0, -1.0, 1.0,
    -1.0, -1.0, -1.0, 1.0,
    -1.0, 1.0, -1.0, 1.0,
    
    //bottom
    -1.0, -1.0, -1.0, 1.0,
    1.0, -1.0, -1.0, 1.0,
    1.0, -1.0, 1.0, 1.0,
    -1.0, -1.0, 1.0, 1.0,

    //Top
    1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, -1.0, 1.0,
    -1.0, 1.0, -1.0, 1.0,
    -1.0, 1.0, 1.0, 1.0,
    
    //right
    1.0, -1.0,-1.0, 1.0,
    1.0, 1.0, -1.0, 1.0,
    1.0, 1.0, 1.0, 1.0,
    1.0, -1.0, 1.0, 1.0,
    
    //left
    -1.0, 1.0, 1.0, 1.0,
    -1.0, 1.0, -1.0, 1.0,
    -1.0, -1.0, -1.0, 1.0,
    -1.0, -1.0, 1.0, 1.0,

   

]
let A:UInt16 =  0, B:UInt16 =  1, C:UInt16 =  2, D:UInt16 =  3
let E:UInt16 =  4, F:UInt16 =  5, G:UInt16 =  6, H:UInt16 =  7
let I:UInt16 =  8, J:UInt16 =  9, K:UInt16 = 10, L:UInt16 = 11
let M:UInt16 = 12, N:UInt16 = 13, O:UInt16 = 14, P:UInt16 = 15
let Q:UInt16 = 16, R:UInt16 = 17, S:UInt16 = 18, T:UInt16 = 19
let U:UInt16 = 20, V:UInt16 = 21, W:UInt16 = 22, X:UInt16 = 23


let indices: [UInt16] = [
    A,B,C, A,C,D,
    E,F,G, E,G,H,
    I,J,K, I,K,L,
    M,N,O, M,O,P,
    Q,R,S, Q,S,T,
    U,V,W, U,W,X
    
]

let txtCoords: [Float] = [
    //Front
    -1.0, -1.0,
    1.0, -1.0,
    1.0, 1.0,
    -1.0, 1.0,
    
    //back
    1.0, 1.0,
    1.0, -1.0,
    -1.0, -1.0,
    -1.0, 1.0,
    
    //bottom
    -1.0, -1.0,
    1.0, -1.0,
    1.0, -1.0,
    -1.0, -1.0,
    
    //Top
    1.0, 1.0,
    1.0, 1.0,
    -1.0, 1.0,
    -1.0, 1.0,
    
    //right
    1.0, -1.0,
    1.0, 1.0,
    1.0, 1.0,
    1.0, -1.0,
    
    //left
    -1.0, 1.0,
    -1.0, 1.0,
    -1.0, -1.0,
    -1.0, -1.0,
]
//let indices: [uint16] = [
//    0,1,2,0,2,3, //Front
//    4,5,6,4,6,7, //Back
//    8,9,10,8,10,11, //top
//    12,13,14,12,14,15, //bottom
//    16,17,18,16,18,19, //right
//    20,21,22,20,22,23 //left
//]
let vertexColorData:[Float] =
[
//    0.0, 0.0, 1.0, 1.0,
//    0.0, 0.0, 1.0, 1.0,
//    0.0, 0.0, 1.0, 1.0,
//
//    0.0, 0.0, 1.0, 1.0,
//    0.0, 0.0, 1.0, 1.0,
//    0.0, 0.0, 1.0, 1.0,
    
    0.0, 0.0, 1.0, 1.0, //Front
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    
    0.0, 1.0, 0.0, 1.0, //Back
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    
    1.0, 0.0, 0.0, 1.0, //Top
    1.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0,
    
    1.0, 1.0, 0.0, 1.0, //Bottom
    1.0, 1.0, 0.0, 1.0,
    1.0, 1.0, 0.0, 1.0,
    1.0, 1.0, 0.0, 1.0,
    
    0.0, 1.0, 1.0, 1.0, //right
    0.0, 1.0, 1.0, 1.0,
    0.0, 1.0, 1.0, 1.0,
    0.0, 1.0, 1.0, 1.0,
    
    1.0, 0.0, 1.0, 1.0, //left
    1.0, 0.0, 1.0, 1.0,
    1.0, 0.0, 1.0, 1.0,
    1.0, 0.0, 1.0, 1.0,
    
//    0.0, 1.0, 1.0, 1.0,
//    0.2, 0.2, 0.2, 1.0
//    0.0, 1.0, 0.0, 1.0
]



class GameViewController: NSViewController, MTKViewDelegate, NSGestureRecognizerDelegate {
    
    let device: MTLDevice = MTLCreateSystemDefaultDevice()!
    let startTime = Float(NSTimeIntervalSince1970)
    var commandQueue: MTLCommandQueue! = nil
    var pipelineState: MTLRenderPipelineState! = nil
    var vertexBuffer: MTLBuffer! = nil
    var vertexColorBuffer: MTLBuffer! = nil
    var indexBuffer: MTLBuffer! = nil
    var uniformBuffer: MTLBuffer! = nil
    var textureBuffer: MTLBuffer! = nil
    var uniforms: Uniform! = nil
//    var viewPort: MTLViewport! = nil
    let inflightSemaphore = dispatch_semaphore_create(MaxBuffers)
    var bufferIndex = 0

    private static var _instance: GameViewController!
    
    static var instance: GameViewController {
        return _instance
    }
    
    
    // offsets used in animation
    var xOffset:[Float] = [ -1.0, 1.0, -1.0 ]
    var yOffset:[Float] = [ 1.0, 0.0, -1.0 ]
    var xDelta:[Float] = [ 0.002, -0.001, 0.003 ]
    var yDelta:[Float] = [ 0.001,  0.002, -0.001 ]

    override func viewDidLoad() {
        GameViewController._instance = self
        if mode == .Engine {
            CppBridge.setupScene()
        }
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
        let fragmentProgram = defaultLibrary.newFunctionWithName("passThroughFragment")!
        let vertexProgram = defaultLibrary.newFunctionWithName("passThroughVertex")!
        
        let pipelineStateDescriptor = MTLRenderPipelineDescriptor()
        pipelineStateDescriptor.vertexFunction = vertexProgram
        pipelineStateDescriptor.fragmentFunction = fragmentProgram
        pipelineStateDescriptor.colorAttachments[0].pixelFormat = view.colorPixelFormat
        pipelineStateDescriptor.sampleCount = view.sampleCount
//        pipelineStateDescriptor.depthAttachmentPixelFormat = .Depth24Unorm_Stencil8
        
        do {
            try pipelineState = device.newRenderPipelineStateWithDescriptor(pipelineStateDescriptor)
        } catch let error {
            print("Failed to create pipeline state, error \(error)")
        }
        
        // generate a large enough buffer to allow streaming vertices for 3 semaphore controlled frames
        vertexBuffer = device.newBufferWithLength(ConstantBufferSize, options: [])
        vertexBuffer.label = "vertices"
        
        let vertexColorSize = vertexData.count * sizeofValue(vertexColorData[0])
        vertexColorBuffer = device.newBufferWithBytes(vertexColorData, length: vertexColorSize, options: [])
        vertexColorBuffer.label = "colors"
        
        let indexSize = indices.count * sizeofValue(indices[0])
        indexBuffer = device.newBufferWithBytes(indices, length: indexSize, options: [])
        
        let texSize = txtCoords.count * sizeofValue(txtCoords[0])
        textureBuffer = device.newBufferWithBytes(txtCoords, length: texSize, options: [])
        loadUniforms()
//        texture = MetalTexture(resourceName: "cube", ext: "png", mipmaped: true)
//        texture.loadTexture(device: device, commandQ: commandQ, flip: true)
        
    }
    var instances: [Uniform] = [
        Uniform(keys: ("modelMatrix",16), ("scale",3)),
        Uniform(keys: ("modelMatrix",16), ("scale",3)),
        Uniform(keys: ("modelMatrix",16), ("scale",3)),
        Uniform(keys: ("modelMatrix",16), ("scale",3))
    ]
    var instanceBuffer: MTLBuffer!
    func loadUniforms() {
        
        uniforms = Uniform(width: Float(view.bounds.width), height: Float(view.bounds.height),
            vars: ("time",1))
        
        uniforms.setView(matrix: viewMatrix)
//        uniforms.setValue(forKey: "scale", array: [1,1,1])
        print("Uniforms:")
        print(uniforms.print)
        uniformBuffer = device.newBufferWithBytes(uniforms.bytes, length: uniforms.size, options: [])

        var size:Int = 0
        var x:Float = 0, y:Float = 0, z:Float = 0
        for var i = 0; i<instances.count; ++i {
            instances[i].setValue(forKey: "scale", vector3: GLKVector3Make(1,1,1))
            instances[i].setValue(forKey: "modelMatrix", matrix4: GLKMatrix4Identity * GLKMatrix4MakeTranslation(x, y, z))
            z += 4; y += 4
            size += instances[i].size
            
        }
        instanceBuffer = device.newBufferWithLength(size, options: [])
    }
    
    
    func update() {
        
        // vData is pointer to the MTLBuffer's Float data contents
        let pData = vertexBuffer.contents()
        let vData = UnsafeMutablePointer<Float>(pData + 256*bufferIndex)
        
        // reset the vertices to default before adding animated offsets
        vData.initializeFrom(vertexData)
        
    }
    
    func drawInMTKView(view: MTKView) {
        
        // use semaphore to encode 3 frames ahead
        dispatch_semaphore_wait(inflightSemaphore, DISPATCH_TIME_FOREVER)
        
       
        self.update()
        
        let commandBuffer = commandQueue.commandBuffer()
        commandBuffer.label = "Frame command buffer"
        
        guard let renderPassDescriptor = view.currentRenderPassDescriptor else {
            return
        }

       
       
        
        
        
        
        uniforms.setValue(forKey: "time", value: uniforms.getValue("time")! + 0.01)
        if mode == .Engine {
            CppBridge.updateSceneLogic()
            uniforms.setView(matrix: CppBridge.viewMatrix())
        }
//        let geometries = CppBridge.geometries()
//        for shape in geometries.shapeData {
            let renderEncoder = commandBuffer.renderCommandEncoderWithDescriptor(renderPassDescriptor)
            renderEncoder.label = "render encoder"
            renderEncoder.setCullMode(MTLCullMode.Front)
        
        let uPointer = uniformBuffer.contents()
        memcpy(uPointer, uniforms.bytes, uniforms.size)
        renderEncoder.setVertexBuffer(uniformBuffer, offset: 0, atIndex: 2)

        
        var bytes: [Float] = []
        for var i = 0;i<instances.count; ++i{
            bytes += instances[i].bytes
        }
        let iPointer = instanceBuffer.contents()
        memcpy(iPointer, bytes, instances.count * instances[0].size)
        
        renderEncoder.setVertexBuffer(instanceBuffer, offset: 0, atIndex: 3)
        
        renderEncoder.pushDebugGroup("draw morphing triangle")
        renderEncoder.setRenderPipelineState(pipelineState)
        renderEncoder.setVertexBuffer(vertexBuffer, offset: 256*bufferIndex, atIndex: 0)
        renderEncoder.setVertexBuffer(vertexColorBuffer, offset:0 , atIndex: 1)
        
        
//        renderEncoder.drawPrimitives(.Triangle, vertexStart: 0, vertexCount: 9, instanceCount: 1)
        renderEncoder.drawIndexedPrimitives(.Triangle, indexCount: indices.count, indexType: MTLIndexType.UInt16, indexBuffer: indexBuffer, indexBufferOffset: 0, instanceCount: instances.count)
        
        renderEncoder.popDebugGroup()
        renderEncoder.endEncoding()
//        }
        
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
        projection = GLKMatrix4MakePerspective(45, Float(view.bounds.width/view.bounds.height), 0.01, 1000)
        uniforms.setProjection(matrix: projection)
    }
    
    override func keyDown(theEvent: NSEvent) {
        print(theEvent)
        switch mode {
        case .Test:
            return
        case .Engine:
            return
        }
    }
    override func keyUp(theEvent: NSEvent) {
        print(theEvent)
    }
    
    
    override func mouseDragged(event: NSEvent) {
        switch mode {
        case .Test:
            let rx = GLKMatrix4MakeRotation(Float(event.deltaY * PI_OVER_180), 1, 0, 0)
            let ry = GLKMatrix4MakeRotation(Float(event.deltaX * PI_OVER_180), 0, 1, 0)
            modelMatrix *= rx
            modelMatrix *= ry
//            viewMatrix = GLKMatrix4RotateX(viewMatrix, Float(theEvent.deltaY) * PI_OVER_180f)
//            viewMatrix = GLKMatrix4RotateY(viewMatrix, Float(theEvent.deltaX) * PI_OVER_180f)
            instances[0].setModel(matrix: modelMatrix)
            return
        case .Engine:
            return
        }
        
        
    }
    var viewMatrix = GLKMatrix4MakeTranslation(0, 0, -4)
    var projection = GLKMatrix4Identity
    override func magnifyWithEvent(event: NSEvent) {
        switch mode {
        case .Test:
            let translation = GLKMatrix4MakeTranslation(0, 0, Float(event.magnification))
            self.viewMatrix *= translation
            uniforms.setView(matrix: viewMatrix)
            return
        case .Engine:
            CppBridge.sendMessage("forward", withScale: Float(event.magnification))
            return
        }

    }
    
    override func rotateWithEvent(event: NSEvent) {
        switch mode {
        case .Test:
            let rz = GLKMatrix4MakeRotation(event.rotation * PI_OVER_180f,0,0,1)
            modelMatrix *= rz
            instances[0].setModel(matrix: modelMatrix)
            return
        case .Engine:
            CppBridge.turnAboutAxis("roll", withForce: event.rotation * PI_OVER_180f)
            return
        }
    }
    let mode = Mode.Test
    enum Mode {
        case Test, Engine
    }
    
    
    override func scrollWheel(event: NSEvent) {
        switch mode {
        case .Test:
            let rx = GLKMatrix4MakeRotation(Float(event.deltaY * PI_OVER_180), 1, 0, 0)
            let ry = GLKMatrix4MakeRotation(Float(event.deltaX * PI_OVER_180), 0, 1, 0)
            viewMatrix *= rx
            viewMatrix *= ry
            uniforms.setView(matrix: viewMatrix)
//            instance.setValue(forKey: "modelMatrix", matrix4: modelMatrix)
            return
        case .Engine:
            CppBridge.turnAboutAxis("pitch", withForce: -Float(event.deltaY))
            CppBridge.turnAboutAxis("yaw", withForce: -Float(event.deltaX) * PI_OVER_180f)
            return
        }

     
    }
    
    
}

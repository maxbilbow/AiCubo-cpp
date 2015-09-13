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

let MaxBuffers = 4
//let ConstantBufferSize = 1024*1024

let scaleVector = GLKVector3Make(1,1,1)

//let vertexData:[Float] =
//[
//
//    //Front
//    -1.0, -1.0, 1.0, 1.0,
//    1.0, -1.0, 1.0, 1.0,
//    1.0, 1.0, 1.0, 1.0,
//    -1.0, 1.0, 1.0, 1.0,
//    
//    //back
//    1.0, 1.0, -1.0, 1.0,
//    1.0, -1.0, -1.0, 1.0,
//    -1.0, -1.0, -1.0, 1.0,
//    -1.0, 1.0, -1.0, 1.0,
//    
//    //bottom
//    -1.0, -1.0, -1.0, 1.0,
//    1.0, -1.0, -1.0, 1.0,
//    1.0, -1.0, 1.0, 1.0,
//    -1.0, -1.0, 1.0, 1.0,
//
//    //Top
//    1.0, 1.0, 1.0, 1.0,
//    1.0, 1.0, -1.0, 1.0,
//    -1.0, 1.0, -1.0, 1.0,
//    -1.0, 1.0, 1.0, 1.0,
//    
//    //right
//    1.0, -1.0,-1.0, 1.0,
//    1.0, 1.0, -1.0, 1.0,
//    1.0, 1.0, 1.0, 1.0,
//    1.0, -1.0, 1.0, 1.0,
//    
//    //left
//    -1.0, 1.0, 1.0, 1.0,
//    -1.0, 1.0, -1.0, 1.0,
//    -1.0, -1.0, -1.0, 1.0,
//    -1.0, -1.0, 1.0, 1.0,
//
//   
//
//]
//let A:UInt16 =  0, B:UInt16 =  1, C:UInt16 =  2, D:UInt16 =  3 //Front
//let E:UInt16 =  4, F:UInt16 =  5, G:UInt16 =  6, H:UInt16 =  7 //Back
//let I:UInt16 =  8, J:UInt16 =  9, K:UInt16 = 10, L:UInt16 = 11 //Bottom
//let M:UInt16 = 12, N:UInt16 = 13, O:UInt16 = 14, P:UInt16 = 15 //Top
//let Q:UInt16 = 16, R:UInt16 = 17, S:UInt16 = 18, T:UInt16 = 19 //Right
//let U:UInt16 = 20, V:UInt16 = 21, W:UInt16 = 22, X:UInt16 = 23 //Left
//
//
//let indices: [UInt16] = [
//    A,B,C, A,C,D,
//    E,F,G, E,G,H,
//    I,J,K, I,K,L,
//    M,N,O, M,O,P,
//    Q,R,S, Q,S,T,
//    U,V,W, U,W,X
//    
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
    1.0, 0.0, 1.0, 1.0
    
//    0.0, 1.0, 1.0, 1.0,
//    0.2, 0.2, 0.2, 1.0
//    0.0, 1.0, 0.0, 1.0
]



class GameViewController: NSViewController, MTKViewDelegate, NSGestureRecognizerDelegate {
    
//    var metalLayer: CAMetalLayer!
    let device: MTLDevice = MTLCreateSystemDefaultDevice()!
    let startTime = Float(NSTimeIntervalSince1970)
    var commandQueue: MTLCommandQueue! = nil
    var pipelineState: MTLRenderPipelineState! = nil
    var depthStencilState: MTLDepthStencilState! = nil
    var colorTex: MTLTexture!
    var depthTex: MTLTexture!
    var samplerState: MTLSamplerState!
    var vertexBuffer: MTLBuffer! = nil
    var vertexColorBuffer: MTLBuffer! = nil
    var vertexNormalBuffer: MTLBuffer! = nil
    var indexBuffer: MTLBuffer! = nil
    var uniformBuffer: MTLBuffer! = nil
//    var textureBuffer: MTLBuffer! = nil
    var uniforms: Uniform! = nil

    let inflightSemaphore = dispatch_semaphore_create(MaxBuffers)

    private static var _instance: GameViewController!
    
    static var instance: GameViewController {
        return _instance
    }

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

    lazy var cube = ShapeData.cube()

//    var sampler: MTLSamplerState! = nil
//    var rendPassDesc: MTLRenderPassDescriptor!
    
    
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
        pipelineStateDescriptor.colorAttachments[0].blendingEnabled = true
        pipelineStateDescriptor.sampleCount = view.sampleCount
//        pipelineStateDescriptor.colorAttachments[0].pixelFormat = MTLPixelFormat.BGRA8Unorm;
        pipelineStateDescriptor.depthAttachmentPixelFormat = .Depth32Float

       
        
        do {
            try pipelineState = device.newRenderPipelineStateWithDescriptor(pipelineStateDescriptor)
        } catch let error {
            print("Failed to create pipeline state, error \(error)")
        }
        
        
        
        let depthStencilStateDescriptor = MTLDepthStencilDescriptor()
        depthStencilStateDescriptor.depthCompareFunction = MTLCompareFunction.Less
        depthStencilStateDescriptor.depthWriteEnabled = true
        depthStencilStateDescriptor.frontFaceStencil.stencilCompareFunction = .Equal
        depthStencilStateDescriptor.frontFaceStencil.stencilFailureOperation = .Keep
        depthStencilStateDescriptor.frontFaceStencil.depthFailureOperation = .IncrementClamp
        depthStencilStateDescriptor.frontFaceStencil.depthStencilPassOperation = .IncrementClamp
        depthStencilStateDescriptor.frontFaceStencil.readMask = 0x1
        depthStencilStateDescriptor.frontFaceStencil.writeMask = 0x1
        depthStencilStateDescriptor.backFaceStencil = nil
        depthStencilState = device.newDepthStencilStateWithDescriptor(depthStencilStateDescriptor)
        
        
        
        

    
        let samplerDescriptor = MTLSamplerDescriptor()
        samplerDescriptor.minFilter = .Nearest;
        samplerDescriptor.magFilter = .Linear;
        samplerDescriptor.sAddressMode = .Repeat;
        samplerDescriptor.tAddressMode = .Repeat;
//        samplerDescriptor.rAddressMode = MTLSamplerAddressMode.ClampToEdge
//        samplerDescriptor.normalizedCoordinates = true
//        samplerDescriptor.lodMinClamp           = 0
//        samplerDescriptor.lodMaxClamp           = FLT_MAX
        samplerState = device.newSamplerStateWithDescriptor(samplerDescriptor)
      
        let size = view.window!.screen!.frame.size
        let colorTexDesc = MTLTextureDescriptor.texture2DDescriptorWithPixelFormat(.RGBA8Unorm,
            width: Int(size.width), height: Int(size.height), mipmapped: false)
        colorTexDesc.resourceOptions = .StorageModePrivate
        colorTex = device.newTextureWithDescriptor(colorTexDesc)
        
        let depthTexDesc = MTLTextureDescriptor.texture2DDescriptorWithPixelFormat(.Depth32Float,
            width: Int(size.width), height: Int(size.height), mipmapped: false)
        depthTexDesc.resourceOptions = .StorageModePrivate
        depthTex = device.newTextureWithDescriptor(depthTexDesc)
        
        // generate a large enough buffer to allow streaming vertices for 3 semaphore controlled frames
        vertexBuffer = device.newBufferWithLength(cube.vertexDataSize * sizeofValue(cube.vertexData[0]), options: [])
        vertexBuffer.label = "vertices"
        
        let vertexColorSize = vertexColorData.count * sizeofValue(vertexColorData[0])
        vertexColorBuffer = device.newBufferWithBytes(vertexColorData, length: vertexColorSize, options: [])
        vertexColorBuffer.label = "colors"
        
        let vertexNormalSize = cube.normalDataSize * sizeofValue(cube.normalData[0])
        vertexNormalBuffer = device.newBufferWithBytes(cube.normalData, length: vertexNormalSize, options: [])
        vertexNormalBuffer.label = "normals"
        
        let indexSize = cube.indexDataSize * sizeofValue(cube.indexData[0])
        indexBuffer = device.newBufferWithBytes(cube.indexData, length: indexSize, options: [])
        indexBuffer.label = "indexData"
        
        loadUniforms()
//        texture = MetalTexture(resourceName: "cube", ext: "png", mipmaped: true)
//        texture.loadTexture(device: device, commandQ: commandQ, flip: true)
        
    }
    var instances: Instances!// = Instances(count: 4)
    var instanceBuffer: MTLBuffer!
    func loadUniforms() {
        
        uniforms = Uniform(width: Float(view.bounds.width), height: Float(view.bounds.height),
            vars: ("time",1))
        
        uniforms.setView(matrix: CppBridge.viewMatrix(), invert: true)

//        print("Uniforms:")
//        print(uniforms.print)
        uniformBuffer = device.newBufferWithBytes(uniforms.bytes, length: uniforms.size, options: [])
        
        let shapes = CppBridge.geometries().shapeData
        
        instances = Instances(count: shapes.count)
        var size:Int = 0
        for var i = 0; i<instances.count; ++i {
            size += instances[i].size
        }
        instanceBuffer = device.newBufferWithLength(size, options: [])
    }
    
    //1
//    override func viewDidLayout() {
//        super.viewDidLayout()
//        if let _ = view.window {
//            let scale:CGFloat = 1// newScale//window.screen.nativeScale
//            let layerSize = view.bounds.size
//            //2
////            (view as? MTKView)?.colorPixelFormat = scale
//            metalLayer.frame = CGRectMake(0, 0, layerSize.width, layerSize.height)
//            metalLayer.drawableSize = CGSizeMake(layerSize.width * scale, layerSize.height * scale)
//        }
//    }
    
    
    func createRenderPass(ColorAttachmentTexture texture: MTLTexture?, view: MTKView)-> MTLRenderPassDescriptor? {

        guard let renderPassDesc = view.currentRenderPassDescriptor else {
            return nil
        }
        
        renderPassDesc.colorAttachments[0].texture = texture;
        renderPassDesc.colorAttachments[0].loadAction = MTLLoadAction.Clear
        renderPassDesc.colorAttachments[0].storeAction = MTLStoreAction.MultisampleResolve
        renderPassDesc.colorAttachments[0].clearColor = MTLClearColorMake(0.6,0.6,1.0,1.0)
        
        renderPassDesc.depthAttachment.texture = depthTex;
        renderPassDesc.depthAttachment.loadAction = MTLLoadAction.Clear
        renderPassDesc.depthAttachment.storeAction = MTLStoreAction.Store;
        renderPassDesc.depthAttachment.clearDepth = 1.0
        
    
        return renderPassDesc;
    }
    
    func drawInMTKView(view: MTKView) {
        //update logic and viewProjection
        uniforms.setValue(forKey: "time", value: uniforms.getValue("time")! + 0.01)
        CppBridge.updateSceneLogic()
        uniforms.setView(matrix: CppBridge.viewMatrix(), invert: false)
        
        
        
        // use semaphore to encode 3 frames ahead
        dispatch_semaphore_wait(inflightSemaphore, DISPATCH_TIME_FOREVER)
        
       

        let pData = vertexBuffer.contents()
        memcpy(pData, cube.vertexData, cube.vertexDataSize * sizeofValue(cube.vertexData[0]))
        
        
        let commandBuffer = commandQueue.commandBuffer()
        commandBuffer.label = "Frame command buffer"
        
        guard let renderPassDesc = createRenderPass(ColorAttachmentTexture: colorTex, view: view) else {
            return
        }
        
        let renderEncoder = commandBuffer.renderCommandEncoderWithDescriptor(renderPassDesc)
        renderEncoder.label = "render encoder"
        renderEncoder.pushDebugGroup("draw scene")
        renderEncoder.setRenderPipelineState(pipelineState)
        renderEncoder.setDepthStencilState(depthStencilState)
        renderEncoder.setFragmentSamplerState(samplerState, atIndex: 0)
        
//        renderEncoder.setFragmentTexture(depthTex, atIndex: 0)
//        renderEncoder.setFragmentTexture(colorTex, atIndex: 0)
        renderEncoder.setStencilReferenceValue(0xFF)
//        renderEncoder.setDepthClipMode(.Clamp)
        
        renderEncoder.setCullMode(MTLCullMode.Back)
        renderEncoder.setFrontFacingWinding(MTLWinding.CounterClockwise)


       
        

        //instance uniforms
        let iPointer = instanceBuffer.contents()
        let shapes = CppBridge.geometries().shapeData
        for var i = 0;i<instances.count; ++i{
            instances[i].setModel(matrix: (shapes.objectAtIndex(i) as? ShapeData)!.modelMatrix)
            instances[i].setScale(scale: (shapes.objectAtIndex(i) as? ShapeData)!.scaleVector)
            instances[i].setColor(color: (shapes.objectAtIndex(i) as? ShapeData)!.color)
            memcpy(iPointer + instances[i].size * i, instances[i].bytes, instances[i].size)
        }
        renderEncoder.setVertexBuffer(instanceBuffer, offset: 0, atIndex: 3)
        
        //shared uniforms
        let uPointer = uniformBuffer.contents()
        memcpy(uPointer, uniforms.bytes, uniforms.size)
        renderEncoder.setVertexBuffer(uniformBuffer, offset: 0, atIndex: 2)
        
        //vertex data
        renderEncoder.setVertexBuffer(vertexBuffer, offset: 0, atIndex: 0)
//        renderEncoder.setVertexBuffer(vertexColorBuffer, offset:0 , atIndex: 1)
        renderEncoder.setVertexBuffer(vertexNormalBuffer, offset:0 , atIndex: 1)
        renderEncoder.drawIndexedPrimitives(.Triangle,
            indexCount: cube.indexDataSize,
            indexType: MTLIndexType.UInt16,
            indexBuffer: indexBuffer,
            indexBufferOffset: 0,
            instanceCount: instances.count)
        
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
//        bufferIndex = (bufferIndex + 1) % MaxBuffers
        
        commandBuffer.presentDrawable(view.currentDrawable!)
        commandBuffer.commit()
    }
    
//    var viewMatrix = GLKMatrix4MakeTranslation(0, 0, -4)
    var projection = GLKMatrix4Identity
    func mtkView(view: MTKView, drawableSizeWillChange size: CGSize) {
        projection = GLKMatrix4MakePerspective(45, Float(view.bounds.width/view.bounds.height), 0.01, 2000)
        uniforms.setProjection(matrix: projection)
    }
    
    
    
    
    
    
    
    
    
}

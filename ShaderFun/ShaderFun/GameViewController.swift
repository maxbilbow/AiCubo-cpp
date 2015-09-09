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
    
    let device: MTLDevice = MTLCreateSystemDefaultDevice()!
    let startTime = Float(NSTimeIntervalSince1970)
    var commandQueue: MTLCommandQueue! = nil
    var pipelineState: MTLRenderPipelineState! = nil
    var depthStencilState: MTLDepthStencilState! = nil
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
        
       
        
        do {
            try pipelineState = device.newRenderPipelineStateWithDescriptor(pipelineStateDescriptor)
        } catch let error {
            print("Failed to create pipeline state, error \(error)")
        }
        
        
        
       
        
        let depthStencilStateDescriptor = MTLDepthStencilDescriptor()
        depthStencilStateDescriptor.depthCompareFunction = MTLCompareFunction.Always
        depthStencilStateDescriptor.depthWriteEnabled = true
        depthStencilStateDescriptor.frontFaceStencil.stencilCompareFunction = .Less
        depthStencilStateDescriptor.frontFaceStencil.stencilFailureOperation = .Invert
        depthStencilStateDescriptor.frontFaceStencil.depthFailureOperation = .Invert
        depthStencilStateDescriptor.frontFaceStencil.depthStencilPassOperation = .Keep
        depthStencilStateDescriptor.frontFaceStencil.readMask = 0x1
        depthStencilStateDescriptor.frontFaceStencil.writeMask = 0x1
        depthStencilStateDescriptor.backFaceStencil = nil
        depthStencilState = device.newDepthStencilStateWithDescriptor(depthStencilStateDescriptor)
        
        /*
        let samplerDescriptor = MTLSamplerDescriptor()
        samplerDescriptor.minFilter = MTLSamplerMinMagFilter.Nearest
        samplerDescriptor.magFilter = MTLSamplerMinMagFilter.Linear;
        samplerDescriptor.sAddressMode = MTLSamplerAddressMode.Repeat;
        samplerDescriptor.tAddressMode = MTLSamplerAddressMode.Repeat;
        sampler = device.newSamplerStateWithDescriptor(samplerDescriptor)
        */
        
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
        
        uniforms.setView(matrix: viewMatrix, invert: true)

        print("Uniforms:")
        print(uniforms.print)
        uniformBuffer = device.newBufferWithBytes(uniforms.bytes, length: uniforms.size, options: [])

        let shapes = CppBridge.geometries().shapeData
        
        instances = Instances(count: shapes.count)
        var size:Int = 0
        var x:Float = 0, y:Float = 0, z:Float = 0
        for var i = 0; i<instances.count; ++i {
            if mode == .Test {
                instances[i].setScale(scale: GLKVector3Make(1, 1, 1))
                instances[i].setValue(forKey: "scale", vector3: GLKVector3Make(1, 1, 1))
                instances[i].setValue(forKey: "modelMatrix", matrix4: GLKMatrix4Identity * GLKMatrix4MakeTranslation(x, y, z))
                z = Float(random() % 30) - 15; y = Float(random() % 30) - 15; x = Float(random() % 30) - 15
            }
            size += instances[i].size
            let s = instances[i].getMatrix4("modelMatrix")!.print
            print("\(i)\n\(s)")
            
        }
//        print("Size: \((size / sizeofValue(Float(0)))/19)")
        instanceBuffer = device.newBufferWithLength(size, options: [])
    }
    
    
    func drawInMTKView(view: MTKView) {
        
        // use semaphore to encode 3 frames ahead
        dispatch_semaphore_wait(inflightSemaphore, DISPATCH_TIME_FOREVER)
        
       
//        self.update()
        let pData = vertexBuffer.contents()
        memcpy(pData, cube.vertexData, cube.vertexDataSize * sizeofValue(cube.vertexData[0]))
        
        
        let commandBuffer = commandQueue.commandBuffer()
        commandBuffer.label = "Frame command buffer"
        
        guard let renderPassDesc = view.currentRenderPassDescriptor else {
            return
        }


        renderPassDesc.colorAttachments[0].loadAction = .Clear
        renderPassDesc.colorAttachments[0].storeAction = .MultisampleResolve
        renderPassDesc.colorAttachments[0].clearColor = MTLClearColorMake(0.0,1.0,0.0,1.0)
        
        renderPassDesc.depthAttachment.loadAction = .Clear
        renderPassDesc.depthAttachment.storeAction = .MultisampleResolve
        renderPassDesc.depthAttachment.clearDepth = 0.0
        
        uniforms.setValue(forKey: "time", value: uniforms.getValue("time")! + 0.01)
        if mode == .Engine {
            CppBridge.updateSceneLogic()
            uniforms.setView(matrix: CppBridge.viewMatrix(), invert: false)
        }
        
        
        let renderEncoder = commandBuffer.renderCommandEncoderWithDescriptor(renderPassDesc)
        renderEncoder.label = "render encoder"
        renderEncoder.setCullMode(MTLCullMode.Front)
       
        let uPointer = uniformBuffer.contents()
        memcpy(uPointer, uniforms.bytes, uniforms.size)
        renderEncoder.setVertexBuffer(uniformBuffer, offset: 0, atIndex: 2)

        
//        var bytes: [Float] = []
//        for var i = 0;i<instances.count; ++i{
//            bytes += instances[i].bytes
//        }
//        memcpy(iPointer, bytes, sizeofValue(bytes[0]) * bytes.count)
        
        let iPointer = instanceBuffer.contents()
        if mode == .Test {
            for var i = 0;i<instances.count; ++i{
                memcpy(iPointer + instances[i].size * i, instances[i].bytes, instances[i].size)
            }
        } else if mode == .Engine {
            let shapes = CppBridge.geometries().shapeData
            for var i = 0;i<instances.count; ++i{
                instances[i].setModel(matrix: (shapes.objectAtIndex(i) as? ShapeData)!.modelMatrix)
                instances[i].setScale(scale: (shapes.objectAtIndex(i) as? ShapeData)!.scaleVector)
                instances[i].setColor(color: (shapes.objectAtIndex(i) as? ShapeData)!.color)
                memcpy(iPointer + instances[i].size * i, instances[i].bytes, instances[i].size)
            }
        }
        
        renderEncoder.setVertexBuffer(instanceBuffer, offset: 0, atIndex: 3)
        
        renderEncoder.pushDebugGroup("draw morphing triangle")
        renderEncoder.setRenderPipelineState(pipelineState)
        renderEncoder.setDepthStencilState(depthStencilState)
        renderEncoder.setStencilReferenceValue(0xFF)
//        renderEncoder.setVertexSamplerState(sampler, atIndex: 0)
        renderEncoder.setVertexBuffer(vertexBuffer, offset: 0, atIndex: 0)
//        renderEncoder.setVertexBuffer(vertexColorBuffer, offset:0 , atIndex: 1)
        renderEncoder.setVertexBuffer(vertexNormalBuffer, offset:0 , atIndex: 1)
        
        
//        renderEncoder.drawPrimitives(.Triangle, vertexStart: 0, vertexCount: 9, instanceCount: 1)
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
    
    
    func mtkView(view: MTKView, drawableSizeWillChange size: CGSize) {
        projection = GLKMatrix4MakePerspective(45, Float(view.bounds.width/view.bounds.height), 0.01, 2000)
        uniforms.setProjection(matrix: projection)
    }
    
    override func keyDown(event: NSEvent) {
        print(event)
        switch mode {
        case .Test:
            switch event.characters! {
            case "w":
                self.viewMatrix = GLKMatrix4Translate(self.viewMatrix, 0, 0, -0.1)
                break
            case "s":
                self.viewMatrix = GLKMatrix4Translate(self.viewMatrix, 0, 0, 0.1)
                break
            case "a":
                self.viewMatrix = GLKMatrix4Translate(self.viewMatrix, -0.1, 0, 0)
                break
            case "d":
                self.viewMatrix = GLKMatrix4Translate(self.viewMatrix, 0.1, 0, 0)
                break
            case "e":
                self.viewMatrix = GLKMatrix4Translate(self.viewMatrix, 0, 0.1, 0)
                break
            case "q":
                self.viewMatrix = GLKMatrix4Translate(self.viewMatrix, 0, -0.1, 0)
                break
            default:
                return
            }
//            self.viewMatrix *= translation
            print("View Matrix:")
            print(viewMatrix.print)
            uniforms.setView(matrix: viewMatrix, invert: true)
            return
        case .Engine:
         
            return
        }
    }
    override func keyUp(event: NSEvent) {
        print(event)
    }
    
    let models = 2
    override func mouseDragged(event: NSEvent) {
        switch mode {
        case .Test:
            let rx = GLKMatrix4MakeRotation(Float(event.deltaY) * PI_OVER_180f,
                viewMatrix.m00, viewMatrix.m01, viewMatrix.m02)
            let ry = GLKMatrix4MakeRotation(Float(event.deltaX) * PI_OVER_180f,
                viewMatrix.m10, viewMatrix.m11, viewMatrix.m12)

            
            for var i = 0; i<instances.count; ++i {
                if var m = instances[i].getMatrix4("modelMatrix") {
//                    let r = viewMatrix * GLKMatrix4Transpose(m)
                    let p = GLKVector3Make(m.m30,m.m31,m.m32)
                    m *= rx
                    m *= ry
                    m = GLKMatrix4Make(
                        m.m00, m.m01, m.m02, 0,
                        m.m10, m.m11, m.m12, 0,
                        m.m20, m.m21, m.m22, 0,
                        p.x  , p.y  , p.z  , 1
                    )

//                    m = GLKMatrix4Rotate(m, Float(event.deltaY) * PI_OVER_180f,
//                        r.m00, r.m01, r.m02)
//                    m = GLKMatrix4Rotate(m, Float(event.deltaX) * PI_OVER_180f,
//                        r.m10, r.m11, r.m12)
                    if i < models {
                        print(" R: \(i)\n\(m.print)")
                    }
                    instances[i].setModel(matrix: m)
                }
            }
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
            var scale = instances[0].scale!
            scale *= (1 + Float(event.magnification))
            instances[0].setScale(scale: scale)
            return
        case .Engine:
           
            return
        }

    }
    
    override func rotateWithEvent(event: NSEvent) {
        switch mode {
        case .Test:
            viewMatrix = GLKMatrix4RotateZ(viewMatrix,Float(event.rotation) * PI_OVER_180f)
            
            print("View Matrix:")
            print(viewMatrix.print)
            uniforms.setView(matrix: viewMatrix, invert: true)

//            
//            let rz = GLKMatrix4MakeRotation(event.rotation * PI_OVER_180f,
//                viewMatrix.m20, viewMatrix.m21, viewMatrix.m22)
//            for var i = 0; i<instances.count; ++i {
//                if var m = instances[i].getMatrix4("modelMatrix") {
//                    let p = GLKVector3Make(m.m30,m.m31,m.m32)
//                    m *= rz
//                    m = GLKMatrix4Make(
//                        m.m00, m.m01, m.m02, 0,
//                        m.m10, m.m11, m.m12, 0,
//                        m.m20, m.m21, m.m22, 0,
//                        p.x  , p.y  , p.z  , 1
//                    )
//                    if i < models {
//                        print("RZ: \(i)\n\(m.print)")
//                    }
//
//                    instances[i].setModel(matrix: m)
//                }
//            }
            return
        case .Engine:
            CppBridge.turnAboutAxis("roll", withForce: event.rotation * PI_OVER_180f)
            return
        }
    }
    let mode = Mode.Engine
    enum Mode {
        case Test, Engine
    }
    
    
    override func scrollWheel(event: NSEvent) {
        switch mode {
        case .Test:
           
            viewMatrix = GLKMatrix4RotateX(viewMatrix,Float(event.deltaY) * -PI_OVER_180f)
            viewMatrix = GLKMatrix4RotateY(viewMatrix,Float(event.deltaX) * -PI_OVER_180f)
           
            print("View Matrix:")
            print(viewMatrix.print)
            uniforms.setView(matrix: viewMatrix, invert: true)
            return
        case .Engine:
            CppBridge.turnAboutAxis("pitch", withForce: -Float(event.deltaY))
            CppBridge.turnAboutAxis("yaw", withForce: -Float(event.deltaX) * PI_OVER_180f)
            return
        }

     
    }
    
    
}

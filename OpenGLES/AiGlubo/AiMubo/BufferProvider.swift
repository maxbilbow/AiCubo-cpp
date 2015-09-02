//
//  BufferProvider.swift
//  AiGlubo
//
//  Created by Max Bilbow on 31/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

import Foundation
import MetalKit


class BufferProvider {
    // 1
    let inflightBuffersCount: Int
    // 2
    private var uniformsBuffers: [MTLBuffer]
    // 3
    private var avaliableBufferIndex: Int = 0
    init(device:MTLDevice, inflightBuffersCount: Int, sizeOfUniformsBuffer: Int){
        
        self.inflightBuffersCount = inflightBuffersCount
        uniformsBuffers = [MTLBuffer]()
        
        for i in 0...inflightBuffersCount-1{
//            var uniformsBuffer = device.newBufferWithLength(sizeOfUniformsBuffer, options: nil)
//            uniformsBuffers.append(uniformsBuffer)
        }
    }
    
    func nextUniformsBuffer(projectionMatrix: UnsafeMutablePointer<Float>, modelViewMatrix: UnsafeMutablePointer<Float>) -> MTLBuffer {
        
        // 1
        let buffer = uniformsBuffers[avaliableBufferIndex]
        
        // 2
        let bufferPointer = buffer.contents()
        
        // 3
        memcpy(bufferPointer,modelViewMatrix, sizeof(Float)*16)
        memcpy(bufferPointer + sizeof(Float)*16, projectionMatrix, sizeof(Float)*16)
        
        // 4
        avaliableBufferIndex++
        if avaliableBufferIndex == inflightBuffersCount{
            avaliableBufferIndex = 0
        }
        
        return buffer
    }
    
}
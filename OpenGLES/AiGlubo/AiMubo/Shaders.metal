//
//  Shaders2.metal
//  AiGlubo
//
//  Created by Max Bilbow on 30/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#include <metal_stdlib>
using namespace metal;



// 1
struct VertexIn{
    packed_float3 position;
//    packed_float4 color;
//    packed_float2 texCoord;
};

struct VertexOut{
    float4 position [[position]];
    float4 color;
//    float2 texCoord;
};

struct Uniforms{
    float4x4 modelMatrix;
    float4x4 viewProjectionMatrix;
    float3 scaleVector;
    float4 colorVector;
//    float4x4 projectionMatrix;
   
};

vertex VertexOut basic_vertex(
                              const device VertexIn* vertex_array [[ buffer(0) ]],
                              const device Uniforms&  uniforms    [[ buffer(1) ]],
                              unsigned int vid [[ vertex_id ]]) {
    
    VertexIn VertexIn = vertex_array[vid];
    float4x4 m_Matrix = uniforms.modelMatrix;
    float4x4 vp_Matrix = uniforms.viewProjectionMatrix;
    float4 scale = float4(uniforms.scaleVector,1);
    float4 color = uniforms.colorVector;
    
    float4 position = float4(VertexIn.position,1);
    
    VertexOut VertexOut;
    VertexOut.position = vp_Matrix * m_Matrix * scale * position;
    VertexOut.color = color;
    // 2
//    VertexOut.texCoord = VertexIn.texCoord;
    
    return VertexOut;
}

// 3
fragment float4 basic_fragment(VertexOut interpolated [[stage_in]]) {//,
//                               texture2d<float>  tex2D     [[ texture(0) ]],
//                               // 4
//                               sampler           sampler2D [[ sampler(0) ]]) {
    // 5
    float4 color = interpolated.color;//tex2D.sample(sampler2D, interpolated.texCoord);
    return float4(1.0,0.0,0.0,1.0);//color;
}
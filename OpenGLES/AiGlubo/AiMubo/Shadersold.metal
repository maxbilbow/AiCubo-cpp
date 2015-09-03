//
//  Shaders.metal
//  AiMubo
//
//  Created by Max Bilbow on 30/08/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#include <metal_stdlib>

using namespace metal;

struct VertexIn
{
    float3  position;
    float3  normal;
};

struct VertexOut
{
    float4  position [[position]];
    float4  normal;
    float4  color;
};

struct Uniforms
{
    float4x4 modelViewMatrix;
    float4x4 projectionMatrix;
};


vertex VertexOut passThroughVertex(uint vid [[ vertex_id ]],
                                   const device VertexIn* vertex_array  [[ buffer(0) ]],
//                                   constant packed_float4* color        [[ buffer(1) ]],
                                   const device Uniforms& uniforms      [[ buffer(2) ]]
                                   )
{
    
    float4x4 mv_Matrix = uniforms.modelViewMatrix;
    float4x4 proj_Matrix = uniforms.projectionMatrix;
    
    VertexIn inVertex = vertex_array[vid];
    VertexOut outVertex;
    
    outVertex.position  = proj_Matrix * mv_Matrix * float4(inVertex.position,1);
    outVertex.normal    = float4(inVertex.normal,1);
    outVertex.color     = float4(color[vid]);
    
    return outVertex;
};

fragment half4 passThroughFragment(VertexOut inFrag [[stage_in]])
{
    return half4(inFrag.color);
};
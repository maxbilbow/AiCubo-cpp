//
//  Shaders.metal
//  ShaderFun
//
//  Created by Max Bilbow on 07/09/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#include <metal_stdlib>

using namespace metal;

struct VertexInOut
{
    float4  position [[position]];
    float4  color;
};

struct Uniform
{
    float4x4 viewMatrix;
    float4x4 projectionMatrix;
    float time;
};

struct Instance
{
    float4x4 modelMatrix;
    float3 scale;
};

vertex VertexInOut passThroughVertex(uint vid [[ vertex_id ]],
                                     uint iid [[ instance_id ]],
                                     constant packed_float4* pos    [[ buffer(0) ]],
                                     constant packed_float4* col    [[ buffer(1) ]],
                                     constant Uniform& u            [[ buffer(2) ]],
                                     constant Instance* i           [[ buffer(3) ]]
                                )
{
    Instance instance = i[iid];
    float4x4 view = u.viewMatrix;
    float4x4 projection = u.projectionMatrix;
    float4 scale = float4(instance.scale.xyz,1);
    float4x4 model =  instance.modelMatrix;
    
    float4 position = pos[vid];
    float4 color = col[vid];
    float time = 0;//u.time;
    

    
    VertexInOut outVertex;
    
    outVertex.position = projection * view * model * position * scale;
    outVertex.color    = float4(color.x, color.y, color.z + sin(time), color.w);
    
    return outVertex;
};

fragment half4 passThroughFragment(VertexInOut inFrag [[stage_in]])
{
    return half4(inFrag.color);
};
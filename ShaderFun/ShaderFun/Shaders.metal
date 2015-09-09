//
//  Shaders.metal
//  ShaderFun
//
//  Created by Max Bilbow on 07/09/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#include <metal_stdlib>
#include <metal_matrix>

using namespace metal;

struct VertexIn
{
    float4  position [[position]];
    float4  color;
};

struct VertexOut
{
    float4 position [[position]];
    float4 color;
    float3 normal;
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
    float4 scale;
    float4 color;
};

vertex VertexOut passThroughVertex(uint vid [[ vertex_id ]],
                                     uint iid [[ instance_id ]],
                                     constant packed_float4* pos    [[ buffer(0) ]],
                                     constant packed_float4* col    [[ buffer(1) ]],
                                     constant Uniform& u            [[ buffer(2) ]],
                                     constant Instance* instance           [[ buffer(3) ]]
                                )
{
    float4x4 viewProjection = u.projectionMatrix * u.viewMatrix;
    float4 scale = float4(instance[iid].scale.xyz,1);
    float4x4 model = instance[iid].modelMatrix;
    
    float3x3 normals = { model[0].xyz, model[1].xyz, model[2].xyz };
    
    float4 position = pos[vid] * scale;
    float4 color = normalize(col[vid] + instance[iid].color);
    float time = 0;//u.time;
    float4x4 modelViewProjection = viewProjection * model;
    
    
    VertexOut outVertex;
    
    outVertex.position = modelViewProjection * position;
    outVertex.color    = float4(color.x, color.y, color.z + sin(time), color.w);
    outVertex.normal   = float3(1);
    
    return outVertex;
};

fragment half4 passThroughFragment(VertexOut inFrag [[stage_in]])
{
    return half4(inFrag.color);
};
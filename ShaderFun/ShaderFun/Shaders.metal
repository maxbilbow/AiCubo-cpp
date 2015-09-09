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

constant float3 kLightDirection(-0.43, -0.8, -0.43);

struct VertexIn
{
    float4  position;
//    float3  normal;
//    float4  color;
};

struct VertexOut
{
    float4 position [[position]];
    float4 color;
    float3 normal;
    float time;
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
                                     constant VertexIn* vertexIn         [[ buffer(0) ]],
//                                     constant packed_float4* pos         [[ buffer(0) ]],
                                     constant packed_float3* normal         [[ buffer(1) ]],
                                     constant Uniform& u                 [[ buffer(2) ]],
                                     constant Instance* instance         [[ buffer(3) ]]
                                )
{
    float4x4 viewProjection = u.projectionMatrix * u.viewMatrix;
    float4 scale = float4(instance[iid].scale.xyz,1);
    float4x4 model = instance[iid].modelMatrix;
    
    float3x3 normalMatrix = { model[0].xyz, model[1].xyz, model[2].xyz };
    
    float4 position = vertexIn[vid].position * scale;
//    float4 position = pos[vid] * scale;
//    float4 color = normalize(col[vid] + instance[iid].color);
    float4 color = instance[iid].color;
    
    float4x4 modelViewProjection = viewProjection * model;
    
    
    VertexOut outVertex;
    
    outVertex.position = modelViewProjection * position;
    outVertex.color    = float4(color.x, color.y, color.z, color.w);
    outVertex.normal   = normalMatrix * float3(normal[vid]);
    outVertex.time     = u.time;
    
    return outVertex;
};

fragment half4 passThroughFragment(VertexOut vert [[stage_in]])
{
    float3 lightDir = kLightDirection;// float3(kLightDirection.x + sin(vert.time), kLightDirection.y, kLightDirection.z);
    float diffuseIntensity = max(0.33, dot(normalize(vert.normal), -lightDir));
    float4 diffuseColor =  vert.color; //texture.sample(texSampler, vert.texCoords);
    float4 color = diffuseColor * diffuseIntensity;
    return half4(color.r, color.g, color.b, 1);
    
//    return half4(inFrag.color);
};
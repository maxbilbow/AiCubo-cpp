//
//  GeometryIterator.m
//  AiGlubo
//
//  Created by Max Bilbow on 30/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//


#import "RMXEngine.hpp"
#import "VertexData.h"

#import <Foundation/NSArray.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>

#import "GeometryIterator.h"

using namespace rmx;
using namespace std;

typedef GameNodeList::iterator GameNodeIterator;
typedef rmx::Camera Camera;
//typedef rmx::Geometry Geometry;

@implementation ShapeData {
@private Geometry * geometry;
}

- (id)initWithGeometry:(void*)g
{
    self = [super init];
    self->geometry = (Geometry*) g;
//    self.vertexData = geometry->vertexData();
//    self.count = count;
//    self->transform = t;
//    self.color = geometry->color();
//    self.indices = i;
    return self;
}

- (long)vertexDataSize
{
    if (self->geometry != nullptr)
        return self->geometry->vertexDataSize();
    else
        return _vertexDataSize;
}

- (long)indexDataSize
{
    if (self->geometry != nullptr)
        return self->geometry->indexDataSize();
    else
        return _vertexDataSize;
}

- (float*)vertexData
{
    if (self->geometry != nullptr)
        return self->geometry->vertexData();
    else
        return _vertexData;
}

- (UInt16*)indexData
{
    if (self->geometry != nullptr)
        return self->geometry->indexData();
    else
        return _indexData;
}

//- (GLKMatrix4)modelViewMatrix
//{
//    return Scene::getCurrent()->pointOfView()->getCamera()->viewMatrix() * (self->geometry->modelMatrix() * self.scaleVector);
//}


- (NSString*)uniqueName
{
    return [NSString stringWithFormat:@"%s", self->geometry->getNode()->uniqueName().c_str()];
}

- (GLKMatrix4)modelScaleMatrix
{
    return self.modelMatrix * self.scaleVector;
}
- (GLKMatrix4)modelMatrix
{
    return self->geometry->modelMatrix();
}

- (GLKVector3)scaleVector
{
    return self->geometry->scale();
}


#if false
- (float*)modelMatrixRaw
{
    float * M;
    M = self.modelMatrix.m;
    return M;
}


- (float*)scaleVectorRaw
{
    float * V;
    V = self.scaleVector.v;
    return V;
}

- (float*)colorVectorRaw
{
    float * V;
    V = self.color.v;
    return V;
}
#endif

- (GLKVector4)color
{
    return self->geometry->color();
}

ShapeData * _cube, * _triangle;


+ (ShapeData*)cube
{
    if (_cube == NULL) {
        _cube = [[ShapeData alloc]init];
        [_cube setVertexData:cubeVertexData];
        [_cube setVertexDataSize:cubeVertexDataSize];
        [_cube setIndexData:cubeIndexData];
        [_cube setIndexDataSize:cubeIndexDataSize];
        [_cube setNormalData:cubeNormalData];
    }
    return _cube;
}

- (long)normalDataSize
{
    return _vertexDataSize;
}
//+ (ShapeData*)triangle
//{
//    if (_triangle == NULL)
//        _triangle = [[ShapeData alloc]initWithData:triandleVertexData andCount:triandleVertexDataSize andTransform:NULL andColor: GLKVector4Make(0.4, 0.4, 1.0, 1.0)];
//    return _triangle;
//}

@end




@implementation GeometryIterator {

}
//GameNodeIterator * list;
//Camera * camera;
//GameNode * node;


- (id)init
{
    self = [super init];
    _shapeData = [NSMutableArray new];
    [self updateGeometry];
    return self;
    
}

void addGeometryData(NSMutableArray * list, GameNode * node) {
    if (node->hasGeometry()) {
        Geometry *g = node->geometry();
        [list addObject:[[ShapeData alloc]initWithGeometry:node->geometry()]];
        rmx::logVector(g->color().v,4,"GeometryIterator", LOG_COLOR_INIT);
    }
    for (GameNodeList::iterator i = node->getChildren()->begin(); i != node->getChildren()->end(); ++i)
        addGeometryData(list, *i);
}

-(void)updateGeometry
{
    [_shapeData removeAllObjects];
    addGeometryData(self.shapeData, Scene::getCurrent()->rootNode());
}

-(NSMutableArray<ShapeData*>*)shapeData
{
    if (Scene::getCurrent()->geometryDidChange()) {
        [self updateGeometry];
    }
    return _shapeData;
}

@end
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

typedef rmx::GameNodeList::Iterator GameNodeIterator;
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
    return self->geometry->vertexDataSize();
}

- (long)indexDataSize
{
    return self->geometry->indexDataSize();
}

- (float*)vertexData
{
    return self->geometry->vertexData();
}

- (UInt16*)indexData
{
    return self->geometry->indexData();
}

//- (GLKMatrix4)modelViewMatrix
//{
//    return Scene::getCurrent()->pointOfView()->getCamera()->viewMatrix() * (self->geometry->modelMatrix() * self.scaleVector);
//}


- (NSString*)uniqueName
{
    return [NSString stringWithFormat:@"%s", self->geometry->getNode()->uniqueName().c_str()];
}

- (float*)modelMatrixRaw
{
    return self.modelMatrix.m;
}

- (GLKMatrix4)modelMatrix
{
    return self->geometry->modelMatrix();
}

- (GLKVector3)scaleVector
{
    return self->geometry->scale();
}

- (float*)scaleVectorRaw
{
    return self.scaleVector.v;
}

- (float*)colorVectorRaw
{
    return self.color.v;
}
- (GLKVector4)color
{
    return self->geometry->color();
}

ShapeData * _cube, * _triangle;


//+ (ShapeData*)cube
//{
//    if (_cube == NULL)
//        _cube = [[ShapeData alloc]initWithData:cubeVertexData andCount:cubeVertexDataSize andTransform:NULL andColor: GLKVector4Make(0.4, 0.4, 1.0, 1.0)];
//    return _cube;
//}


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
Camera * camera;
GameNode * node;


- (id)init
{
    self = [super init];
    [self reset];
    return self;
    
}

void addGeometryData(NSMutableArray * list, GameNode * node) {
    if (node->hasGeometry()) {
        Geometry *g = node->geometry();
        [list addObject:[[ShapeData alloc]initWithGeometry:node->geometry()]];
        cout << g->color() << endl;
    }
    GameNodeIterator * i = node->getChildren()->getIterator();
    while (i->hasNext()) {
        addGeometryData(list, i->next());
    }
}

-(void)reset
{
    
    self.shapeData = [NSMutableArray new];
    addGeometryData(self.shapeData, Scene::getCurrent()->rootNode());

    camera = Scene::getCurrent()->pointOfView()->getCamera();
//    list = Scene::getCurrent()->rootNode()->getChildren()->getIterator();
}


@end
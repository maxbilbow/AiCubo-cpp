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


@implementation ShapeData {
@private Transform * transform;
}

- (id)initWithData:( float *)data andCount:(long)count andTransform:(Transform *)t andColor:(GLKVector4)color
{
    self = [super init];
    self.vertexData = data;
    self.count = count;
    self->transform = t;
    self.color = color;
    
    return self;
}

- (long)vertexCount
{
    return _count / 6;
}

- (GLKMatrix4)modelViewMatrix
{
    return Scene::getCurrent()->pointOfView()->getCamera()->viewMatrix() * (self->transform->worldMatrix() * self.scaleVector);
}


- (NSString*)uniqueName
{
    return [NSString stringWithFormat:@"%s", self->transform->getNode()->uniqueName().c_str()];
}

- (void*)modelViewMatrixRaw
{
    return self.modelViewMatrix.m;
}

- (GLKMatrix4)modelMatrix
{
    return self->transform->worldMatrix();
}

- (GLKVector3)scaleVector
{
    return self->transform->scale();
}



ShapeData * _cube, * _triangle;


+ (ShapeData*)cube
{
    if (_cube == NULL)
        _cube = [[ShapeData alloc]initWithData:cubeData andCount:cubeDataSize andTransform:NULL andColor: GLKVector4Make(0.4, 0.4, 1.0, 1.0)];
    return _cube;
}


+ (ShapeData*)triangle
{
    if (_triangle == NULL)
        _triangle = [[ShapeData alloc]initWithData:triandleData andCount:triandleDataSize andTransform:NULL andColor: GLKVector4Make(0.4, 0.4, 1.0, 1.0)];
    return _triangle;
}

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
        [list addObject:[[ShapeData alloc]initWithData:g->vertexData andCount:g->vertexCount andTransform:node->getTransform() andColor:g->color()]];
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
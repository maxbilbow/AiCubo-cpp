//
//  GeometryIterator.h
//  AiGlubo
//
//  Created by Max Bilbow on 30/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef GeometryIterator_h
#define GeometryIterator_h


#endif /* GeometryIterator_h */

@interface ShapeData : NSObject
@property float * vertexData;
@property (nonatomic) long vertexCount;
@property long count;
@property (nonatomic) GLKMatrix4 modelViewMatrix;
@property (nonatomic) void * modelViewMatrixRaw;
@property (nonatomic) GLKMatrix4 modelMatrix;
@property (nonatomic) GLKVector3 scale;

+ (ShapeData*)cube;
+ (ShapeData*)triangle;
//- (id)initWithData:(const float*)data andCount:(const long*)count;
@end

@interface GeometryIterator : NSObject

@property NSMutableArray<ShapeData *>* shapeData;

- (id)init;
//- (BOOL)hasNext;
//- (void)reset;
//- (GLKMatrix4)modelViewMatrix;
//- (const float*)vertexData;
//- (const long*)vertexCount;

@end


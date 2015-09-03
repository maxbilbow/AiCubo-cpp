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
@property (nonatomic) float * vertexData;
@property (nonatomic) NSString* uniqueName;
@property (nonatomic) long vertexDataSize;
//@property long count;
//@property (nonatomic) GLKMatrix4 modelViewMatrix;
@property (nonatomic) float * modelMatrixRaw;
@property (nonatomic) GLKMatrix4 modelMatrix;
@property (nonatomic) GLKVector3 scaleVector;
@property (nonatomic) float* scaleVectorRaw;
@property (nonatomic) float* colorVectorRaw;

@property (nonatomic) UInt16 * indexData;
@property (nonatomic) long indexDataSize;
@property (nonatomic) GLKVector4 color;
- (id)initWithGeometry:(void*)geometry;
//+ (ShapeData*)cube;
//+ (ShapeData*)triangle;
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


//
//  CppBridge.hpp
//  AiGlubo
//
//  Created by Max Bilbow on 29/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef CppBridge_hpp
#define CppBridge_hpp

//#include <stdio.h>

#import <GLKit/GLKMatrix4.h>
#import "RMXKeyStates.h"
#import "VertexData.h"
#import <Foundation/NSArray.h>
#import "GeometryIterator.h"

#endif /* CppBridge_hpp */

//#import <Foundation/NSObject.h>
//#import <Foundation/NSString.h>
typedef struct _Uniform
{
    float * pm;
    float * mvm;
}Uniform;

@interface CppBridge : NSObject
+ (void) setupScene;
+ (GLKMatrix4) viewMatrix;
+ (GLKVector3) eulerAngles;

+ (GLKMatrix4) projectionMatrix;
+ (Uniform)getUniformWithModelViewMatrix:(GLKMatrix4)modelView withAspect:(float)aspect;
+ (float*)rawProjectionMatrixWithAspect:(float)aspect;

+ (GLKMatrix4) projectionMatrixWithAspect:(float)aspect;
+ (void) updateSceneLogic;

+ (GeometryIterator*)geometries;


+ (void) sendMessage:(NSString* )message DEPRECATED_ATTRIBUTE;

+ (void) sendMessage:(NSString* )message withScale:(float)scale DEPRECATED_ATTRIBUTE;

+ (void) sendMessage:(NSString* )message withBool:(bool)on DEPRECATED_ATTRIBUTE;

+ (void) moveWithDirection:(NSString* )direction withForce:(float)force DEPRECATED_ATTRIBUTE;

+ (void) turnAboutAxis:(NSString* )axis withForce:(float)force DEPRECATED_ATTRIBUTE;

+ (void) sendMessage:(NSString* )message withVector:(GLKVector3)vetor withScale:(float)scale DEPRECATED_ATTRIBUTE;

+ (NSString*)toStringMatrix4:(GLKMatrix4)m;

+ (void)setKey:(int)key action:(int)action withMods:(int)mods;

+ (void)setCursor:(double)x y:(double)y;
+ (void)cursorDelta:(double)dx dy:(double)dy;
//+ (const float*)vertsForShape:(unsigned int)shape;
//+ (long)sizeOf:(unsigned int)shape;

@end



//extern void RMXSetupScene();
//extern float* RMXModelViewMatrix();
//
//extern void RMXUpdateSceneLogic();
//
//extern void RMXSendMessage(char * message);
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


#endif /* CppBridge_hpp */

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
@interface CppBridge : NSObject 
+ (void) setupScene;
+ (GLKMatrix4) modelViewMatrix;

+ (void) updateSceneLogic:(GLKMatrix4)Matrix4;

+ (void) sendMessage:(NSString* )message;

+ (void) sendMessage:(NSString* )message withScale:(float)scale;

+ (void) moveWithDirection:(NSString* )direction withForce:(float)force;

+ (void) turnAboutAxis:(NSString* )axis withForce:(float)force;

+ (void) sendMessage:(NSString* )message withVector:(GLKVector3)vetor withScale:(float)scale;

+ (NSString*)toStringMatrix4:(GLKMatrix4)m;

@end

//extern void RMXSetupScene();
//extern float* RMXModelViewMatrix();
//
//extern void RMXUpdateSceneLogic();
//
//extern void RMXSendMessage(char * message);
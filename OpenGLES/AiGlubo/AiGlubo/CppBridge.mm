//
//  CppBridge.cpp
//  AiGlubo
//
//  Created by Max Bilbow on 29/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//
#import "RMXEngine.hpp"
#import "AiCubo.hpp"
//#import <GLKit/GLKMatrix4.h>

#include "CppBridge.h"

using namespace rmx;
using namespace std;

AiCubo game = AiCubo();

@implementation CppBridge

+ (void) setupScene
{
    game.run();
}
+ (GLKMatrix4) modelViewMatrix
{
    GLKMatrix4 m = Scene::getCurrent()->pointOfView()->getCamera()->modelViewMatrix();
    
    
    
    return m;
}

+ (void) updateSceneLogic {
    Scene::getCurrent()->updateSceneLogic();
}

+ (void) sendMessage:(NSString*)message {
    Transform * player = Scene::getCurrent()->pointOfView()->getTransform()->rootTransform();
    player->move(Forward);//physicsBody()->applyForce(0.5f, player->getTransform()->forward());
}

    + (NSString*)toStringMatrix4:(GLKMatrix4)m
    {
        NSString * s = @"AFTER Matrix:\n";
        s = [s stringByAppendingString:[NSString stringWithFormat:@"%f, %f, %f, %f\n", m.m00, m.m01, m.m02, m.m03]];
        s = [s stringByAppendingString:[NSString stringWithFormat:@"%f, %f, %f, %f\n", m.m10, m.m11, m.m12, m.m13]];
        s = [s stringByAppendingString:[NSString stringWithFormat:@"%f, %f, %f, %f\n", m.m20, m.m21, m.m22, m.m23]];
        s = [s stringByAppendingString:[NSString stringWithFormat:@"%f, %f, %f, %f\n", m.m30, m.m31, m.m32, m.m33]];
        
        return s;

    }
    
@end
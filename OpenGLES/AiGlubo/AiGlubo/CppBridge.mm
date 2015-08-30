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

+ (void) updateSceneLogic:(Matrix4)moodelMatrix {
    Scene::getCurrent()->updateSceneLogic();
    
//    Scene::getCurrent()->renderScene(moodelMatrix);
}

+ (void) moveWithDirection:(NSString* )direction withForce:(float)force
{
    GameNode * player = GameNode::getCurrent();
    GameNode * camera = Scene::getCurrent()->pointOfView();
    if ([direction isEqualToString:@"forward"])
        player->physicsBody()->applyForce(Forward, force);
    else if ([direction isEqualToString:@"left"])
        player->physicsBody()->applyForce(Left, force);
    else if ([direction isEqualToString:@"up"])
        player->physicsBody()->applyForce(Up, force);
    else if ([direction isEqualToString:@"pitch"])
        camera->physicsBody()->applyTorque(Pitch, force);
    else if ([direction isEqualToString:@"yaw"])
        player->physicsBody()->applyTorque(Yaw, force);
    else if ([direction isEqualToString:@"roll"])
        player->physicsBody()->applyTorque(Roll, force);

     cout << player->getTransform()->position() << endl;
}

+ (void) turnAboutAxis:(NSString* )axis withForce:(float)force
{
    GameNode * player = GameNode::getCurrent();
    GameNode * camera = Scene::getCurrent()->pointOfView();
    if ([axis isEqualToString:@"pitch"])
        camera->getTransform()->rotate(Pitch, force);
    else if ([axis isEqualToString:@"yaw"])
        player->physicsBody()->applyTorque(Yaw, force);
    else if ([axis isEqualToString:@"roll"])
        player->physicsBody()->applyTorque(Roll, force);
}

+ (void) sendMessage:(NSString*)message {
    GameNode * player = Scene::getCurrent()->pointOfView();
    if ([message isEqualToString:@"jump"])
        player->BroadcastMessage("jump");
   //physicsBody()->applyForce(0.5f, player->getTransform()->forward());
}


+ (void) sendMessage:(NSString* )message withScale:(float)scale {
    GameNode * player = Scene::getCurrent()->pointOfView();
    if ([message isEqualToString:@"jump"]) {
        if (scale == 0)
            player->BroadcastMessage("crouch");
        else if (scale == 1)
            player->BroadcastMessage("jump");
    } else if ([message isEqualToString:@"setEffectedByGravity:"]) {
        player->physicsBody()->setEffectedByGravity(scale);
    }
    NSLog(@"%@%f",message,scale);
}

+ (void) sendMessage:(NSString* )message withVector:(GLKVector3)vetor withScale:(float)scale {
    
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
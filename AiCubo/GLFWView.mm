//
//  GLFWView.m
//  RMXKit
//
//  Created by Max Bilbow on 10/09/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <AppKit/AppKit.h>

#import "CppBridge.h"
//#import <Cocoa/Cocoa.h>
#import "glfw3.h"
//#import "cocoa_platform.h"

#import "GLFWView.h"


@implementation GLFWView

- (NSMutableArray<ShapeData*>*)geometries
{
    return [CppBridge geometries].shapeData;
}

- (void)setUpGState
{
    [super setUpGState];
    _gl = glfwGetCurrentContext();
    
}


@end
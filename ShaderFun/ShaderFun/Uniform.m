//
//  cStuff.m
//  ShaderFun
//
//  Created by Max Bilbow on 07/09/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ShaderFun-Bridging-Header.h"

@implementation Uniform

- (id)init
{
    self = [super init];
    _projection = GLKMatrix4MakePerspective(65, 1, 0.01, 2000);
    _viewMatrix = GLKMatrix4Identity;
    _nearZ = 0.1;
    _farZ = 2000;
    _fov = 65;
    return self;
}

- (id)initWithBounds:(CGFloat)width height:(CGFloat)height
{
    self = [super init];
    _nearZ = 0.1;
    _farZ = 2000;
    _fov = 65;
    _projection = GLKMatrix4MakePerspective(65, height / width, 0.01, 2000);
    _viewMatrix = GLKMatrix4Identity;
    return self;
}

- (void)setProjectionWithWidth:(CGFloat)width height:(CGFloat)height
{
    _projection = GLKMatrix4MakePerspective(_fov, height / width, _nearZ, _farZ);
}

- (const float*)raw
{
    return _projection.m;
}

- (int)length
{
    return 16;
}

@end
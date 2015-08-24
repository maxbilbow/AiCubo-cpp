//
//  Includes.h
//  RMXKit
//
//  Created by Max Bilbow on 20/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef Includes_h
#define Includes_h


#endif /* Includes_h */
#import <iostream>
#import <GLKit/GLKMatrix4.h>
#import <GLKit/GLKVector3.h>
#import <GLKit/GLKVector4.h>
//
typedef GLKMatrix4 Matrix4;
typedef GLKVector3 Vector3;
typedef GLKVector4 Vector4;
typedef GLKQuaternion Quaternion;
typedef Vector3 EulerAngles;
typedef int BOOL;
#define TRUE 1
#define FALSE 0
//typedef nullptr null;
#define null nullptr
#import "RMXKit.h"
#import "RMXMath.hpp"

//#import <CoreVideo/CoreVideo.h>
//#import <IOKit/IOKitLib.h>
//#import <Cocoa/Cocoa.h>
//
#include <vector>
#include <list>

#define GLFW_h
#ifdef GLFW_h
#include "glfw3.h"
typedef GLFWwindow GLWindow;
#else
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>
#include <OpenGL/gluContext.h>
#include <GLUT/GLUT.h>
#include <GLKit/GLKit.h>
typedef long GLWindow;
#endif

namespace rmx {
    class Transform;
    class GameNode;
    class Behaviour;
    class SpriteBehaviour;
    class Geometry;
    class NodeComponent;
    class PhysicsBody;
    class Camera;
    class Scene;
    class PhysicsWorld;
    class GameView;
    class Floor;
    class Cube;
    class RenderDelegate;
    class GameController;
    typedef Dictionary<std::string, NodeComponent> GameNodeComponents;
    typedef LinkedList<Behaviour> GameNodeBehaviours;
    typedef LinkedList<GameNode> GameNodeList;
}
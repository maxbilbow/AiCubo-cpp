//
//  Window.cpp
//  RMXKit
//
//  Created by Max Bilbow on 30/07/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//
#import <iostream>
#import <GLKit/GLKVector2.h>
#import <GLUT/GLUT.h>
#import <GLKit/GLKMatrix4.h>
#import "Object.h"
#import "ASingleton.h"
#import "Camera.h"
#import "Window.h"
#import "GLFacade.h"



using namespace rmx;

void Window::toggleFullScreen(){
    if (fullscreen) {
        GL::LeaveGameMode();
        GL::InitWindowSize (getWidth(), getHeight());
        //glutInitWindowPosition (100, 100);
        initWindowSize(getWidth(),getHeight());
        id = GL::CreateWindow(title);
        //EXIT GAME MODE
        
        fullscreen = false;
    } else {
        GL::DestroyWindow(id);
        id = GL::EnterGameMode();
        GL::PostRedisplay();
        fullscreen = true;
    }
    
}
//
//  GameView.c
//  RMXKit
//
//  Created by Max Bilbow on 18/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//


#import "Includes.h"

#import "Scene.hpp"

#import "Transform.hpp"
#import "NodeComponent.hpp"
#import "GameNode.hpp"
#import "Behaviour.hpp"
#import "PhysicsBody.hpp"
#import "Delegates.hpp"
//#import <GLFW/glfw3.h>
#import "GameController.hpp"
#import "GameView.hpp"


#define GLFW_INCLUDE_GLU



//#import <Glut/Glut.h>
using namespace rmx;
using namespace std;

GameView::GameView(){
//    this->setPointOfView(GameNode::newCameraNode());
}



void GameView::initGL() {
    
   
    
#ifdef GLFW_h
    // Initialize GLFW. Most GLFW functions will not work before doing this.
    if ( glfwInit() != GL_TRUE )
        throw new invalid_argument("Unable to initialize GLFW");
    
    glfwDefaultWindowHints(); // optional, the current window hints are already the default
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE); // the window will stay hidden after creation
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); // the window will be resizable
    _window = glfwCreateWindow(_width, _height, "Hello World!", null, null);
    if ( _window == null )
        throw new invalid_argument("Failed to create the GLFW window");

    
   
    // Create the window
    
  
    
    // Setup a key callback. It will be called every time a key is pressed, repeated or released.
    glfwSetKeyCallback(_window, GameController::keyCallback);
    glfwSetWindowSizeCallback(_window, GameController::windowSizeCallback);
    
    glfwSetCursorPosCallback(_window, GameController::cursorCallback);
    // Get the resolution of the primary monitor
    const GLFWvidmode * vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    // Center our window
    glfwSetWindowPos(
                     _window,
                     (vidmode->width - _width) / 2,
                     (vidmode->height - _height) / 2
                     );
    
    // Make the OpenGL context current
    glfwMakeContextCurrent(_window);
    // Enable v-sync
    glfwSwapInterval(1);
    
    // Make the window visible
    glfwShowWindow(_window);
    
    //        more();
    
#else
    _window =  glutCreateWindow("Hello");
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    glViewport(
               (1280 - _width) / 2,
               (720 - _height) / 2,
               _width, _height);
    
    
#endif
}

void GameView::enterGameLoop() {
    //    	glfwGenuffers(1, frameBuffer);
    // This line is critical for LWJGL's interoperation with GLFW's
    // OpenGL context, or any context that is managed externally.
    // LWJGL detects the context that is current in the current thread,
    // creates the ContextCapabilities instance and makes the OpenGL
    // bindings available for use.
//    GLFWwindow * window =
#ifdef GLFW_h
    glfwMakeContextCurrent(_window);
#else
//    CGLSetCurrentContext(_window);
    CGLGetCurrentContext();
#endif
    // >> glEnableVertexAttribArray enables the generic vertex attribute array specified by index.
    // >> glDisableVertexAttribArray disables the generic vertex attribute array specified by
    // >> index. By default, all client-side capabilities are disabled, including all generic
    // >> vertex attribute arrays. If enabled, the values in the generic vertex attribute array
    // >> will be accessed and used for rendering when calls are made to vertex array commands
    // >> such as glDrawArrays, glDrawElements, glDrawRangeElements, glMultiDrawElements, or glMultiDrawArrays.
    // Enable the vertex position vertex attribute.
    //        glEnableVertexAttribArray(VERTEX_POSITION);
    // Enable the vertex colour vertex attribute.;
    //        glEnableVertexAttribArray(VERTEX_COLOUR);
    
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    //        GL11.glMatrixMode(GL11.GL_PROJECTION);
    //        GL11.glLoadIdentity();
    
    // >> glVertexAttribPointer and glVertexAttribIPointer specify the location and data format of the
    // >> array of generic vertex attributes at index index to use when rendering. size specifies
    // >> the number of components per attribute and must be 1, 2, 3, 4, or GL_BGRA. type specifies
    // >> the data type of each component, and stride specifies the byte stride from one attribute
    // >> to the next, allowing vertices and attributes to be packed into a single array or stored
    // >> in separate arrays.
    // Tell OpenGL where to find the vertex position data (inside the VBO).
    //        glVertexAttribPointer(VERTEX_POSITION, 2, GL_DOUBLE, false, 0, 0);
    // Tell OpenGL where to find the vertex colour data (inside the VBO).
    //        glVertexAttribPointer(VERTEX_COLOUR, 3, GL_DOUBLE, false, 0, 8 * 4 * 2);
    
    
    
    //        GL11.glMatrixMode(GL11.GL_MODELVIEW);
    //        GL11.glHint(GL11.GL_PERSPECTIVE_CORRECTION_HINT, GL11.GL_NICEST);
    
    
    
    //        glClearColor(8.0f, 0.0f, 0.0f, 0.0f);
    // Run the rendering loop until the user has attempted to close
    // the window or has pressed the ESCAPE key.
    while ( glfwWindowShouldClose(_window) == GL_FALSE ) {
        Scene * scene = Scene::getCurrent();
        Camera * camera = pointOfView()->getCamera();
        
        if (this->delegate != null)
            this->delegate->updateBeforeScene(_window);
        
        scene->updateSceneLogic();
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        camera->makePerspective(this);
        
        
        
        glClearColor(0.3f, 0.3f, 0.3f, 0.3f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the framebuffer
        glMatrixMode(GL_MODELVIEW);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glLoadIdentity();
        
//            camera.look();
        scene->renderScene(camera);
        
        glfwSwapBuffers(_window);
        
        glMatrixMode(GL_PROJECTION);
        // swap the color buffers
        if (this->delegate != null)
            this->delegate->updateAfterScene(_window);
        
        // Poll for window events. The key callback above will only be
        // invoked during this call.
        glfwPollEvents();
        
        NotificationCenter::eventDidOccur(END_OF_GAMELOOP);
        
    }
}



bool GameView::setPointOfView(GameNode * pointOfView) {
    if (!pointOfView->hasCamera()) 
        throw new invalid_argument("PointOfView musy have a camera != null");//pointOfView->setCamera(new Camera());//
    this->_pointOfView = pointOfView;
    return true;
}

RenderDelegate * GameView::getDelegate() {
    return this->delegate;
}


void GameView::setDelegate(RenderDelegate * delegate) {
    this->delegate = delegate;
}




GLFWwindow * GameView::window() {
    // TODO Auto-generated method stub
    return _window;
}

void GameView::errorCallback(int i, const char *c) {
    cout << "there was an error: " << c << endl;
}



int GameView::width() {
    return _width;
}

void GameView::setWidth(int width) {
    this->_width = width;
}

int GameView::height() {
    return _height;
}

void GameView::setHeight(int height) {
    this->_height = height;
}

GameNode * GameView::pointOfView() {
    if (_pointOfView != null )//|| this->setPointOfView(GameNode::getCurrent()))
        return _pointOfView;
    throw invalid_argument("ERROR: Could Not Set _pointOfView");
    return   null;
}

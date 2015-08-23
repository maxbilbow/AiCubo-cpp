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
    this->setPointOfView(GameNode::newCameraNode());
}

void GameView::initGL() {
    
    if (!glfwInit())
        throw new invalid_argument("Unable to initialize GLFW");
    
    // Configure our window
    glfwDefaultWindowHints(); // optional, the current window hints are already the default
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE); // the window will stay hidden after creation
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); // the window will be resizable
    
    // Create the window
    _window = glfwCreateWindow(_width, _height, "Hello World!", null, null);
    if ( _window == null )
        throw new invalid_argument("Failed to create the GLFW window");
    
    // Setup a key callback. It will be called every time a key is pressed, repeated or released.
    glfwSetKeyCallback(_window, GameController::keyCallback);
    
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
}

void GameView::enterGameLoop() {
    //    	glfwGenuffers(1, frameBuffer);

    glfwMakeContextCurrent(_window);
    
    
    
    
//    glEnable(GL_TEXTURE_2D);
//    glShadeModel(GL_SMOOTH);
//    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//    glClearDepth(1.0);
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LEQUAL);
    
    // Use Gouraud (smooth) shading
    glShadeModel(GL_SMOOTH);
    
    // Switch on the z-buffer
    glEnable(GL_DEPTH_TEST);
    
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_COLOR_ARRAY);
//    glVertexPointer(3, GL_FLOAT, sizeof(struct Vertex), vertex);
//    glColorPointer(3, GL_FLOAT, sizeof(struct Vertex), &vertex[0].r); // Pointer to the first color
//    
//    glPointSize(2.0);
    
    // Background color is black
    glClearColor(0, 0, 0, 0);
    
    while (!glfwWindowShouldClose(_window))
    {
        Scene * scene = Scene::getCurrent();
        Camera * camera = pointOfView()->getCamera();
        if (this->delegate != null)
            this->delegate->updateBeforeScene(_window);
        scene->updateSceneLogic();
        
        float ratio;
        int width, height;
        
        glfwGetFramebufferSize(_window, &width, &height);
        ratio = width / (float) height;
        
        glViewport(0, 0, width, height);
        glClearColor(0.3f, 0.3f, 0.3f, 0.3f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the framebuffer
//        glMatrixMode(GL_MODELVIEW);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
//        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        camera->makePerspective(this);
        glMatrixMode(GL_MODELVIEW);
        
        glLoadIdentity();
//        glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
        
        scene->renderScene(camera);
        
        glfwSwapBuffers(_window);
        glfwPollEvents();
        NotificationCenter::eventWillStart(END_OF_GAMELOOP);
        if (this->delegate != null)
            this->delegate->updateAfterScene(_window);
        NotificationCenter::eventDidEnd(END_OF_GAMELOOP);
    }

}



bool GameView::setPointOfView(GameNode * pointOfView) {
    if (!pointOfView->hasCamera()) {
        throw new invalid_argument("PointOfView musy have a camera != null");//pointOfView->setCamera(new Camera());//
    } else if (_pointOfView == pointOfView)
        return false;
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
    if (_pointOfView != null || this->setPointOfView(GameNode::getCurrent()))
        return _pointOfView;
    throw invalid_argument("ERROR: Could Not Set _pointOfView");
    return   null;
}

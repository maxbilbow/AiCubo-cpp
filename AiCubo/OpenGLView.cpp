//
//  OpenGLView.cpp
//  RMXKit
//
//  Created by Max Bilbow on 29/07/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//
#import "Constants.h"
#import <iostream>
//#import <OpenGL/OpenGL.h>
#import <GLUT/glut.h>
//#import <GLKit/GLKVector3.h>
//#import <GLKit/GLKVector4.h>
#import <GLKit/GLKMatrix4.h>
#import "Object.h"
#import "ASingleton.h"
#import "Camera.h"
#import "Window.h"
#import "GLFacade.h"
#import "OpenGLView.h"


using namespace std;

namespace RMX {

    void Display() {
        
        
    }

    void LoadView(void)
    {
        //    int width, height;
        //    int nComponents;
        //    void* pTextureImage;
        
        
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        //glEnable(GL_LIGHT1);
        // Create texture for cube; load marble texture from file and bind it
        //pTextureImage = read_texture("marble.rgb", &width, &height, &nComponents);
    //    glBindTexture(GL_TEXTURE_2D, TEXTURE_ID_CUBE);
        
        glGenerateMipmap(GL_MAP1_NORMAL);
        //    gluBuild2DMipmaps(GL_TEXTURE_2D,     // texture to specify
        //                      GL_RGBA,           // internal texture storage format
        //                      width,             // texture width
        //                      height,            // texture height
        //                      GL_RGBA,           // pixel format
        //                      GL_UNSIGNED_BYTE,	// color component format
        //                      pTextureImage);    // pointer to texture image
        glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                         GL_LINEAR_MIPMAP_LINEAR);
        glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        
        
    //    DrawFog(true);
    }
    //@class RMXGLProxy;
    void AnimateScene(void)
    {
        //animate();
    //    [world.thisWorld animate];
    //    if (world.thisWorld == nil) exit(1);
        
        //[sun drawWith:DrawSphere];
    //    DrawFog();
        //[art animate];
        // getDt();
        GL::PostRedisplay();
        
    }

    void OpenGLView::reshape (int width, int height) {
        //[window setSize:width h:height]; //glutGet(GLUT_WINDOW_WIDTH);
        // window.height = height;// glutGet(GLUT_WINDOW_HEIGHT);
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        GL::perspective(65.0, (float) width / height, 1, 2000);
        //GLKMatrix4MakePerspective(65*PI_OVER_180 ,(float)window.width / window.height, window.nearPlane, window.farPlane);
        glMatrixMode(GL_MODELVIEW);
    }

    bool alt = true;

    void OpenGLView::display (void) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.8f, 0.85f, 1.8f, 0.0f);
        //[rmxDebugger add:RMX_DISPLAY_PROCESSOR n:@"DisplayProcessor" t:[NSString stringWithFormat:@"r%f, g%f, b%f, k%f",art.r,art.g,art.b,art.k]];
        glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations
    //    [world.observer.camera makeLookAtGl:gluLookAt]; @TODO
        
        
        GL::LookAt(Camera::current());
        
    //    repeatedKeys();
        AnimateScene();
        // Make sure changes appear onscreen
        GL::SwapBuffers();
        glFlush();
    //    debug();
        //tester.checks[1] = observer->toString();
        //NSLog([world.observer viewDescription]);
        
        
    }






    void keyPressed (unsigned char key, int x, int y){
    //    RMXkeyPressed(key, x, y);
    }
    void keyUp (unsigned char key, int x, int y){
    //    RMXkeyUp(key, x, y);
    }
    void keySpecial (int key, int x, int y){
    //    RMXkeySpecial(key, x, y);
    }
    void keySpecialUp (int key, int x, int y){
    //    RMXkeySpecialUp(key, x, y);
    }

    void mouseButton(int button, int state, int x, int y){
    //    MouseButton(button, state, x, y);
    }
    void mouseMotion(int x, int y){
    //    MouseMotion(x, y);
    }
    void mouseFree(int x, int y){
    //    MouseFree(x, y);
    }

    void idle(){
    //    [RMXGLProxy animateScene];
    }


    //#ifdef RMX_USE_DEPRECIATED

    int OpenGLView::Run(int argc, char * argv[])
    {
        
        GL::Init(argc, argv);
    //    initKeys();
        
        
        GL::InitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
        
        
        if (FULL_SCREEN && GL::GameModeGet(GLUT_GAME_MODE_POSSIBLE)){
            GL::EnterGameMode();
        }else {
            cout << "Game Mode Not Possibe" << endl;
            GL::CreateWindow("AiCubo");
            
    //        (100,100,1280,720,"AiCubo");
        }
        //Setup Display:
        GL::DisplayFunc(Display);
        GL::ReshapeFunc(reshape);
        
        // Register callbacks:
        GL::KeyboardFunc(keyPressed);
        GL::KeyboardUpFunc(keyUp);
        GL::SpecialFunc(keySpecial);
        GL::SpecialUpFunc(keySpecialUp);
        
        GL::MouseFunc(mouseButton);
        GL::MotionFunc(mouseMotion);
        GL::PassiveMotionFunc(mouseFree);
        
        //Animation
        GL::IdleFunc(idle);
        
        LoadView();
        
        
        if (FULL_SCREEN) {
    //        [RMXGLProxy performAction:@"toggleMouseLock"];

        }
        GL::MainLoop();
        return 0;
    }
}

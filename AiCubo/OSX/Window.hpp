//
//  Window.hpp
//  RMXKit
//
//  Created by Max Bilbow on 30/07/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <stdio.h>

#endif /* Window_hpp */
#define VIEWING_DISTANCE_MIN  3.0

namespace RMX {
    
    
    //#include "RattleGLI.h"
    //void init();
    //template <typename Particle>
    class Window : public ASingleton<Window> {
        
        static Window * _current;
        
    protected:
        int id;
        int height, width;
        float fViewDistance = 3 * VIEWING_DISTANCE_MIN;
        float nearPlane = 1;
        float farPlane = 1000;
        bool fullscreen = false;
        //template <typename Number>
        const char * title = "Rattle X Window";
        
        
        void
        //Display
        (*initWindowSize)(int width, int height),
        //(*initDisplayMode)(unsigned int mode),
        (*displayFunc)(void (*func)(void)),
        (*reshapeFunc)(void (*func)(int width, int height)),
        //Keyboard
        (*keyPressed)(void (*func)(unsigned char key, int x, int y)),
        (*keyUp)(void (*func)(unsigned char key, int x, int y)),
        (*keySpecial)(void (*func)(int key, int x, int y)),
        (*keySpecialUp)(void (*func)(int key, int x, int y)),
        //Mouse
        (*mouseFunc)(void (*func)(int button, int state, int x, int y)),
        (*motionFunc)(void (*func)(int x, int y)),
        (*passiveMotionFunc)(void (*func)(int x, int y)),
        //Other
        (*idleFunc)(void (*func)(void));
        // (*initalise)(void);
        
        Window() {
            this->height = 600;
            this->width = 600;
        }
        
    public:
        static Window * Default() {
            if (_current != nullptr)
                return _current;
            else {
                _current = new Window();
                return _current;
            }
        }
        
        
        int getWidth(){
            return this->width;
        }
        int getHeight(){
            return this->height;
        }
        
        
        void setSize(int width, int height){
            this->width = width;
            this->height = height;
        }
        
        float getNearPlane(){
            return nearPlane;
        }
        
        float getFarPlane(){
            return farPlane;
        }
        bool isFullscreen(){
            return fullscreen;
        }
        
        float getFViewDistance() {
            return fViewDistance;
        }
        
        void setFViewDistance(float fViewDistance){
            this->fViewDistance = fViewDistance;
        }
        //Glut Init
        void init(
                  //Display
                  void (*initWindowSize)(int width, int height),
                  //void (*initDisplayMode)(unsigned int mode),
                  void (*displayFunc)(void (*func)(void)),
                  void (*reshapeFunc)(void (*func)(int width, int height)),
                  //Keyboard
                  void (*keyPressed)(void (*func)(unsigned char key, int x, int y)),
                  void (*keyUp)(void (*func)(unsigned char key, int x, int y)),
                  void (*keySpecial)(void (*func)(int key, int x, int y)),
                  void (*keySpecialUp)(void (*func)(int key, int x, int y)),
                  //Mouse
                  void (*mouseFunc)(void (*func)(int button, int state, int x, int y)),
                  void (*motionFunc)(void (*func)(int x, int y)),
                  void (*passiveMotionFunc)(void (*func)(int x, int y)),
                  //Other
                  void (*idleFunc)(void (*func)(void))//,
        // void (*init)(void)
        ) {
            //Set Display
            this->initWindowSize = initWindowSize;
            //this->initDisplayMode = initDisplayMode;
            this->displayFunc = displayFunc;
            this->reshapeFunc = reshapeFunc;
            //Set Keyboard
            this->keyPressed = keyPressed;
            this->keyUp = keyUp;
            this->keySpecial = keySpecial;
            this->keySpecialUp = keySpecialUp;
            //Set Mouse
            this->mouseFunc = mouseFunc;
            this->motionFunc = motionFunc;
            this->passiveMotionFunc = passiveMotionFunc;
            //Other
            this->idleFunc = idleFunc;
            
            
            //this->initDisplayMode(
            //init();
            
        }
        
        void toggleFullScreen();
        
        
        
        
        void display (void (*display)(void),void (*reshape)(int width, int height)){
            displayFunc(display);
            reshapeFunc(reshape);
        }
        
        
        
        
        void keyboard(
                      void (*pressed)(unsigned char key, int x, int y),
                      void (*up)(unsigned char key, int x, int y),
                      void (*special)(int key, int x, int y),
                      void (*specialUp)(int key, int x, int y)
                      ){
            keyPressed(pressed);
            keyUp(up);
            keySpecial(special);
            keySpecialUp(specialUp);
            
        }
        
        
        void mouse(
                   void (*mouse)(int button, int state, int x, int y),
                   void (*motion)(int x, int y),
                   void (*passiveMotion)(int x, int y)
                   ) {
            mouseFunc(mouse);
            motionFunc(motion);
            passiveMotionFunc(passiveMotion);
        }
        
        void idle (void (*func)(void)){
            idleFunc(func);
        }
        
    };

}
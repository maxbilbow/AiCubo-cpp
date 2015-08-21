//
//  GameController.hpp
//  RMXKit
//
//  Created by Max Bilbow on 18/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef GameController_hpp
#define GameController_hpp

#include <stdio.h>

#endif /* GameController_hpp */

namespace rmx {

    typedef bool KeyStates;

    class GameController : public Object,  public RenderDelegate  {
        GameView * view;
        static GameController * _singleton;
        
        void initpov();
        void setup();

        GameController();
        
        static int keys[600];
        
        bool cursorLocked;
    public:
        static GameController * getInstance();
        void lockCursor(bool lock);
        bool isCursorLocked();
        void run();
        
//        bool * keys = new KeyStates[500];
        
        void repeatedKeys(GLFWwindow * window);
        
        void setView(GameView * view);
        
        static void keyCallback(GLFWwindow* w,int a,int b,int c,int d);
        
        static void cursorCallback(GLFWwindow*,double,double);
        void updateBeforeScene(GLFWwindow * window) override;
        void updateAfterScene(GLFWwindow * window) override;
        
    };

}
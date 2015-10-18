//
//  GameController.cpp
//  RMXKit
//
//  Created by Max Bilbow on 18/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#import "Includes.h"

#import "Scene.hpp"

#import "GameNode.hpp"

#import "Delegates.hpp"
#import "Transform.hpp"
#import "Behaviour.hpp"
#import "PhysicsBody.hpp"

#import "GameView.hpp"
#import "Geometry.hpp"
#ifdef GLFW
#import "glfw3.h"
#endif
#import "RMXKeyStates.h"
#import "GameController.hpp"
#import "EntityGenerator.hpp"
#import "SpriteBehaviour.hpp"
using namespace std;
using namespace rmx;

GameController::GameController() {
    if (_singleton != nullptr)
        throw invalid_argument("GameController already started");
    else
        _singleton = this;
    this->view = new GameView();
    this->view->setDelegate(this);
    this->lockCursor(true);
    //    this->setView(new GameView());
}

GameController * GameController::_singleton = nullptr;// = new GameController();
GameController * GameController::getInstance() {
    if(_singleton ==   nullptr) {
        _singleton = new GameController();
    }
    return _singleton;
}





void GameController::run() {
    
    this->setup();
#ifdef GLFW
    this->view->initGL();
    this->view->enterGameLoop();
    
    
    glfwDestroyWindow(view->window());
    
    glfwTerminate();
#endif
    
    
}


void GameController::updateBeforeScene(GLWindow * window) {
    this->repeatedKeys(window);
}


void GameController::updateAfterScene(GLWindow * window) {
    
}



int GameController::getKeyState(GLWindow * w, int key) {
#ifndef GLFW
    return GameController::getInstance()->keys[key];
#else
    return getkeyState(w,key);
#endif
    
}


void GameController::repeatedKeys(GLWindow * window) {
    GameNode * player = GameNode::getCurrent();
    //    #ifdef GLFW
    //GameNode::getCurrent();
    
    if (getKeyState(window, RMX_KEY_W) == RMX_PRESS) {
        player->BroadcastMessage("forward", new float(1.0));
    }
    
    if (getKeyState(window, RMX_KEY_S) == RMX_PRESS) {
        player->BroadcastMessage("forward", new float(-1.0));
    }
    
    if (getKeyState(window, RMX_KEY_A) == RMX_PRESS) {
        player->BroadcastMessage("left", new float(1.0));
    }
    
    if (getKeyState(window, RMX_KEY_D) == RMX_PRESS) {
        player->BroadcastMessage("left", new float(-1.0));
    }
    
    if (getKeyState(window, RMX_KEY_E) == RMX_PRESS) {
        player->BroadcastMessage("up", new float(1.0));
    }
    
    if (getKeyState(window, RMX_KEY_Q) == RMX_PRESS) {
        player->BroadcastMessage("up", new float(- 1.0));
    }
    //    if (getKeyState(window, RMX_KEY_SPACE) == RMX_PRESS) {
    //        player->BroadcastMessage("jump");
    //    }
    
    if (getKeyState(window, RMX_KEY_RIGHT) == RMX_PRESS) {
        player->getTransform()->move(Yaw, 1.0f);
    }
    
    if (getKeyState(window, RMX_KEY_LEFT) == RMX_PRESS) {
        player->getTransform()->move(Yaw,-1.0f);
    }
    
    if (getKeyState(window, RMX_KEY_UP) == RMX_PRESS) {
        view->pointOfView()->getTransform()->move(Pitch,-1.0f);
    }
    
    if (getKeyState(window, RMX_KEY_DOWN) == RMX_PRESS) {
        view->pointOfView()->getTransform()->move(Pitch, 1.0f);
    }
    
    if (getKeyState(window, RMX_KEY_X) == RMX_PRESS) {
        player->getTransform()->move(Roll, 1.0f);
    }
    
    if (getKeyState(window, RMX_KEY_Z) == RMX_PRESS) {
        player->getTransform()->move(Roll,-1.0f);
    }
    //#endif
    //    cout << player->getTransform()->localMatrix();
    //    cout << "             Euler: " << player->getTransform()->eulerAngles() << endl;
    //    cout << "       Local Euler: " << player->getTransform()->localEulerAngles() << endl;
    //    cout << "          Position: " << player->getTransform()->position() << endl;
    //    cout << endl;
}


void GameController::setView(GameView * view) {
    this->view = view;
    this->view->setDelegate(this);
    //    this->keys = new int[600];
}

//int GameController::keys[600] = {0};

GameNode * player() {
    return GameNode::getCurrent();
}

void GameController::initButtons()
{
    
}

void GameController::keyCallback(GLWindow *window, int key, int scancode, int action, int mods) {
    GameController * gc = GameController::getInstance();
    gc->keys[key] = action;
    if (action == RMX_PRESS) {
        switch (key) {
            case RMX_KEY_SPACE:
                GameNode::getCurrent()->BroadcastMessage("crouch");
                break;
            default:
                cout << key << " (down) not recognised" << endl;
        }
    } else if (action == RMX_RELEASE)
        switch (key) {
            case RMX_KEY_SPACE:
                GameNode::getCurrent()->BroadcastMessage("jump");
                break;
            case RMX_KEY_ESCAPE:
                exit(0);
                break;
            case RMX_KEY_W:
                //			 Node.getCurrent().transform.moveForward(1);
                break;
            case RMX_KEY_M:
                
                if (gc->cursorLocked) {
#ifdef GLFW
                    glfwSetInputMode(window, RMX_CURSOR, RMX_CURSOR_NORMAL);
#endif
                    gc->lockCursor(false);
                } else {
#ifdef GLFW
                    glfwSetInputMode(window, RMX_CURSOR, RMX_CURSOR_DISABLED);
#endif
                    gc->lockCursor(true);
                }
                break;
            case RMX_KEY_G:
                if (mods == RMX_MOD_SHIFT)
                    player()->physicsBody()->setEffectedByGravity(false);
                else
                    player()->physicsBody()->setEffectedByGravity(true);
                break;
        }
    
}


void GameController::lockCursor(bool lock) {
    this->cursorLocked = lock;
}
bool GameController::isCursorLocked() {
    return this->cursorLocked;
}

double xpos ,ypos;
bool restart = true;

void GameController::cursorCallback(GLWindow * w, double x, double y) {
    
    GameController * gc = getInstance();
    
    if (!gc->cursorLocked)
        return;
    //    cout << "CURSOR: " << w << ", " << x << ", " << y << endl;
    if (restart) {
        xpos = x;
        ypos = y;
        restart = false;
        return;
    } else {

        double dx = x * 0.4;
        double dy = y * 0.4;
        
        Transform * body = GameNode::getCurrent()->getTransform();
        Transform * head = gc->view->pointOfView()->getTransform();
        
        if (gc->passiveMode)
            head->rotate(Yaw,   dx);
        else {
            body->rotate(Yaw,   dx);
            head->rotate(Pitch, dy);
        }
    }
    
    
}
GameView * GameController::getView() {
    return this->view;
}

void GameController::windowSizeCallback(GLWindow * window, int width, int height) {
    GameController * gvc = getInstance();
    gvc->view->setWidth(width);
    gvc->view->setHeight(height);
#ifdef GLFW
    glfwSetWindowSize(window, width, height);
#endif
}
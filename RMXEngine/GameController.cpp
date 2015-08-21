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
//#import <GLFW/glfw3.h>
#import "GameView.hpp"
#import "Geometry.hpp"
#import "GameController.hpp"

using namespace std;
using namespace rmx;

GameController::GameController() {
    this->view = new GameView();
    this->view->setDelegate(this);
//    this->setView(new GameView());
}

GameController * GameController::_singleton = new GameController();
GameController * GameController::getInstance() {
    if(_singleton ==   null) {
        _singleton = new GameController();
    }
    return _singleton;
}


void GameController::initpov() {
    GameNode * n = GameNode::getCurrent();
    n->setPhysicsBody(new PhysicsBody());
    cout << n->physicsBody() << endl;
    n->physicsBody()->setMass(1.0f);

    n->setGeometry(Geometry::Cube());
    n->getTransform()->setScale(2.0f, 0.02f, 2.0f);
    Scene::getCurrent()->rootNode()->addChild(n);
}

class BehaviourA : public Behaviour {
public:
    void update() override {
        this->getNode()->getTransform()->move(Forward,0.1);
    }
};

class BehaviourB : public Behaviour {
public:
    void update() override {
        this->getNode()->getTransform()->move(Yaw,   0.1);
        this->getNode()->getTransform()->move(Pitch, 0.1);
        this->getNode()->getTransform()->move(Roll,  0.1);
    }
    
};

class BehaviourC : public Behaviour {
public:
    void update() override {
        this->getNode()->getTransform()->move(Forward,0.5);
        this->getNode()->getTransform()->move(Yaw,  0.1);
    }
    
};

void GameController::setup() {
    Scene * scene = Scene::getCurrent();
    initpov();
    
    GameNode * cube = GameNode::makeCube(0.5f, true, new BehaviourA());
    cube->getTransform()->setPosition(0.0f,0.0f,5.0f);
        
        
    GameNode * cube2 = GameNode::makeCube(0.2f, true, new BehaviourB());
        
    GameNode * cube3 = GameNode::makeCube(0.5f, true, new BehaviourC());
    cube3->getTransform()->setPosition(-10.0f,0.0f,10.0f);
    cube3->addChild(cube2);
    cube2->getTransform()->setPosition(0.0f,1.0f,0.0f);
        
    GameNode * floor = new GameNode("Floor");
    floor->getTransform()->setPosition(0,0,0);
    scene->rootNode()->addChild(floor);
        
    floor->setGeometry(new Floor());
    
}

void GameController::run() {
        //
        //       System.out.println("Hello LWJGL " + Sys.getVersion() + "!");
//        try {
    
            this->setup();
//            SharedLibraryLoader::load();
            
            this->view->initGL();
            this->view->enterGameLoop();
            
            // Release window and window callbacks
            glfwDestroyWindow(view->window());
//            view->keyCallback().release();
//        } catch (exception e){
//            cout << typeid(this).name() << ": " << e.what() << endl;
//        }
    // Terminate GLFW and release the GLFWerrorfun
            glfwTerminate();
//            view.errorCallback().release();
    
}
    

void GameController::updateBeforeScene(GLFWwindow * window) {
    this->repeatedKeys(window);
}


void GameController::updateAfterScene(GLFWwindow * window) {
    
}

void GameController::repeatedKeys(GLFWwindow * window) {
    GameNode * player = this->view->pointOfView();//GameNode::getCurrent();
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        player->getTransform()->move(Forward, 1.0f);
    }
    
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        player->getTransform()->move(Forward,-1.0f);
    }
    
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        player->getTransform()->move(Left, 1.0f);
    }
    
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        player->getTransform()->move(Left, -1.0f);
    }
    
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        player->getTransform()->move(Up,-1.0f);
    }
    
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        player->getTransform()->move(Up, 1.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        player->BroadcastMessage("jump");
    }
    
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        player->getTransform()->move(Yaw, 1.0f);
    }
    
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        player->getTransform()->move(Yaw,-1.0f);
    }
    
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        player->getTransform()->move(Pitch,1.0f);
    }
    
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        player->getTransform()->move(Pitch, -1.0f);
    }
    
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        player->getTransform()->move(Roll, 1.0f);
    }
    
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        player->getTransform()->move(Roll,-1.0f);
    }
    
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

int GameController::keys[600] = {0};
void GameController::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
//    cout << "  KEYS: " << key << ", " << scancode << ", " << action << ", " << mods << endl;
    GameController * gc = getInstance();
    if (action == GLFW_PRESS) {
        gc->keys[key] = action;
        cout << "Key Down: " << (char) key << " " << scancode << " " << action << " " << mods << endl;
    } else if (action == GLFW_RELEASE) {
        gc->keys[key] = action;
        cout << "  Key Up: " << (char) key << " " << scancode << " " << action << " " << mods << endl;
    }
    
    if (action == GLFW_RELEASE)
        switch (key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GL_TRUE);
                break;
            case GLFW_KEY_W:
                //			 Node.getCurrent().transform.moveForward(1);
                break;
            case GLFW_KEY_M:
                
                if (gc->cursorLocked) {
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                    gc->lockCursor(false);
                } else {
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                    gc->lockCursor(true);
                }
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

void GameController::cursorCallback(GLFWwindow * w, double x, double y) {
    
    GameController * gc = getInstance();
    
    if (!gc->cursorLocked)
        return;
    cout << "CURSOR: " << w << ", " << x << ", " << y << endl;
    if (restart) {
        xpos = x;
        ypos = y;
        restart = false;
        return;
    } else {
        double dx = x - xpos;
        double dy = y - ypos;
        dx *= 0.1; dy *= 0.1;
        xpos = x;
        ypos = y;
        Transform * t = gc->view->pointOfView()->getTransform();
        t->move(Pitch, dy);
        t->move(Yaw,   dx);
    }
    
    
}
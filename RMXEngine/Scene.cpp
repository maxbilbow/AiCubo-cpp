//
//  Scene.cpp
//  RMXKit
//
//  Created by Max Bilbow on 19/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#import "Includes.h"


#import "NodeComponent.hpp"
#import "Transform.hpp"
#import "Camera.hpp"
#import "GameNode.hpp"
#import "PhysicsWorld.hpp"
#import "Scene.hpp"
#import "Delegates.hpp"
#import "GameView.hpp"
#import "GameController.hpp"


using namespace rmx;
using namespace std;

Scene * Scene::_current =   nullptr;

Scene::Scene() {
    this->_rootNode = new GameNode("rootNode");
    cout << "initializing scene" << endl;
    if (_current == nullptr) {
          cout << "Setting Scene::_current" << endl;
        _current = this;
    }
}


//	private static Scene current;
Scene * Scene::getCurrent() {
    if (Scene::_current ==   nullptr)
        _current = new Scene();
    return _current;
}

bool Scene::geometryDidChange() {
    return _rootNode->geometryDidChange();
}

Scene * Scene::setCurrent(Scene * scene) {
    Scene * old = _current;
    _current = scene;
    return old;
}

void Scene::setAsCurrent() {
    setCurrent(this);
}


void Scene::renderScene(Matrix4 modelMatrix) {
//    this->_rootNode->draw(cam->modelViewMatrix());

//    if (this->renderDelegate != null)
//        this->renderDelegate.updateBeforeSceneRender(cam);

#ifdef GLFW
    GameNodeList * children = _rootNode->getChildren();
    for (GameNodeList::iterator i = children->begin(); i != children->end(); ++i)
        (*i)->draw(modelMatrix);
#endif
}
#import <thread>

void updateLogic(GameNodeList * children) {
    for (GameNodeList::iterator i = children->begin(); i != children->end(); ++i)
        (*i)->updateLogic();
}

void updatePhysics(Scene * scene) {
    scene->physicsWorld()->updatePhysics(scene->rootNode());
}

void updateCollisions(Scene * scene) {
    scene->physicsWorld()->updateCollisionEvents(scene->rootNode());
}

PhysicsWorld * Scene::physicsWorld() {
    return _physicsWorld;
}

void Scene::updateSceneLogic() {
    GameNodeList * children = _rootNode->getChildren();
//    thread logic (updateLogic,children);
     updateLogic(children);
//    thread physics (updatePhysics,this);
//    thread collisions(updateCollisions,this);
    
    
    
   
    _physicsWorld->updatePhysics(this->_rootNode);
    _physicsWorld->updateCollisionEvents(this->_rootNode);

//    logic.join();
//    physics.join();
//    collisions.join();
    for (GameNodeList::iterator i = children->begin(); i != children->end(); ++i)
        (*i)->updateAfterPhysics();
}

GameNode * Scene::rootNode() {
    return _rootNode;
}

GameNode * Scene::pointOfView() {
    return GameController::getInstance()->getView()->pointOfView();
}
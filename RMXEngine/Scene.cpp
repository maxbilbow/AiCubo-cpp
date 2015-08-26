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


using namespace rmx;
using namespace std;

Scene * Scene::_current =   null;

Scene::Scene() {
    this->_rootNode = new GameNode("rootNode");
}
//	private static Scene current;
Scene * Scene::getCurrent() {
    if (Scene::_current ==   null)
        _current = new Scene();
    return _current;
}

Scene * Scene::setCurrent(Scene * scene) {
    Scene * old = _current;
    _current = scene;
    return old;
}

void Scene::setAsCurrent() {
    setCurrent(this);
}


void Scene::renderScene(Camera * camera) {
//    this->_rootNode->draw(cam->modelViewMatrix());

//    if (this->renderDelegate != null)
//        this->renderDelegate.updateBeforeSceneRender(cam);

    LinkedList<GameNode>::Iterator * i = _rootNode->getChildren()->getIterator();
    while (i->hasNext()) {
        i->next()->draw(camera->modelViewMatrix());
    }
}


void Scene::updateSceneLogic() {
    LinkedList<GameNode>::Iterator * i = _rootNode->getChildren()->getIterator();
    while (i->hasNext()) {
        i->next()->updateLogic();
    }
    this->_physicsWorld->updatePhysics(this->_rootNode);
//    if (this->renderDelegate != null)
//        this->renderDelegate->updateBeforeSceneLogic();
    _physicsWorld->updatePhysics(this->_rootNode);
    _physicsWorld->updateCollisionEvents(this->_rootNode);
    i->begin();
    while (i->hasNext()) {
        i->next()->updateAfterPhysics();
    }
    
}

GameNode * Scene::rootNode() {
    return _rootNode;
}
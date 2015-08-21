//
//  Node.c
//  RMXKit
//
//  Created by Max Bilbow on 18/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//
//#import <iostream>

#import "Includes.h"

#import "NodeComponent.hpp"
#import "Transform.hpp"
#import "Geometry.hpp"

#import "Scene.hpp"
#import "Camera.hpp"
#import "PhysicsBody.hpp"
#import "Behaviour.hpp"
#import "GameNode.hpp"


using namespace rmx;
using namespace std;
    
GameNode * GameNode::_current = GameNode::newCameraNode();

GameNode::GameNode() {
    this->setName("GameNode");
    this->onLoad();
}

GameNode::GameNode(string name) {
    this->setName(name);
    this->onLoad();
}



void GameNode::onLoad() {
    this->_hasGeometry = this->_hasPhysicsBody = FALSE;
//    this->camera = new Camera();
    this->_transform = new Transform(this);
    this->afterLoad();
}

void GameNode::setCurrent(GameNode * node) {
    GameNode::_current = node;
}
    
Transform * GameNode::getTransform() {
    return _transform;
}

GameNode * GameNode::getCurrent() {
        if (_current == null)
            _current = newCameraNode();
        return _current;
}
    
NodeComponent * GameNode::setComponent(NodeComponent * component)  {
    string key = typeid(component).name();
//    NodeComponent * result = this->components->getValueForKey(key);
    cout << "Adding component: " << component << endl;
    return this->components.setValueForKey(key,component);
}

void GameNode::addBehaviour(Behaviour * behaviour) {
    if (behaviour != null && !this->behaviours->contains(behaviour)) {
        this->behaviours->append(behaviour);
        behaviour->setNode(this);
    }
}
    
NodeComponent * GameNode::getComponent(string className) {
    return this->components.getValueForKey(className);
}


GameNodeList * GameNode::getChildren() {
    return &this->children;
}
    
void GameNode::addChild(GameNode * child) {
    if (!this->children.contains(child)) {
        this->children.append(child);
        child->setParent(this);
    }
}
    
bool GameNode::removeChildNode(GameNode * node) {
    return this->children.removeValue(node);
}

GameNode * GameNode::getChildWithName(string name) {
    GameNodeList::Iterator * i = this->children.getIterator();
    while (i->hasNext()) {
        GameNode * n = i->next();
        if (n->Name() == name)
            return n;
    }
    return    null;
}
    

Camera * GameNode::getCamera() {
//    cout << this << endl;
    return this->camera;// GameNode::getCurrent()->camera;// new Camera();// this->camera;
//    if (this->camera != null)
//        return this->camera;//(Camera*) this->getComponent(typeid(Camera).name());
//    else {
//        cout << "WARNING: Camera is null, generating new... " << this << endl;
//        this->camera = new Camera();
//        this->camera->setName("Spare Camera");
//        this->camera->setNode(this);
//    }
//    return this->camera;
}

bool GameNode::hasCamera() {
    return this->_hasCamera;
}
void GameNode::setCamera(Camera * camera) {
//    this->setComponent(camera);
    camera->setNode(this);
    this->camera = camera;
    this->_hasCamera = TRUE;
}
    
GameNode * GameNode::newCameraNode() {
    GameNode * cameraNode = new GameNode("CameraNode");
    cameraNode->setCamera(new Camera());
    if (_current == null)
        _current = cameraNode;
    cameraNode->addBehaviour(new SpriteBehaviour());
    cameraNode->setPhysicsBody(new PhysicsBody());
    cameraNode->physicsBody()->setMass(1);
    return cameraNode;
}
    
Geometry * GameNode::geometry() {
    return this->_geometry;// (Geometry) this.getComponent(Geometry.class);
}

bool GameNode::hasGeometry() {
    return this->_hasGeometry;
}

void GameNode::setGeometry(Geometry * geometry) {
    this->_geometry = geometry;
    this->_hasGeometry = TRUE;
}
    
PhysicsBody * GameNode::physicsBody(){
//    PhysicsBody * body = (PhysicsBody*) this->getComponent(typeid(PhysicsBody).name());
//    if (body ==   null)
//        cout << "WARNING: null returned when requesting physicsBody in GameNode" << endl;
//    if (this->_physicsBody != null)
        return this->_physicsBody;
//    else
//        return null;
}

bool GameNode::hasPhysicsBody() {
    return this->_hasPhysicsBody;
}

void GameNode::setPhysicsBody(PhysicsBody * body) {
//    this->setComponent(body);
    this->_physicsBody = body;
    body->setNode(this);
    this->_hasPhysicsBody = TRUE;
}
    
void GameNode::updateLogic() {
//    bool isBEmpty = this->behaviours->isEmpty();
    GameNodeBehaviours::Iterator * bi = this->behaviours->getIterator();
//    if (!isBEmpty)
        while (bi->hasNext()) {
            Behaviour * b = bi->next();
            if (b->isEnabled())
                b->update();
        }
//    if (!this->children.isEmpty()) {
        GameNodeList::Iterator * ci = this->children.getIterator();
        while (ci->hasNext()) {
            GameNode * n = ci->next();
            if (n != null)
                n->updateLogic();
        }
//    }
//    if (!isBEmpty) {
        bi->begin();
        while (bi->hasNext()) {
            Behaviour * b = bi->next();
            if (b->isEnabled())
                b->lateUpdate();
        }
//    }
}

void GameNode::draw(Matrix4 rootTransform) {
    if (this->_hasGeometry) {
        this->_geometry->render(this, rootTransform);
    }
    GameNodeList::Iterator * i = this->children.getIterator();
    while (i->hasNext()) {
        i->next()->draw(rootTransform);
    }
}

    
    

    
GameNode * GameNode::getParent() {
    return this->parent;
}
    
void GameNode::setParent(GameNode * parent) {
    if (this->parent !=   null && parent != this->parent) {
        this->parent->removeChildNode(this);
        this->parent = parent;
    }
}

///TODO
void GameNode::SendMessage(std::string message, void * args, SendMessageOptions options) {
    //TODO
}

void GameNode::BroadcastMessage(std::string message, void * args, SendMessageOptions options) {
    GameNodeBehaviours::Iterator * i = this->behaviours->getIterator();
    while (i->hasNext())
        i->next()->SendMessage(message,args,options);
}
    
GameNode * GameNode::makeCube(float s,bool body, Behaviour * b) {
    GameNode * n = new GameNode("Cube");
    n->setGeometry(Geometry::Cube());
        if (body)
            n->setPhysicsBody(new PhysicsBody());
        n->getTransform()->setScale(s, s, s);
        n->addBehaviour(b);
        n->addToCurrentScene();
        return n;
    }
    
void GameNode::addToCurrentScene() {
    Scene::getCurrent()->rootNode()->addChild(this);
}

void GameNode::setTransform(Transform *transform) {
    if (this->_transform !=   null)
//        throw invalid_argument("Transform can only be set once! " + this->ToString());
        cout << "WARNING: Transform can only be set once! " << this << endl;
    else
        this->_transform = transform;
}

void GameNode::test() {
    Object * o = new Object();
    o->setName("Parent");
    GameNode * o2 = GameNode::newCameraNode();
    
    try {
        o->SendMessage("getCamera",  null);
        
        o2->SendMessage("getCamera",  null);
        o->SendMessage("getCamera",new string("Hello 1"));
        o2->SendMessage("getCamera",new string("Hello Node"));
    } catch (exception e) {
        // TODO Auto-generated catch block
        cout << typeid(GameNode).name() << " " << "ERROR: " << e.what() << endl;
    }
    o2->updateLogic();
}

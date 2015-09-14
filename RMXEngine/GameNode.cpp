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
#import "CollisionBody.hpp"
#import "Scene.hpp"
#import "Camera.hpp"
#import "PhysicsBody.hpp"
#import "Behaviour.hpp"

#import "GameNode.hpp"


using namespace rmx;
using namespace std;
    
GameNode * GameNode::_current;// = GameNode::newCameraNode();

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
        if (_current == nullptr)
            _current = new GameNode("Player");
        return _current;
}

void GameNode::setDidCollideThisTurn(bool didCollideThisTurn) {
    _didCollideThisTurn = didCollideThisTurn;
}

bool GameNode::didCollideThisTurn() {
    if (_didCollideThisTurn) {
        _didCollideThisTurn = false;
        return true;
    } else
        return false;
}

NodeComponent * GameNode::setComponent(NodeComponent * component)  {
    string key = typeid(component).name();
//    NodeComponent * result = this->components->getValueForKey(key);
    cout << "Adding component: " << component->uniqueName() << " to " << this->uniqueName() << endl;
    return this->components.setValueForKey(key,component);
}

bool GameNode::hasBehaviour(Behaviour * behaviour) {
//    GameNodeList * children = scene->rootNode()->getChildren();//->getIterator();
    for (GameNodeList::iterator i = children.begin(); i != children.end(); ++i)
        if ((*i)->ClassName() == behaviour->ClassName())
            return true;
    return false;
}

void GameNode::addBehaviour(Behaviour * behaviour) {
    if (behaviour != nullptr && !this->hasBehaviour(behaviour)) {
        cout << "BEHAVIOUR: Adding " << behaviour->uniqueName() << " to " << this->uniqueName() << endl;
        this->behaviours->insert(behaviour);
        behaviour->setNode(this);
    } else {
        string reason = behaviour == nullptr ? " NullPointerException" : "Behaviour has already been added";
        cout << "!!! FAILED to add " << behaviour->uniqueName() << " to " << this->uniqueName() << endl;
        cout << " -- REASON: " << reason << endl;
    }
}
    
NodeComponent * GameNode::getComponent(string className) {
    return this->components.getValueForKey(className);
}


//GameNodeList::Iterator * GameNode::childNodeIterator() {
//    return this->children.getIterator();
//}

GameNodeList * GameNode::getChildren() {
    return &this->children;
}

void GameNode::addChild(GameNode * child) {
//    if (!this->children.contains(child)) {

        this->children.insert(child);
        if (child->parent != nullptr && this != child->parent) {
            child->getParent()->removeChildNode(child);
        }
        child->parent = this;
        if (child->geometryDidChange()) {
            this->_geometryDidChange = true;
        }
        cout << "GameNode: Adding child: " << child->uniqueName() << " to " << this->uniqueName() << endl;
//    } else {
//        cout << "!!! WARNING: " << child->uniqueName() << " was NOT added to " << this->uniqueName() << endl;
//        cout << " --  REASON: child may already exist in children" << endl;
//    }
    
}
    
bool GameNode::removeChildNode(GameNode * node) {
    return this->children.erase(node); //this->children.removeValue(node);
}

GameNode * GameNode::getChildWithName(string name) {
//    GameNodeList::Iterator * i = this->children.getIterator();
    for (GameNodeList::iterator i = children.begin(); i != children.end(); ++i)
        if ((*i)->Name() == name)
            return *i;
    return   nullptr;
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
    
//GameNode * GameNode::newCameraNode() {
//    GameNode * cameraNode = new GameNode("CameraNode");
//    cameraNode->setCamera(new Camera());
//    return cameraNode;
//}

Geometry * GameNode::geometry() {
    return this->_geometry;// (Geometry) this.getComponent(Geometry.class);
}


bool GameNode::hasGeometry() {
    return this->_hasGeometry;
}

void GameNode::setGeometry(Geometry * geometry) {
    this->_geometry = geometry;
    geometry->setNode(this);
    this->_hasGeometry = TRUE;
    _geometryDidChange = true;
    GameNode * root = this->rootNode();
    root->_geometryDidChange = true;
    if (root != Scene::getCurrent()->rootNode())
        cout << "!!! WARNING: " << root->uniqueName() << " == Scene->rootNode" << endl;
}

bool GameNode::geometryDidChange(bool reset) {
    if (_geometryDidChange && reset) {
        _geometryDidChange = false;
        return true;
    }
    return _geometryDidChange;
}

GameNode * GameNode::rootNode() {
//    if (this->parent == nullptr)
//        cout << "CHILD: " << this << ", PARENT: " << this->parent << endl;
    return this->parent == nullptr ? this : this->parent->rootNode();
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
//    GameNodeBehaviours::Iterator * bi = this->behaviours->getIterator();
//    if (!isBEmpty)
//        while (bi->hasNext()) {
//            Behaviour * b = bi->next();
        for (GameNodeBehaviours::iterator i = this->behaviours->begin(); i != behaviours->end(); ++i)
            if ((*i)->isEnabled())
                (*i)->update();
//        }
//    if (!this->children.isEmpty()) {
        for (GameNodeList::iterator i = children.begin(); i != children.end(); ++i)
            (*i)->updateLogic();
    
//    }
//    if (!isBEmpty) {
    
}

void GameNode::updateAfterPhysics() {
    for (GameNodeBehaviours::iterator i = this->behaviours->begin(); i != behaviours->end(); ++i)
        if ((*i)->isEnabled())
            (*i)->lateUpdate();
    
    
    //    }
    _transform->updateLastPosition();
    _tick++;
}
void GameNode::draw(Matrix4 rootTransform) {
    if (this->_hasGeometry) {
        this->_geometry->render(this, rootTransform);
    
//    GameNodeList::Iterator * i = this->children.getIterator();
        
    for (GameNodeList::iterator i = children.begin(); i != children.end(); ++i)
        (*i)->draw(rootTransform);
    }
}

    
    

    
GameNode * GameNode::getParent() {
    return this->parent;
}


//void GameNode::setParent(GameNode * parent) {
//    if (parent == nullptr)
//        throw invalid_argument("GameNode parent was NULL!");
//    if (this->parent != nullptr && parent != this->parent) {
//        this->parent->removeChildNode(this);
//    }
//    
////    if (typeid(parent) == typeid(RootNode))
////        this->parent = null;
////    else
//     this->parent = parent;
//    cout << "Adding child: " << this->uniqueName() << " to " << this->parent->uniqueName() << endl;
//}

///TODO
void GameNode::SendMessage(std::string message, void * args, SendMessageOptions options) {
    //TODO
    cout << "Message Received by " << this->uniqueName() << ": " << message << endl;
}

void GameNode::BroadcastMessage(std::string message, void * args, SendMessageOptions options) {
//    GameNodeBehaviours::Iterator * i = this->behaviours->getIterator();
//    while (i->hasNext()) {
//        Behaviour * b = i->next();
    for (GameNodeBehaviours::iterator i = this->behaviours->begin(); i != behaviours->end(); ++i)
        (*i)->SendMessage(message,args,options);
//        cout << "Message sent to: " << b->uniqueName() << endl;
    
}

GameNode * GameNode::makeCube(float s, PhysicsBody * body) {
    GameNode * n = new GameNode("Cube");
    n->setGeometry(Geometry::Cube());
    if (body!=nullptr)
        n->setPhysicsBody(body);
    n->getTransform()->setScale(s, s, s);
    return n;
}
    
void GameNode::addToCurrentScene() {
    Scene::getCurrent()->rootNode()->addChild(this);
}

void GameNode::setTransform(Transform *transform) {
    if (this->_transform !=   nullptr)
//        throw invalid_argument("Transform can only be set once! " + this->ToString());
        cout << "WARNING: Transform can only be set once! " << this << endl;
    else
        this->_transform = transform;
}

CollisionBody * GameNode::collisionBody() {
    if (_hasPhysicsBody)
        return _physicsBody->collisionBody();
    else
        return nullptr;
}



//
//  AiCubo.cpp
//  RMXKit
//
//  Created by Max Bilbow on 26/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#include "RMXEngine.hpp"
using namespace rmx;
using namespace std;
#include "AiCubo.hpp"


void AiCubo::setup() {
    GameController::setup();
    Scene * scene = Scene::getCurrent();
    
    
    GameNode * cube = GameNode::makeCube(2.0f, PhysicsBody::newDynamicBody());
    cube->addBehaviour( new BehaviourA());
    cube->getTransform()->setPosition(0.0f,100.0f,5.0f);
    
    
    
    
    GameNode * floor = new GameNode("Floor");
    floor->setGeometry(new Cube());
    float inf = 600;
    floor->setPhysicsBody(PhysicsBody::newStaticBody());
    floor->getTransform()->setScale(inf, 10, inf);
    floor->getTransform()->setPosition(0, -10, 0);
    scene->rootNode()->addChild(floor);
    
    EG eg = EG();
    
    eg.makeShapesAndAddToScene(scene, 1);
    
    LinkedList<GameNode>::Iterator * i = scene->rootNode()->getChildren()->getIterator();
    while(i->hasNext()) {
        GameNode * node = i->next();
        if (node->getTransform() == nullptr) {
            cout << node << endl;
            throw invalid_argument("Transform cannot be NULL!");
        }
    }
    

    GameNode * box = GameNode::makeCube(5, PhysicsBody::newDynamicBody());
    box->getTransform()->setPosition(10, 10, 10);
    box->addToCurrentScene();
    
    GameNode * box2 = GameNode::makeCube(5, PhysicsBody::newStaticBody());
    box2->getTransform()->setPosition(10, 5, -10);
    box2->addToCurrentScene();
    
    
    GameNode * box3a = GameNode::makeCube(2, PhysicsBody::newStaticBody());
    box3a->getTransform()->setPosition(-5, 2, -10);
    box3a->addToCurrentScene();
    
    GameNode * box3 = GameNode::makeCube(3, PhysicsBody::newStaticBody());
    box3->getTransform()->setPosition(-10, 3, -10);
    box3->addToCurrentScene();
    
    GameNode * box4 = GameNode::makeCube(5, PhysicsBody::newStaticBody());
    box4->getTransform()->setPosition(-15, 5, -10);
    box4->addToCurrentScene();
    
    GameNode * box5 = GameNode::makeCube(8, PhysicsBody::newStaticBody());
    box5->getTransform()->setPosition(-20, 8, -10);
    box5->addToCurrentScene();
    
}

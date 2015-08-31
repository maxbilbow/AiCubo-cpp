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
    
    
    GameNode * cube = GameNode::makeCube(0.5f, true);
    cube->addBehaviour( new BehaviourA());
    cube->getTransform()->setPosition(0.0f,0.0f,5.0f);
    
    
    
    
    GameNode * floor = new GameNode("Floor");
    floor->getTransform()->setPosition(0,0,0);
    scene->rootNode()->addChild(floor);
    
    floor->setGeometry(new Cube());
    float inf = 9999;
    floor->getTransform()->setScale(inf, inf, inf);
    floor->getTransform()->setPosition(0, -inf/2, 0);
    floor->setPhysicsBody(PhysicsBody::newTransientBody());
    
    
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
    

    GameNode * box = GameNode::makeCube(5, false);
    box->setPhysicsBody(PhysicsBody::newStaticBody());
    box->getTransform()->setPosition(10, 5, 10);
    box->addToCurrentScene();
    
}

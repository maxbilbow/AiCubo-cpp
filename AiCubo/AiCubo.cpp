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
    
    
    GameNode * cube = GameNode::makeCube(0.5f, true, new BehaviourA());
    cube->getTransform()->setPosition(0.0f,0.0f,5.0f);
    
    
    
    
    GameNode * floor = new GameNode("Floor");
    floor->getTransform()->setPosition(0,0,0);
    scene->rootNode()->addChild(floor);
    
    floor->setGeometry(new Floor());
    
    
    EG eg = EG();
    
    eg.makeShapesAndAddToScene(scene, 1);
    
    LinkedList<GameNode>::Iterator * i = scene->rootNode()->getChildren()->getIterator();
    while(i->hasNext()) {
        GameNode * node = i->next();
        if (node->getTransform() == null) {
            cout << node << endl;
            throw invalid_argument("Transform cannot be NULL!");
        }
    }
    

    GameNode * box = GameNode::makeCube(5, false, null);
    box->setPhysicsBody(PhysicsBody::newStaticBody());
    box->getTransform()->setPosition(10, 5, 10);
    box->addToCurrentScene();
    
}

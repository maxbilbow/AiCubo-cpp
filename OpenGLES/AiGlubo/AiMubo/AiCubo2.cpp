//
//  AiCubo.cpp
//  RMXKit
//
//  Created by Max Bilbow on 26/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#include "RMXEngine.hpp"
#include "SpriteBehaviour.hpp"
using namespace rmx;
using namespace std;
#include "AiCubo.hpp"
#include "EntityGenerator.hpp"

GameNode * EntityGenerator::makeEntity(){
    GameNode * node = AiCubo::newAiCubo();
    node->addBehaviour(new MoveForward());
    node->addBehaviour(new ApplyTorque());
    return node;
}


GameNode * AiCubo::newAiCubo()
{
    float size = 1;
    GameNode * body = GameNode::makeCube(size, PhysicsBody::newDynamicBody());
    body->addBehaviour(new SpriteBehaviour());
    GameNode * head = GameNode::makeCube(size * 0.7);
    head->setName("head");
    GameNode * eyeLeft = GameNode::makeCube(size * 0.1);
    eyeLeft->setName("leftEye");
    GameNode * eyeRight = GameNode::makeCube(size * 0.1);
    eyeRight->setName("eyeRight");
    eyeLeft->geometry()->setColor(1.0,1.0,1.0);
    eyeRight->geometry()->setColor(1.0,1.0,1.0);
    head->addChild(eyeLeft);
    head->addChild(eyeRight);
    body->addChild(head);
    head->getTransform()->setPosition(0.0f,2.0f,1.0f);
    eyeLeft->getTransform()->setPosition(0.2, 0.0, size * 0.7);
    eyeRight->getTransform()->setPosition(-0.2, 0.0, size * 0.7);
    return body;
}
void AiCubo::initpov() {
    GameController::initpov();
    GameNode * player = AiCubo::newAiCubo();// GameNode::getCurrent();
    player->setName("player");
    player->setPhysicsBody(PhysicsBody::newDynamicBody());
    player->physicsBody()->setMass(2);

    
    player->getTransform()->scaleNode(1.5f);//.0f, 3.0f, 2.0f);
    player->getTransform()->setPosition(10,100, -50);
    player->addToCurrentScene();

    player->addBehaviour(new MoveForward()); //TODO: Remove when we have control
        player->addBehaviour(new ApplyTorque(0.001));
    if (this->passiveMode) {

        player->addBehaviour(new ApplyTorque());
    }
    GameNode * head = player->getChildWithName("head");//new GameNode("Camera");//GameNode::newCameraNode();// new GameNode("Head");
    head->setCamera(new Camera());
    
    player->setGeometry(nullptr);
    head->setGeometry(nullptr);
    head->getChildren()->clear();

    view->setPointOfView(head);
    GameNode::setCurrent(player);
}

void AiCubo::setup() {
//    this->passiveMode = true;
    GameController::setup();
    Scene * scene = Scene::getCurrent();
    
    
//    GameNode * cube = GameNode::makeCube(2.0f, PhysicsBody::newDynamicBody());
////    cube->addBehaviour( new BehaviourA());
//    cube->getTransform()->setPosition(0.0f,100.0f,5.0f);
//    
    
    
    
    GameNode * floor = new GameNode("Floor");
    floor->setGeometry(Geometry::Cube());
    float inf = 600;
    floor->setPhysicsBody(PhysicsBody::newStaticBody());
    floor->getTransform()->setScale(inf, inf, inf);
    floor->getTransform()->setPosition(0, -inf, 0);
    scene->rootNode()->addChild(floor);
    
    EntityGenerator eg = EntityGenerator();
    eg.yMin = 10;
    eg.makeShapesAndAddToScene(scene, 100);
    
//    LinkedList<GameNode>::Iterator * i = scene->rootNode()->childNodeIterator();
//    while(i->hasNext()) {
//        GameNode * node = i->next();
//        if (node->getTransform() == nullptr) {
////            cout << node << endl;
//            throw invalid_argument("AiCubo::Transform cannot be NULL!");
//        }
//    }
    
    
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
    
    GameNode * box6 = GameNode::makeCube(1, PhysicsBody::newStaticBody());
    box6->getTransform()->setPosition(0, 1, -10);
    box6->addToCurrentScene();
    
    GameNode * box7 = GameNode::makeCube(1, PhysicsBody::newStaticBody());
    box7->getTransform()->setPosition(0, 1, 10);
    box7->addToCurrentScene();
    
    GameNode * box8 = GameNode::makeCube(1, PhysicsBody::newStaticBody());
    box8->getTransform()->setPosition(-10, 1, 0);
    box8->addToCurrentScene();
    
    GameNode * box9 = GameNode::makeCube(1, PhysicsBody::newStaticBody());
    box9->getTransform()->setPosition(10, 1, 0);
    box9->addToCurrentScene();
    
    Bugger::getInstance()->printToTerminalAfterStartUpInfoAndSwitchToDefault();
    
}

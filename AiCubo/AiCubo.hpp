//
//  AiCubo.hpp
//  RMXKit
//
//  Created by Max Bilbow on 26/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef AiCubo_hpp
#define AiCubo_hpp

#include <stdio.h>

#endif /* AiCubo_hpp */


namespace rmx {
   
class BehaviourA : public Behaviour {
public:
    void update() override {
//        Transform * t = this->getNode()->getTransform();
        //        t->physicsBody()->applyForce(0.01, t->forward());
    }
};

class BehaviourB : public Behaviour {
public:
    void update() override {
        //        Transform * t = this->getNode()->getTransform();
        //        PhysicsBody * b = t->physicsBody();
        //        b->applyTorque(0.1, t->up());
        //        b->applyTorque(0.1, t->forward());
//                b->applyTorque(0.1, t->left());
        this->getNode()->getTransform()->move(Yaw,   0.1);
//        this->getNode()->getTransform()->move(Pitch, 0.1);
//        this->getNode()->getTransform()->move(Roll,  0.1);
    }
    
};

class BehaviourC : public Behaviour {
public:
    void update() override {
        Transform * t = this->getNode()->getTransform();
        PhysicsBody * b = t->physicsBody();
        b->applyTorque(0.01, t->up());
        b->applyForce(0.1, t->forward());
    }
    
};

class EG : public EntityGenerator {
public:
    GameNode * makeEntity() override {
        float size = 1;
        GameNode * body = GameNode::makeCube(size, PhysicsBody::newDynamicBody());
        body->addBehaviour( new BehaviourC());
        
        GameNode * head = GameNode::makeCube(size * 0.7);
        head->addBehaviour( new BehaviourB());
        GameNode * eyeLeft = GameNode::makeCube(size * 0.1);
        GameNode * eyeRight = GameNode::makeCube(size * 0.1);
        eyeLeft->geometry()->setColor(1.0,1.0,1.0);
        eyeRight->geometry()->setColor(1.0,1.0,1.0);
        head->addChild(eyeLeft);
        head->addChild(eyeRight);
        body->addChild(head);
        head->getTransform()->setPosition(0.0f,1.0f,1.0f);
        eyeLeft->getTransform()->setPosition(0.2, 0.0, size * 0.7);
        eyeRight->getTransform()->setPosition(-0.2, 0.0, size * 0.7);
        return body;
    }
};
}

class AiCubo : public rmx::GameController {
protected:
    void setup() override;
    void initpov() override;
};
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
        //        b->applyTorque(0.1, t->left());
        this->getNode()->getTransform()->move(Yaw,   0.1);
        this->getNode()->getTransform()->move(Pitch, 0.1);
        this->getNode()->getTransform()->move(Roll,  0.1);
    }
    
};

class BehaviourC : public Behaviour {
public:
    void update() override {
        Transform * t = this->getNode()->getTransform();
        PhysicsBody * b = t->physicsBody();
        b->applyTorque(0.01, t->left());
        //        b->applyForce(0.01, t->forward());
    }
    
};

class EG : public EntityGenerator {
public:
    GameNode * makeEntity() override {
        GameNode * head = GameNode::makeCube(0.2f, false);
        head->addBehaviour( new BehaviourB());
        GameNode * body = GameNode::makeCube(0.5f, true);
        body->addBehaviour( new BehaviourC());
        //        body->getTransform()->setPosition(-10.0f,0.0f,10.0f);
        body->addChild(head);
        head->getTransform()->setPosition(0.0f,1.0f,0.0f);
        return body;
    }
};
}

class AiCubo : public rmx::GameController {
protected:
    void setup() override;
};
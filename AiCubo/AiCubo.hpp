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


class AiCubo : public rmx::GameController {
protected:
    void setup() override;
    void initpov() override;
public:
    static rmx::GameNode * newAiCubo();
    
};


namespace rmx {
    
   
class MoveForward : public Behaviour {
public:
    void update() override {
        Transform * t = this->getNode()->getTransform();
        t->physicsBody()->applyForce(0.1, t->forward());
    }
    
    
    virtual std::string ClassName() override {
        return "rmx::MoveForward";
    }
};

class TurnBehaviour : public Behaviour {
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
    
    virtual std::string ClassName() override {
        return "rmx::TurnBehaviour";
    }
    
};

class ApplyTorque : public Behaviour {
public:
    float amount = 0.01;
    
    ApplyTorque(){}
    ApplyTorque(float amount) {
        this->amount = amount;
    }
    void update() override {
        Transform * t = this->getNode()->getTransform();
        PhysicsBody * b = t->physicsBody();
        b->applyTorque(amount, t->up());

    }
    
    std::string ClassName() override {
        return "rmx::ApplyTorque";
    }
    
};
}
//class Eg : public EntityGenerator {
//public:
//    GameNode * makeEntity() override;
//};





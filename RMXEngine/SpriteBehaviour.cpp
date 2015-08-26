//
//  SpriteBehaviour.cpp
//  RMXKit
//
//  Created by Max Bilbow on 26/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#include "Includes.h"

#include "GameNode.hpp"
#include "NodeComponent.hpp"
#include "Transform.hpp"
#include "PhysicsBody.hpp"
#include "Behaviour.hpp"
#include "SpriteBehaviour.hpp"

using namespace rmx;
using namespace std;

void SpriteBehaviour::SendMessage(string message, void * args, SendMessageOptions options) {
//    if ((args) != null)
//        cout << message << ": " << *((float*)args) << endl;
    if (message == "forward")
        this->getNode()->physicsBody()->applyForce(*((float*)args) * -1, getNode()->getTransform()->forward());
    else if (message == "left")
        this->getNode()->physicsBody()->applyForce(*((float*)args) * -1, getNode()->getTransform()->left());
    else if (message == "up")
        this->getNode()->physicsBody()->applyForce(*((float*)args), getNode()->getTransform()->up());
    else if (message == "pitch")
        this->getNode()->physicsBody()->applyForce(*((float*)args), getNode()->getTransform()->left());
    else if (message == "yaw")
        this->getNode()->physicsBody()->applyForce(*((float*)args), getNode()->getTransform()->up());
    else if (message == "roll")
        this->getNode()->physicsBody()->applyForce(*((float*)args), getNode()->getTransform()->forward());
    else if (message == "jump")
        this->getNode()->physicsBody()->applyForce(10, GLKVector3Make(0,1,0));
    else if (message == "onCollision") {
//        CollisionEvent * e = (CollisionEvent*) args;
//        cout << "       Pos:" << this->getTransform()->position() << endl;
//        cout << "   LastPos:" << this->getTransform()->lastPosition() << endl;
////        cout << "" << endl;
    }
    
    //            std::cout << this->getNode()->getTransform()->localMatrix();
}

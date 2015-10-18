//
//  PhysicsWorld.cpp
//  RMXKit
//
//  Created by Max Bilbow on 19/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#import "Includes.h"

#import "BoundingBox.hpp"
#import "BoundingSphere.hpp"



#import "NodeComponent.hpp"
#import "PhysicsBody.hpp"
#import "CollisionBody.hpp"
#import "CollisionEvent.hpp"
#import "GameNode.hpp"
#import "Transform.hpp"
#import "PhysicsWorld.hpp"

#define List std::list<CollisionBody*>
using namespace std;
using namespace rmx;



Vector3 PhysicsWorld::getGravity() {
    return this->gravity;
}

void PhysicsWorld::setGravity(Vector3 gravity) {
    this->gravity = gravity;
}

void PhysicsWorld::setGravity(float x, float y, float z) {
    this->gravity.x = x;
    this->gravity.y = y;
    this->gravity.z = z;
}

void PhysicsWorld::updatePhysics(GameNode * rootNode) {
//    GameNodeList::Iterator * i = rootNode->childNodeIterator();
//    while (i->hasNext()) {
//        GameNode * node = i->next();
    for (GameNodeList::iterator i = rootNode->getChildren()->begin(); i != rootNode->getChildren()->end(); ++i)
        if ((*i)->hasPhysicsBody()) {
            this->applyGravityTo(*i);
            (*i)->physicsBody()->updatePhysics(this);
        }
}

const double spf = 0.0167;
float getCurrentFramerate() {
    return spf;
}

void PhysicsWorld::applyGravityTo(GameNode * node) {
    if (node->didCollideThisTurn())
        return;
    if (node->physicsBody()->type() == Dynamic && node->physicsBody()->isEffectedByGravity()) {
        Transform * t = node->getTransform();

        
        
        float mass = node->getTransform()->mass();
        float framerate = getCurrentFramerate();
        
//        GameNode * floor = node->rootNode()->getChildWithName("floor");
//        float ground = t->scale().y / 2;
//        if (floor != nullptr) {
//            ground += floor->collisionBody()->boundingBox()->top();
//            if (t->position().y <= ground) {
//                t->setPosition(0, ground, 0);// setM(3 * 4 + 1, ground);
////                return;
//            }
//        }
        
        t->physicsBody()->applyForce( framerate * mass, this->gravity);
    }
}


void PhysicsWorld::buildCollisionList(GameNode * rootNode) {
    
    this->staticBodies = new List();
    this->dynamicBodies = new List();
    this->kinematicBodies = new List();
    for (GameNodeList::iterator i = rootNode->getChildren()->begin(); i != rootNode->getChildren()->end(); ++i) {
        GameNode * node = *i;
        if (node->hasPhysicsBody()) {
            if (node->collisionBody()->CollisionGroup() != NO_COLLISIONS)
                switch (node->physicsBody()->type()) {
                    case Dynamic:
                        this->dynamicBodies->emplace_front(node->collisionBody());
                        break;
                    case Static:
                        this->staticBodies->emplace_front(node->collisionBody());
                        break;
                    case Kinematic:
                        this->kinematicBodies->emplace_front(node->collisionBody());
                        break;
                    default:
                        break;
                }
        }
    }
}

void PhysicsWorld::updateCollisionEvents(GameNode * rootNode) {
    
    
    this->buildCollisionList(rootNode);
    
    
    if (!dynamicBodies->empty()) {
        if (!staticBodies->empty())
            checkForStaticCollisions(dynamicBodies, staticBodies);
        checkForDynamicCollisions(dynamicBodies);
        //        count = checks = 0;
        //			swapLists();
    }
    
    delete this->staticBodies;//.clear();
    delete this->dynamicBodies;
    delete this->kinematicBodies;
    
}


void PhysicsWorld::checkForStaticCollisions(List * dynamic, List * staticBodies) {
    for (List::iterator si = staticBodies->begin(); si != staticBodies->end(); ++si) {
        CollisionBody * staticBody = (*si);
        for (List::iterator di = dynamic->begin(); di != dynamic->end(); ++di)  {
            CollisionBody * dynamicBody = (*di);
            //            checks++;
            if (this->checkForCollision(staticBody,dynamicBody)) {
                //                count++;
                
                //					di.remove();
            }
        }
    }
}

//int count = 0; int checks = 0;
void PhysicsWorld::checkForDynamicCollisions(List * dynamic) {
    CollisionBody * A = dynamic->front();// removeFirst();
    dynamic->remove(A);
    for (List::iterator di = dynamic->begin(); di != dynamic->end(); ++di) {
        CollisionBody * B = (*di);
        //        checks++;
        if (this->checkForCollision(A,B)) {
            //            count++;
            //					if (unchecked.remove(A))
            //						System.err.println(A.uniqueName() + " removed twie");//checked.addLast(A);
            //            if (
            dynamic->remove(B);
            //                == null)
            //                cout << "WARNING: " << B->uniqueName() << " was not removed from unchecked" << endl;
            //            else
            //                cout << "SUCCESS: " << B->uniqueName() << " was removed from unchecked" << endl;
            if (!dynamic->empty()) {
                this->checkForDynamicCollisions(dynamic);
                return;
            }
        }
    }
    if (!dynamic->empty()) {
        this->checkForDynamicCollisions(dynamic);
    }
}
const static unsigned int secureKey = rand() % 100;
bool PhysicsWorld::checkForCollision(CollisionBody * A, CollisionBody * B) {
    if (A == B)
        return false;
    if (A->getCollisionGroup() != B->getCollisionGroup())
        if (A->getCollisionGroup() != EXCLUSIVE_COLLISION_GROUP &&
            B->getCollisionGroup() != EXCLUSIVE_COLLISION_GROUP)
            return false;
    
    switch (A->getCollisionGroup()) {
        case NO_COLLISIONS:
        case EXCLUSIVE_COLLISION_GROUP:
            return false;
    }
    
    
    bool isHit = A->intersects(B);
    if (isHit) {
        CollisionEvent * e = new CollisionEvent(A->getNode(),B->getNode(),secureKey);
        if (collisionDelegate != nullptr)
            collisionDelegate->handleCollision(A->getNode(), B->getNode(), e);
        e->processCollision(secureKey);
        delete e;
    } 
    return isHit;			
    
}




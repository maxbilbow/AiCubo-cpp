//
//  CollisionEvent.cpp
//  RMXKit
//
//  Created by Max Bilbow on 26/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#import "Includes.h"


//
#import "NodeComponent.hpp"

#import "Transform.hpp"
#import "CollisionBody.hpp"
#import "PhysicsBody.hpp"
#import "BoundingBox.hpp"
#import "BoundingSphere.hpp"
#import "GameNode.hpp"
#include "CollisionEvent.hpp"


using namespace rmx;
using namespace std;


CollisionEvent::CollisionEvent(GameNode * nodeA, GameNode * nodeB) {
//    _log = "\nNew Collision Event: " + _nodeA->uniqueName() + " vs. " + _nodeB->uniqueName();
    _nodeA = nodeA;
    _nodeB = nodeB;
    _hitPointA = GLKVector3Make(0,0,0);
    _hitPointB = GLKVector3Make(0,0,0);
    Transform * A = nodeA->getTransform();//.rootTransform();
    Transform * B = nodeB->getTransform();//.rootTransform();
    
       
    Vector3 posA = A->localPosition();
    Vector3 posB = B->localPosition();
//    _log += "\n        Pos A: " + to_string(posA.x) ;
//    _log += "\n        Pos B: " + to_string(posB.x) ;
    _AtoB = posB - posA;
    _dist = GLKVector3Distance( A->localPosition() ,B->localPosition());
    if (isnan(_dist)) {
        cout << A->localPosition() << ", " << B->localPosition() << endl;
        throw invalid_argument("NOT A NUMBER");
    }
    
    this->seperateBodies(A,B);
    
    
    this->processMomentum(A,B);

    nodeA->BroadcastMessage("onCollision", this);
    nodeB->BroadcastMessage("onCollision", this);
}

void CollisionEvent::seperateBodies(Transform * A, Transform * B) {
    //apply force relative to overlapping areas
    float min;
    
    
    min = _nodeA->collisionBody()->boundingSphere()->radius() + _nodeB->collisionBody()->boundingSphere()->radius();
    
//    _log += "\n       A to B: " + _AtoB.x ;
    
    const float delta = min - _dist / 2;
//    _log += "\n     Distance: " + _dist + " < " + min + ", delta == " + delta;
    if (_dist > min || _dist < 0)
        throw invalid_argument("Distance" + to_string(_dist) + " should be less than min: " + to_string(min) + "\n");
        //			System.err.println("Distance" + dist + " should be less than min: " + min);
        
    Vector3 AtoB = _AtoB;// * -delta;//.normalize();
//    AtoB = Aiscale(-delta);
        if (isZero(AtoB)) {
            AtoB.x = -min;//TODO: normalize again.
        }
    Vector3 posA = A->localPosition(); Vector3 posB = B->localPosition();

    BoundingBox * boxA = _nodeA->collisionBody()->boundingBox(); BoundingBox * boxB = _nodeB->collisionBody()->boundingBox();
    float dx  = boxA->xMax() + posA.x - boxB->xMin() - posB.x;//Math.abs(AtoB.x);
    float dy  = boxA->yMax() + posA.y - boxB->yMin() - posB.y;//Math.abs(AtoB.y);
    float dz  = boxA->zMax() + posA.z - boxB->zMin() - posB.z;// Math.abs(AtoB.z);
    float dx2 = boxB->xMax() + posB.x - boxA->xMin() - posA.x;//Math.abs(AtoB.x);
    float dy2 = boxB->yMax() + posB.y - boxA->yMin() - posA.y;//Math.abs(AtoB.y);
    float dz2 = boxB->zMax() + posB.z - boxA->zMin() - posA.z;// Math.abs(AtoB.z);
    string axis = "x"; float diff = dx;
    
    if (dx2 < diff) {
        axis = "x";
        diff = dx2;
    }
    if (dy < diff) {
        axis = "y";
        diff = dy;
    }
    if (dy2 < diff) {
        axis = "y";
        diff = dy2;
    }
    if (dz < diff) {
        axis = "z";
        diff = dz;
    }
    if (dz2 < diff) {
        axis = "z";
        diff = dz2;
    }
    cout << axis << ": " << diff << endl;
    
//    if (dy < dx && dy < dz) {
//        axis = "y";
//        cout << dy << " vs " << dy2 << endl;
//        diff = dy;
//    }else if (dx < dy && dx < dz) {
//        axis = "x";
//        cout << dx << " vs " << dx2 << endl;
//        diff = dx;
//    }else {
//        axis = "z";
//        cout << dz << " vs " << dz2 << endl;
//        diff = dz;
//    }
   
  
    
    
    CollisionBody * bodyA = A->physicsBody()->collisionBody();
    CollisionBody * bodyB = B->physicsBody()->collisionBody();
    newCollision = !bodyA->contacts->contains(bodyB);

    
    
    if (A->physicsBody()->type() == Dynamic && A->position() != A->rootTransform()->lastPosition())
        A->getNode()->getTransform()->rootTransform()->stepBack(axis);
    if (B->physicsBody()->type() == Dynamic && B->position() != B->rootTransform()->lastPosition())
        B->getNode()->getTransform()->rootTransform()->stepBack(axis);
    
    if (bodyA->intersects(bodyB) ){
//        if (newCollision) {
//            bodyA->contacts->append(B);
//            bodyB->contacts->append(A);
//        }
        float time = 0.167;// RMX.getCurrentFramerate();
        float escapeForce = time;// GLKVector3Length(_AtoB);
        Vector3 dir = //AtoB.getNormalized();
        GLKVector3Make(
                       axis == "x" ? 1 : 0,
                       axis == "y" ? 1 : 0,
                       axis == "z" ? 1 : 0
                       );
        A->physicsBody()->applyForce(escapeForce * A->mass(), dir, _hitPointA);//.translate(AtoB);
        
        //        _log += "\n Translating B: " + AtoB;
        B->physicsBody()->applyForce(-escapeForce * B->mass(), dir, _hitPointB);//translate(AtoB);
    }
    
    
}


void CollisionEvent::finishUp(CollisionBody * A, CollisionBody * B) {
    

    
    //		if (A.position().getDistanceTo(B.position()) < min) {
    
}
void CollisionEvent::processMomentum(Transform * A, Transform * B)  {
    
//    _log += "\n\nCollision Momentum Report: " + nodeA.uniqueName() + " vs. " + nodeB.uniqueName();
    
    Vector3 Va = A->physicsBody()->getVelocity();
    Vector3 Vb = B->physicsBody()->getVelocity();
    Vector3 direction = Va - Vb;
    if (isZero(direction))
        return;
    else
        GLKVector3Normalize(direction);
    
    float m1 = A->mass();
    float m2 = B->mass();
    
    //		float res = (1 - A.node.physicsBody().getRestitution()) * (1 - B.node.physicsBody().getRestitution());
    //		float resA = 1 - A.node.physicsBody().getRestitution();
    //		float resB = 1 - B.node.physicsBody().getRestitution();
    
    
    
    
    float lossA = 1 - A->physicsBody()->getRestitution();
    float lossB = 1 - B->physicsBody()->getRestitution();
    float v1 = GLKVector3Length(Va);
    float v2 = GLKVector3Length(Vb);
    
    float mass = m1 + m2 + 0.01f;
    float diffMass = m1 - m2;
    float forceOnA = -m2;// (diffMass * v1 + 2 * m2 * v2 ) / mass;
    
    float forceOnB = m1;//(2 * m1 * v1 - diffMass * v2 ) / mass;
    
    //Transfer of forces
    
    A->physicsBody()->applyForce( forceOnA * lossA , direction, _hitPointA);
    B->physicsBody()->applyForce( forceOnB * lossB , direction, _hitPointB);
    
    //Loss of energy
    //				nodeA.physicsBody().applyForce(-m1 * lossA, direction, hitPointA);
    //				nodeA.physicsBody().applyForce(-m2 * lossB, direction, hitPointA);
    
    
    //		System.out.println(_log);
    //System.out.println("Velocities: " +
    //				"\n     "+ nodeA.uniqueName() + ": " + va + nodeB.uniqueName() + ": " + vb);
}
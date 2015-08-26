//
//  PhysicsBody.hpp
//  RMXKit
//
//  Created by Max Bilbow on 20/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef PhysicsBody_hpp
#define PhysicsBody_hpp

#include <stdio.h>

#endif /* PhysicsBody_hpp */




namespace rmx {
    enum PhysicsBodyType {
        Static, Dynamic, Kinematic, Transient
    };

    class PhysicsBody : public NodeComponent {
        float mass = 1,
        restitution = 0.2,
        friction = 0.1,
        rollingFriction = 0.5,
        damping = 0.2,
        rotationalDamping = 0.1;
        CollisionBody * _collisionBody;
        PhysicsBodyType _type;
        GLKVector3 forces, torque, velocity, rotationalVelocity;
    public:
        PhysicsBodyType type();
        void setType(PhysicsBodyType type);
        PhysicsBody();
        void setMass(float mass);

        float getMass();
        
        float TotalMass();
    
        CollisionBody * collisionBody();
        
        GameNode * setNode(GameNode * node) override;
        
        
        void applyForce(float force, Vector3 direction, Vector3 atPoint = GLKVector3Make(0,0,0));
        
        void applyTorque(float force, Vector3 axis, Vector3 atPoint = GLKVector3Make(0,0,0));
        
        Vector3 getVelocity();
        float getRestitution();
        void setRestitution(float);
        
        void updatePhysics(PhysicsWorld *);
        
        static PhysicsBody * newStaticBody();
        
        static PhysicsBody * newDynamicBody();
        
        static PhysicsBody * newKinematicBody();
        
        static PhysicsBody * newTransientBody();

    };
}
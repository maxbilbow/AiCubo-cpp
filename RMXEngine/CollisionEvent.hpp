//
//  CollisionEvent.hpp
//  RMXKit
//
//  Created by Max Bilbow on 26/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef CollisionEvent_hpp
#define CollisionEvent_hpp

#include <stdio.h>

#endif /* CollisionEvent_hpp */


namespace rmx {
    class CollisionEvent : public Object {
        bool newCollision = false;
        GameNode * _nodeA, * _nodeB;
        Vector3 _hitPointA, _hitPointB, _AtoB;
        float _dist;
//        std::string _log;
        void seperateBodies(Transform * A, Transform * B);
        void processMomentum(Transform * A, Transform * B);
        void finishUp(CollisionBody * A,  CollisionBody * B);
    public:
        CollisionEvent(GameNode * nodeA, GameNode * nodeB);
        
    };
}
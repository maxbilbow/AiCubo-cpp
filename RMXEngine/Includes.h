//
//  Includes.h
//  RMXKit
//
//  Created by Max Bilbow on 20/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef Includes_h
#define Includes_h






//typedef int BOOL;
#define TRUE 1
#define FALSE 0


#include "RMXKit.h"
#include "RMXMath.h"
#include "RMXKeyStates.h"


typedef long GLWindow;

namespace rmx {
    class Transform;
    class GameNode;
    class Behaviour;
    class SpriteBehaviour;
    class Geometry;
    class NodeComponent;
    class PhysicsBody;
    class Camera;
    class Scene;
    class PhysicsWorld;
    class GameView;
    class Floor;
    class Cube;
    class RenderDelegate;
    class GameController;
    class CollisionBody;
    class CollisionEvent;
    class BoundingBox;
    class BoundingSphere;
    class Bugger;
//    typedef Dictionary<std::string, NodeComponent> GameNodeComponents;
    typedef std::map<std::string, NodeComponent*> GameNodeComponents;
//    typedef LinkedList<Behaviour> GameNodeBehaviours;
//    typedef LinkedList<GameNode> GameNodeList;set<GameNode*>
    typedef std::set<Behaviour*>  GameNodeBehaviours;
    typedef std::set<GameNode*> GameNodeList;
}

enum RMXMessage {
    Forward, Left, Up, X, Y, Z,
    Pitch, Yaw, Roll,
    Jump
};

#endif /* Includes_h */
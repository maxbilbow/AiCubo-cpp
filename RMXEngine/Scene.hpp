//
//  Scene.hpp
//  RMXKit
//
//  Created by Max Bilbow on 19/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>

#endif /* Scene_hpp */

#ifndef GameNode_hpp
#import "GameNode.hpp"
#endif

#ifndef NodeComponent_hpp
#import "NodeComponent.hpp"
#endif

#ifndef Camera_hpp
#import "Camera.hpp"
#endif

#ifndef PhysicsWorld_hpp
#import "PhysicsWorld.hpp"
#endif


namespace rmx {

    class Scene : public Object, public Unfinised {
        static Scene * _current;
        GameNode * _rootNode =   null;
        PhysicsWorld * _physicsWorld = new PhysicsWorld();

    public:
        Scene();
        GameNode * rootNode();
        static Scene * getCurrent();
        static Scene * setCurrent(Scene * scene);
        void updateSceneLogic();
        void renderScene(Camera * camera);
        
        void setAsCurrent();
    };

}
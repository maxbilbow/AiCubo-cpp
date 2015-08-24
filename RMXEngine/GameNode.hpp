//
//  Node.h
//  RMXKit
//
//  Created by Max Bilbow on 18/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef GameNode_hpp
#define GameNode_hpp

#include <stdio.h>
//#import <iostream>
#endif /* Node_h */


namespace rmx {
   
   
    
    class GameNode : public Object { //, public _Node {
   
    protected:
        GameNode * parent = null;
    private:
        static GameNode * _current;
        
        
        
        Transform * _transform = null;
        
        BOOL _hasCamera = FALSE;
        Camera * camera = null;
        
        BOOL _hasPhysicsBody = FALSE;
        PhysicsBody * _physicsBody = null;
        
        BOOL _hasGeometry = FALSE;
        Geometry * _geometry = null;
        
        GameNodeList children = GameNodeList();
        
        GameNodeComponents components __deprecated_enum_msg("Avoid using until safer key-value mapping implemented") = GameNodeComponents();
        
        GameNodeBehaviours * behaviours = new GameNodeBehaviours();

    protected:
        void onLoad();
        virtual void afterLoad(){}
    public:
        GameNode();
        GameNode(std::string name);
        
        

        void setTransform(Transform * transform);
        
        Transform * getTransform();
        
        static void setCurrent(GameNode * node);
        
        static GameNode * getCurrent();
        
        
        
    //    template <class T = NodeComponent>
        NodeComponent * setComponent(NodeComponent * component) __deprecated_enum_msg("Avoid using until safer key-value mapping implemented");
        
        void addBehaviour(Behaviour * behaviour);
       
        NodeComponent * getComponent(std::string className)  __deprecated_enum_msg("Do not use until better keyvalue list implemented");
        

        
        
        GameNodeList * getChildren();
        
        virtual void addChild(GameNode * child);
        bool removeChildNode(GameNode * node);
        
        GameNode * getChildWithName(std::string name);
        
        
        
        
        Camera * getCamera();
        
        bool hasCamera();
        void setCamera(Camera * camera);
        
//        static GameNode * newCameraNode();
        
        
        Geometry * geometry();
        
        
        bool hasGeometry();
        void setGeometry(Geometry * geometry);
        
        PhysicsBody * physicsBody();
        
        bool hasPhysicsBody();
        void setPhysicsBody(PhysicsBody * body);
        
        void updateLogic();
        
        void draw(Matrix4 rootTransform);
        
        
        
        
        
        GameNode * getParent();
        
        void setParent(GameNode * parent);
        
        static GameNode * makeCube(float s,bool body, Behaviour * b);
        
        void addToCurrentScene();

        void SendMessage(std::string message, void * args =   null, SendMessageOptions options = DoesNotRequireReceiver) override;
        void BroadcastMessage(std::string message, void * args =   null, SendMessageOptions options = DoesNotRequireReceiver) override;
        
        static void test();
    };
    
    

}
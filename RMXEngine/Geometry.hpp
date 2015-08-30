//
//  Geometry.hpp
//  RMXKit
//
//  Created by Max Bilbow on 19/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef Geometry_hpp
#define Geometry_hpp

#include <stdio.h>

#endif /* Geometry_hpp */


namespace rmx {
 
    class Geometry : public NodeComponent {
        static Geometry * _cube;
        //
        int _size = 0, _count = 0;
        bool vertexMode = FALSE;
        void pushMatrix(GameNode *, Matrix4);
        void popMatrix();
    protected:
        virtual void drawWithScale(float x, float y, float z) {
             throw std::invalid_argument("drawWithScale(float x, float y, float z) must be overriden");
        }
    public:
        float * vertexData;// = nullptr, * _indexData = nullptr;
        long vertexCount;
        bool isVertexMode();
        void setVertexMode(bool vertexMode);
        void render(GameNode * GameNode, Matrix4 root);
        
        static Geometry * Cube();
        
//        int * vertexData();
//        int * indexData();
        
        Geometry(float * vertexData, long count);
        void addVertex(Vector3 v);
        
        void addVertex(float x, float y, float z);
        void prepare();
        
        
        Matrix4 modelMatrix();
    };
    
    

    class Floor : public Geometry {
        
    protected:
        void drawWithScale(float x, float y, float z) override;
    public:
        Floor():Geometry(nullptr,0){}
        
    };

}
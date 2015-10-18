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
       
        float * _vertexData;
        long _vertexDataSize;
        unsigned short * _indexData;
        long  _indexDataSize;
        void pushMatrix(GameNode *, Matrix4);
        void popMatrix();
        Vector4 _color;
    protected:
        virtual void drawWithScale(float x, float y, float z) {
             throw std::invalid_argument("drawWithScale(float x, float y, float z) must be overriden");
        }
        Geometry();
    public:
        float * vertexData();// = nullptr, * _indexData = nullptr;
        long vertexDataSize();
        unsigned short * indexData();
        long indexDataSize();
        bool isVertexMode();
        void setVertexMode(bool vertexMode);
        void render(GameNode * GameNode, Matrix4 root);
        Vector3 scale();
        Vector4 color();
        void setColor(float,float,float,float=1.0);
        static Geometry * Cube();
        
//        int * vertexData();
//        int * indexData();
//
        Geometry(float*,long, unsigned short *, long);
        void addVertex(Vector3 v);
        
        void addVertex(float x, float y, float z);
        void prepare();
        
        virtual std::string ClassName() override {
            return "rmx::Geometry";
        }
        Matrix4 modelMatrix();
    };
    
    
    
    class Floor : public Geometry {
        
    protected:
        void drawWithScale(float x, float y, float z) override;
    public:
        Floor():Geometry(nullptr,0,nullptr,0){}
        virtual std::string ClassName() override {
            return "rmx::Floor(ext Geometry";
        }
    };
    
    

}

//    typedef rmx::Geometry RMXGeometry;

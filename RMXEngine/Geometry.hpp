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

static const BOOL VERTEX_MODE = FALSE;
struct Vertex
{
    Vertex() {
        x=y=z=r=g=b=0;
    }
    Vertex(float x, float y, float z, float r, float g, float b) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->r = r;
        this->g = g;
        this->b = b;
    }
    
    GLfloat x, y, z;
    GLfloat r, g, b;
};

namespace rmx {
 
    class Geometry{
        static Geometry * _cube;
        Vertex * _vertexData = null;
        GLuint * _indexData = null;
        int _numberOfVertices = 0, _count = 0;
        
        void pushMatrix(GameNode *, Matrix4);
        void popMatrix();
    protected:
        virtual void drawWithScale(float x, float y, float z)
        {
            throw std::invalid_argument("drawWithScale(float x, float y, float z) must be overriden");
        }
    public:
        bool isVertexMode();
        void setVertexMode(bool vertexMode);
        void render(GameNode * GameNode, Matrix4 root);
        
        Geometry();
        Geometry(int numberOfVertices);
        static Geometry * Cube();
        
        Vertex * vertexData();
        GLuint * indexData();
        
       
        void addVertex(Vertex v);
        
        void addVertex(float x, float y, float z, float r, float g, float b);
        void prepare();
        
        
    
    };
    
    

    class Floor : public Geometry {
        
    protected:
        void drawWithScale(float x, float y, float z) override;
    public:
        Floor():Geometry(4*9) {}
        
    };

}
//
//  Geometry.cpp
//  RMXKit
//
//  Created by Max Bilbow on 19/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#import "Includes.h"
#import "GameNode.hpp"
#import "NodeComponent.hpp"
#import "Transform.hpp"
#ifdef GLFW
#import "glfw3.h"
#endif
#import "Geometry.hpp"


using namespace rmx;
using namespace std;

void Floor::drawWithScale(float x, float y, float z) {
#ifdef GLFW
    float inf = 99999;//Float.POSITIVE_INFINITY;
    glBegin(GL_POLYGON);
    glColor3f(0.8f,0.8f,0.8f);
    glVertex3f( inf, -y,-inf);
    glVertex3f(-inf, -y,-inf);
    glVertex3f(-inf, -y, inf);
    glVertex3f( inf, -y, inf);
    glEnd();
#endif
}

//private ByteBuffer _elements;
//private ShortBuffer _indexData;
//private int _e = 0;
Geometry::Geometry(int size) {
    _vertexData = new int[sizeof(int) * size];
    _indexData = new int[sizeof(int) * size / 3];
}

int * Geometry::vertexData() {
    return _vertexData;
}

int * Geometry::indexData() {
    return _indexData;
}
void Geometry::addVertex(Vector3 v) {
    this->addVertex(v.x, v.y, v.z);
}

void Geometry::addVertex(float x, float y, float z)  {
    if (_count >= _size)
        throw new invalid_argument("ERROR: TOO MANY VERTICES");
    _vertexData[_count++] = x;
    _vertexData[_count++] = y;
    _vertexData[_count++] = z;
    
}



void Geometry::render(GameNode * node, Matrix4 base) {
    
#ifdef GLFW
    
    Matrix4 model = node->getTransform()->worldMatrix();
    
    EulerAngles modelA = node->getTransform()->localEulerAngles();
    
    glPushMatrix();
    
    glTranslatef(
                 model.m30 + base.m30,
                 model.m31 + base.m31,
                 model.m32 + base.m32
                 );
    
    glRotatef(modelA.x, 1,0,0);
    glRotatef(modelA.y, 0,1,0);
    glRotatef(modelA.z, 0,0,1);

    

    float X = node->getTransform()->scale().x;
    float Y = node->getTransform()->scale().y;
    float Z = node->getTransform()->scale().z;
    drawWithScale(X, Y, Z);
    
    
    glPopMatrix();
#endif
}

void _render() {
    //this.pushMatrx();
    //		glVertex3dv(_elements);
    //glColor3f(0.0f,0.0f,1.0f);
    //glDrawElements(GL_QUADS, _elements);
    //this.popMatrix();
}



    /*Bugger.logAndPrint("Cube with " + 6*3*4 + " elements", true);
     _cube = new Geometry(6 * 3 * 4);
     _cube.addVertex( 1.0f, 1.0f,-1.0f);
     _cube.addVertex(-1.0f, 1.0f,-1.0f);
     _cube.addVertex(-1.0f, 1.0f, 1.0f);
     _cube.addVertex( 1.0f, 1.0f, 1.0f);
     //            glColor3f(1.0f,0.5f,0.0f);
     _cube.addVertex( 1.0f,-1.0f, 1.0f);
     _cube.addVertex(-1.0f,-1.0f, 1.0f);
     _cube.addVertex(-1.0f,-1.0f,-1.0f);
     _cube.addVertex( 1.0f,-1.0f,-1.0f);
     //            glColor3f(1.0f,0.0f,0.0f);
     _cube.addVertex( 1.0f, 1.0f, 1.0f);
     _cube.addVertex(-1.0f, 1.0f, 1.0f);
     _cube.addVertex(-1.0f,-1.0f, 1.0f);
     _cube.addVertex( 1.0f,-1.0f, 1.0f);
     //            glColor3f(1.0f,1.0f,0.0f);
     _cube.addVertex( 1.0f,-1.0f,-1.0f);
     _cube.addVertex(-1.0f,-1.0f,-1.0f);
     _cube.addVertex(-1.0f, 1.0f,-1.0f);
     _cube.addVertex( 1.0f, 1.0f,-1.0f);
     //            glColor3f(0.0f,0.0f,1.0f);
     _cube.addVertex(-1.0f, 1.0f, 1.0f);
     _cube.addVertex(-1.0f, 1.0f,-1.0f);
     _cube.addVertex(-1.0f,-1.0f,-1.0f);
     _cube.addVertex(-1.0f,-1.0f, 1.0f);
     //            glColor3f(1.0f,0.0f,1.0f);
     _cube.addVertex( 1.0f, 1.0f,-1.0f);
     _cube.addVertex( 1.0f, 1.0f, 1.0f);
     _cube.addVertex( 1.0f,-1.0f, 1.0f);
     _cube.addVertex( 1.0f,-1.0f,-1.0f);
     _cube.prepare();
     }*/
//    return _cube;
//}

class ACube : public Geometry {

public:
    ACube():Geometry(6*3*4){}
protected:
#ifdef GLFW
    void drawWithScale(float X, float Y, float Z)override {
        
        glBegin(GL_QUADS);
        glColor3f(1.0f,1.0f,0.0f);
        glNormal3f(0,1,0);
        glVertex3f( X, Y,-Z);
        glVertex3f(-X, Y,-Z);
        glVertex3f(-X, Y, Z);
        glVertex3f( X, Y, Z);
        glColor3f(1.0f,0.5f,0.0f);
        glNormal3f(0,-1,0);
        glVertex3f( X,-Y, Z);
        glVertex3f(-X,-Y, Z);
        glVertex3f(-X,-Y,-Z);
        glVertex3f( X,-Y,-Z);
        glColor3f(1.0f,0.0f,0.0f);
        glNormal3f(0,0,1);
        glVertex3f( X, Y, Z);
        glVertex3f(-X, Y, Z);
        glVertex3f(-X,-Y, Z);
        glVertex3f( X,-Y, Z);
        glColor3f(1.0f,1.0f,0.0f);
        glNormal3f(0,0,-1);
        glVertex3f( X,-Y,-Z);
        glVertex3f(-X,-Y,-Z);
        glVertex3f(-X, Y,-Z);
        glVertex3f( X, Y,-Z);
        glColor3f(0.0f,0.0f,1.0f);
        glNormal3f(-1,0,0);
        glVertex3f(-X, Y, Z);
        glVertex3f(-X, Y,-Z);
        glVertex3f(-X,-Y,-Z);
        glVertex3f(-X,-Y, Z);
        glColor3f(1.0f,0.0f,1.0f);
        glNormal3f(1,0,0);
        glVertex3f( X, Y,-Z);
        glVertex3f( X, Y, Z);
        glVertex3f( X,-Y, Z);
        glVertex3f( X,-Y,-Z);
        glEnd();
    }
#endif
};

Geometry * Geometry::_cube = nullptr;
Geometry * Geometry::Cube() {
    if (_cube ==   nullptr)
        _cube = new ACube();
    return _cube;
}





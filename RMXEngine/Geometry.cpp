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
#import "glfw3.h"
#import "Geometry.hpp"


using namespace rmx;
using namespace std;

void Floor::drawWithScale(float x, float y, float z) {
    float inf = 99999;//Float.POSITIVE_INFINITY;
    glBegin(GL_POLYGON);
    glColor3f(0.8f,0.8f,0.8f);
    glVertex3f( inf, -y,-inf);
    glVertex3f(-inf, -y,-inf);
    glVertex3f(-inf, -y, inf);
    glVertex3f( inf, -y, inf);
    glEnd();
}

//private ByteBuffer _elements;
//private ShortBuffer _indexData;
//private int _e = 0;
Geometry::Geometry(int numberOfVertices) {
    _vertexData = new Vertex[sizeof(Vertex) * numberOfVertices];
    _indexData = new GLuint[sizeof(Vertex) * numberOfVertices / 3];
    _numberOfVertices = numberOfVertices;
//    this->vertexMode = true;
}

Geometry::Geometry() {
//    this->vertexMode = false;
}

Vertex * Geometry::vertexData() {
    return _vertexData;
}

GLuint * Geometry::indexData() {
    return _indexData;
}
void Geometry::addVertex(float x, float y, float z, float r, float g, float b) {
    this->addVertex(Vertex(x,y,z,r,b,g));
}
void Geometry::addVertex(Vertex v)  {
    if (_count >= _numberOfVertices)
        throw new invalid_argument("ERROR: TOO MANY VERTICES");
    _vertexData[_count++] = v;
}


void Geometry::pushMatrix(GameNode * node, Matrix4 base) {
    Matrix4 model = node->getTransform()->worldMatrix() * base;

    EulerAngles modelA = RMXMatrix3MakeEuler(model);
//    modelA /= PI_OVER_180;
    
    glPushMatrix();

//    glMultMatrixf(model.m);
    glTranslatef(
                 model.m30 + base.m30,
                 model.m31 + base.m31,
                 model.m32 + base.m32
                 );
    

    glRotatef(modelA.x, 1,0,0);
    glRotatef(modelA.y, 0,1,0);
    glRotatef(modelA.z, 0,0,1);

    
}



void Geometry::popMatrix() {
    //		 glDisable(GL_TEXTURE_2D);//TODO perhaps?
    
    glPopMatrix();
}


void Geometry::render(GameNode * node, Matrix4 rootTransform)
{
    this->pushMatrix(node, rootTransform);
    float X = node->getTransform()->scale().x;
    float Y = node->getTransform()->scale().y;
    float Z = node->getTransform()->scale().z;
    if (VERTEX_MODE) {
        glVertexPointer(3, GL_FLOAT, sizeof(Vertex), _vertexData);
        glColorPointer(3, GL_FLOAT, sizeof(Vertex), &_vertexData[0].r); // Pointer to the first color
        glPointSize(2.0);
        glDrawElements(GL_QUADS, _numberOfVertices * sizeof(Vertex), GL_UNSIGNED_INT, _indexData);
    } else
        this->drawWithScale(X, Y, Z);
    
    this->popMatrix();
}

void _render() {
    //this.pushMatrx();
    //		glVertex3dv(_elements);
    //glColor3f(0.0f,0.0f,1.0f);
    //glDrawElements(GL_QUADS, _elements);
    //this.popMatrix();
}




class ACube : public Geometry
{
public:
    ACube():Geometry(6*3*4){}
protected:
    void drawWithScale(float X, float Y, float Z)override
    {
        glBegin(GL_QUADS);
        glColor3f(1.0f,1.0f,0.0f);
        glVertex3f( X, Y,-Z);
        glVertex3f(-X, Y,-Z);
        glVertex3f(-X, Y, Z);
        glVertex3f( X, Y, Z);
        glColor3f(1.0f,0.5f,0.0f);
        glVertex3f( X,-Y, Z);
        glVertex3f(-X,-Y, Z);
        glVertex3f(-X,-Y,-Z);
        glVertex3f( X,-Y,-Z);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f( X, Y, Z);
        glVertex3f(-X, Y, Z);
        glVertex3f(-X,-Y, Z);
        glVertex3f( X,-Y, Z);
        glColor3f(1.0f,1.0f,0.0f);
        glVertex3f( X,-Y,-Z);
        glVertex3f(-X,-Y,-Z);
        glVertex3f(-X, Y,-Z);
        glVertex3f( X, Y,-Z);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(-X, Y, Z);
        glVertex3f(-X, Y,-Z);
        glVertex3f(-X,-Y,-Z);
        glVertex3f(-X,-Y, Z);
        glColor3f(1.0f,0.0f,1.0f);
        glVertex3f( X, Y,-Z);
        glVertex3f( X, Y, Z);
        glVertex3f( X,-Y, Z);
        glVertex3f( X,-Y,-Z);
        glEnd();
    }

};


Geometry * MakeVertexCube()
{
    Geometry _cube = ACube();//Geometry(6 * 3 * 4);
    _cube.addVertex( 1.0f, 1.0f,-1.0f, 1.0f,0.5f,0.0f);
    _cube.addVertex(-1.0f, 1.0f,-1.0f, 1.0f,0.5f,0.0f);
    _cube.addVertex(-1.0f, 1.0f, 1.0f, 1.0f,0.5f,0.0f);
    _cube.addVertex( 1.0f, 1.0f, 1.0f, 1.0f,0.5f,0.0f);
    
    _cube.addVertex( 1.0f,-1.0f, 1.0f, 1.0f,0.0f,0.0f);
    _cube.addVertex(-1.0f,-1.0f, 1.0f, 1.0f,0.0f,0.0f);
    _cube.addVertex(-1.0f,-1.0f,-1.0f, 1.0f,0.0f,0.0f);
    _cube.addVertex( 1.0f,-1.0f,-1.0f, 1.0f,0.0f,0.0f);
    
    _cube.addVertex( 1.0f, 1.0f, 1.0f, 1.0f,0.0f,0.0f);
    _cube.addVertex(-1.0f, 1.0f, 1.0f, 1.0f,0.0f,0.0f);
    _cube.addVertex(-1.0f,-1.0f, 1.0f, 1.0f,0.0f,0.0f);
    _cube.addVertex( 1.0f,-1.0f, 1.0f, 1.0f,0.0f,0.0f);
    
    _cube.addVertex( 1.0f,-1.0f,-1.0f, 1.0f,1.0f,0.0f);
    _cube.addVertex(-1.0f,-1.0f,-1.0f, 1.0f,1.0f,0.0f);
    _cube.addVertex(-1.0f, 1.0f,-1.0f, 1.0f,1.0f,0.0f);
    _cube.addVertex( 1.0f, 1.0f,-1.0f, 1.0f,1.0f,0.0f);
    
    _cube.addVertex(-1.0f, 1.0f, 1.0f, 0.0f,0.0f,1.0f);
    _cube.addVertex(-1.0f, 1.0f,-1.0f, 0.0f,0.0f,1.0f);
    _cube.addVertex(-1.0f,-1.0f,-1.0f, 0.0f,0.0f,1.0f);
    _cube.addVertex(-1.0f,-1.0f, 1.0f, 0.0f,0.0f,1.0f);
    
    _cube.addVertex( 1.0f, 1.0f,-1.0f, 1.0f,0.0f,1.0f);
    _cube.addVertex( 1.0f, 1.0f, 1.0f, 1.0f,0.0f,1.0f);
    _cube.addVertex( 1.0f,-1.0f, 1.0f, 1.0f,0.0f,1.0f);
    _cube.addVertex( 1.0f,-1.0f,-1.0f, 1.0f,0.0f,1.0f);
    
    Geometry * g = &_cube;
    return g;
    
}

Geometry * Geometry::_cube = null;
Geometry * Geometry::Cube() {
    if (_cube ==   null)
        _cube = MakeVertexCube();//new ACube();
    return _cube;
}





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

void Geometry::pushMatrix(GameNode * node, Matrix4 baseModelView) {
    
    EulerAngles modelA = node->getTransform()->eulerAngles() / PI_OVER_180;
    
    glPushMatrix();
    
    Matrix4 modelMatrix = GLKMatrix4Multiply(
                                             node->getTransform()->worldMatrix(),
                                             baseModelView
                                             );
    //		 glMultMatrixf(_modelView.buffer())    
    glTranslatef(
                 modelMatrix.m30,
                 modelMatrix.m31,
                 modelMatrix.m32
                 );
    
//    Vector3 m_translation = node->getTransform()->getTransform()->position();
//    glTranslatef(
//                 m_translation.z,
//                 m_translation.y,
//                 m_translation.z
//                 );
    Vector3 euler = RMXMatrix3MakeEuler(modelMatrix);
    glRotatef(euler.x, 1,0,0);
    glRotatef(euler.y, 0,1,0);
    glRotatef(euler.z, 0,0,1);
    
    
}


//	private void enableTexture() {
//		 glEnable(GL_TEXTURE_2D); //Enable texture
////         glBindTexture(GL_TEXTURE_2D,text2D);//Binding texture
//	}

void Geometry::popMatrix() {
    //		 glDisable(GL_TEXTURE_2D);//TODO perhaps?
    
    glPopMatrix();
}
void Geometry::render(GameNode * node, Matrix4 rootTransform) {
    if (vertexMode) {
        cout << "WARNING: Vertex Mode enabled but may not be fully implemented yet." << endl;
        return;
    }
    //		 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //		         glLoadIdentity();
    
    this->pushMatrix(node, rootTransform);
    float X = node->getTransform()->scale().x;
    float Y = node->getTransform()->scale().y;
    float Z = node->getTransform()->scale().z;
    drawWithScale(X, Y, Z);
    
    this->popMatrix();
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
    void drawWithScale(float X, float Y, float Z)override {
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

Geometry * Geometry::_cube = null;
Geometry * Geometry::Cube() {
    if (_cube ==   null)
        _cube = new ACube();
    return _cube;
}





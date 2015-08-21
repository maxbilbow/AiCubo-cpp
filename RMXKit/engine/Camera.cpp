//
//  Camera.cpp
//  RMXKit
//
//  Created by Max Bilbow on 20/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#import "Includes.h"

#import "NodeComponent.hpp"
#import "Transform.hpp"
//#import <GLFW/glfw3.h>
#import "GameView.hpp"
#import "GameNode.hpp"
#import "Camera.hpp"
#import <math.h>


using namespace rmx;
using namespace std;






Camera::Camera() {
    NodeComponent::NodeComponent();
    this->_projectionMatrix = GLKMatrix4Identity;
    this->fovX = 45;
    this->fovY = 45;
    this->nearZ = 1;
    this->farZ = 2000;
    this->aspect = 16.0/9.0f;
    this->setName("Camera");
    
}

float Camera::getFarZ() {
    return farZ;
}

void Camera::setFarZ(float farZ) {
    this->farZ = farZ;
}

float Camera::getFovX() {
    return fovX;
}

void Camera::setFovX(float fovX) {
    this->fovX = fovX;
}

float Camera::getNearZ() {
    return this->nearZ;
}

void Camera::setNearZ(float nearZ) {
    this->nearZ = nearZ;
}

Matrix4 Camera::projectionMatrix() {
    return this->_projectionMatrix;
}
void Camera::makePerspective(GameView * view) {
    aspect = view->width() / view->height();
    double fW, fH;
    
    //fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fH = tan( fovY / 360 * PI ) * nearZ;
    fW = fH * aspect;
    
//    GLKMatrix4MakeFrustum(-fW, fW, -fH, fH, nearZ, farZ );
    
    glFrustum( -fW, fW, -fH, fH, nearZ, farZ );
    
    
    //
    Matrix4 m = this->getNode()->getTransform()->worldMatrix();
    //		 Matrix4 root = Scene.getCurrent().rootNode.transform.localMatrix();
    //		 root.set(m);
    //		 m.mul(root);
    //		 root.negate();
    m.m30 = m.m31 = m.m32 = 0;
    bool isInvertable;
    m = GLKMatrix4Invert(m, &isInvertable);
    if (!isInvertable)
        throw invalid_argument("Matrix couldnt be inverted");
    
    //		 m.mul(Scene.getCurrent().rootNode.transform.localMatrix());
    //	        m.set(this.getNode().transform.localMatrix());
    //	        m.negatePosition();
    
    //		 m.setIdentity();
    
    glMultMatrixf(m.m);
}

Matrix4 Camera::modelViewMatrix() {
//    Transform * t = this->getNode()->getTransform();
//    Vector3 eye = t->position();
//    Vector3 up = t->up();
//    Vector3 center = t->position() + t->forward();
//    
//    return GLKMatrix4Multiply(t->worldMatrix(), GLKMatrix4MakeLookAt(
//                                eye.x, eye.y, eye.z,
//                                center.x, center.y, center.z,
//                                up.x, up.y, up.z
//                                )
//                              );
    
    Matrix4 m = this->getNode()->getTransform()->worldMatrix();

//    cout << m << endl;
//    m.negate();
//    return m;
    return GLKMatrix4Invert(m, new bool());
}


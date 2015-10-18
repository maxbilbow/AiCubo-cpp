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
    this->fovX = 65;
    this->fovY = 65;
    this->nearZ = 0.1;
    this->farZ = 2000;
    this->aspect = 16.0/9.0f;
//    this->setName("Camera");
    
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

Matrix4 Camera::baseModelViewMatrix() {
    Matrix4 m = GLKMatrix4Identity;
    return GLKMatrix4Invert(m, new bool());
}

//Matrix4 Camera::modelViewMatrix() {
//    
//    Matrix4 m = this->getNode()->getTransform()->worldMatrix();
//
////    cout << GameNode::getCurrent()->Name() <<GameNode::getCurrent()->getTransform()->worldMatrix() << endl;
//    return RMXMatrix4Negate(m);
//}
//

Matrix4 Camera::viewMatrix() {
    
    Matrix4 m = this->getNode()->getTransform()->worldMatrix();

    m = GLKMatrix4RotateY(m, 180 * PI_OVER_180);
    m = GLKMatrix4Invert(m,nullptr);
    return m;
}


Matrix4 Camera::projectionMatrix() {
    return GLKMatrix4MakePerspective(fovX * PI_OVER_180, aspect, nearZ, farZ);
}

Matrix4 Camera::projectionMatrix(float aspect) {

    if (true)
        return GLKMatrix4MakePerspective(fovX * PI_OVER_180, this->aspect = aspect, nearZ, farZ);

    Matrix4 m = this->getNode()->getTransform()->worldMatrix();
    // Some calculus before the formula.
    float size = nearZ * tanf(fovX * PI_OVER_180 / 2.0);
    float left = -size, right = size, bottom = -size / aspect, top = size / aspect;
    
    // First Column
    m.m[0] = 2 * nearZ / (right - left);
    m.m[1] = 0.0;
    m.m[2] = 0.0;
    m.m[3] = 0.0;
    
    // Second Column
    m.m[4] = 0.0;
    m.m[5] = 2 * nearZ / (top - bottom);
    m.m[6] = 0.0;
    m.m[7] = 0.0;
    
    // Third Column
    m.m[8] = (right + left) / (right - left);
    m.m[9] = (top + bottom) / (top - bottom);
    m.m[10] = -(farZ + nearZ) / (farZ - nearZ);
    m.m[11] = -1;
    
    // Fourth Column
    m.m[12] = 0.0;
    m.m[13] = 0.0;
    m.m[14] = -(2 * farZ * nearZ) / (farZ - nearZ);
    m.m[15] = 0.0;
    return m;//GLKMatrix4MakePerspective(fovX * PI_OVER_180, aspect, nearZ, farZ);
}


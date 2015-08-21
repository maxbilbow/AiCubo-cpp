//
//  Transform.cpp
//  RMXKit
//
//  Created by Max Bilbow on 19/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//
#import "Includes.h"
#import "GameNode.hpp"
#import "NodeComponent.hpp"
#import "PhysicsBody.hpp"

#import "Transform.hpp"

#import <math.h>


using namespace rmx;
using namespace std;

Transform * Transform::New(GameNode * node) {
    return new Transform(node);
}

Transform::Transform(){
    NodeComponent::NodeComponent();
    throw invalid_argument("Not allowed to use construct without node");
}

Transform::Transform(GameNode * node) {
    NodeComponent::NodeComponent();
    this->node = node;
    _axis = GLKMatrix4Identity;
    _localMatrix = GLKMatrix4Identity;
    _scale = GLKVector3Make(1,1,1);
    this->setName("Transform");
}

Vector3 Transform::scale() {
    return this->_scale;
}

void Transform::setScale(float x, float y, float z) {
    _scale.x = x;
    _scale.y = y;
    _scale.z = z;
}



/**
 * TODO: Test with children
 * @return
 */
float Transform::mass() {
    float mass = this->getNode()->physicsBody() != null ? this->getNode()->physicsBody()->getMass() : 0.0f;
    GameNodeList::Iterator i = getNode()->getChildren();
    while (i.hasNext())
        mass += i.next()->getTransform()->mass();
    return mass;
}


/**
 * TODO check maths
 * @return
 */
Matrix4 Transform::worldMatrix() {
    Transform * parent = this->parent();
    if (parent !=   null && parent->parent() !=   null) {
        return GLKMatrix4Multiply(this->_localMatrix, parent->worldMatrix());
    } else {
        return this->_localMatrix;
    }
}

Transform * Transform::parent() {
    GameNode * parentNode = this->getNode()->getParent();
    return parentNode !=   null ? parentNode->getParent()->getTransform() :   null;
}

Vector3 Transform::localPosition() {
    return GLKVector3Make(_localMatrix.m30,
                          _localMatrix.m31,
                          _localMatrix.m32
                          );
}

Vector3 Transform::position() {
    Transform * parent = this->parent();
    if (parent !=   null && parent->parent() !=   null) {
        return this->localPosition() + parent->position();
    }
    return this->localPosition();
}

void Transform::setM(int i, float value) {
    this->_localMatrix.m[i] = value;
}

void Transform::addM(int i, float value) {
    this->_localMatrix.m[i] += value;
}

void Transform::setPosition(Vector3 position) {
    this->_localMatrix.m30 = position.x;
    this->_localMatrix.m31 = position.y;
    this->_localMatrix.m32 = position.z;
//    cout << _localMatrix;
}

void Transform::setPosition(float x, float y, float z) {
    this->_localMatrix.m30 = x;
    this->_localMatrix.m31 = y;
    this->_localMatrix.m32 = z;
}


    
string * readMessage(string message) {
    string * args = new string[message.length() / 3];
    int n = 0, j=0;
    cout<<message<<endl;
    for (int i = 0; i<message.length();++i){
        if (message[i] == ':') {
            n++; j=0;
        } else
            args[n][j++] = message[i];
    }
    return args;
}



bool Transform::move(Move name, float scale, string message) {

   return (this->translate(name, scale)
           || this->rotate(name, scale));
//        cout << "Successfully read message: " << name << ":" << message << endl;
    

    
}

//void Transform::translate(float x, float y, float z) {
//    _localMatrix = GLKMatrix4Translate(_localMatrix,x,y,z);
////    _localMatrix.m30 += x;
////    _localMatrix.m31 += y;
////    _localMatrix.m32 += z;
//}
//
//void Transform::translate(Vector3 v) {
//    _localMatrix = GLKMatrix4TranslateWithVector3(_localMatrix, v);
////    _localMatrix.m30 += v.x;
////    _localMatrix.m31 += v.y;
////    _localMatrix.m32 += v.z;
//}

bool Transform::translate(Move direction, float scale) {
    Vector3 v;
    switch (direction) {
        case Forward:
            scale *= -1;
            v = this->forward();
            break;
        case Up:
            //			scale *= -1;
            v = this->up();
            break;
        case Left:
            scale *= -1;
            v = this->left();
            break;
        case X:
            //			scale *= -1;
            v = GLKVector3Make(1,0,0);
            break;
        case Y:
            //			scale *= -1;
            v = GLKVector3Make(0,1,0);
            break;
        case Z:
            //			scale *= -1;
            v = GLKVector3Make(0,0,1);
            break;
        default:
            return false;
    }
    _localMatrix = GLKMatrix4TranslateWithVector3(_localMatrix, v * scale);
//    this->translate(v * scale);
    return true;
}



bool Transform::rotate(Move direction, float scale) {
    Vector3 v;
    switch (direction) {
        case Pitch:
//           scale *= -1;
            v = this->left();
            break;
        case Yaw:
            //			scale *= -1;
            v = this->up();
            break;
        case Roll:
            //			scale *= -1;
            v = this->forward();
            break;
        default:
            return false;
    }
    this->rotate(scale * PI_OVER_180,v);
    //				v.x * scale,
    //				v.y * scale,
    //				v.z * scale
    //				);
    return true;
}

void Transform::rotate(float radians, Vector3 v) {
    this->_localMatrix = GLKMatrix4RotateWithVector3(_localMatrix, radians, v);
    
}

//void Transform::rotate(float radians, float x, float y, float z) {
//    
//    this->_localMatrix = GLKMatrix4RotateWithVector3(_localMatrix, radians, x,y,z);

//    Matrix4 rMatrix = new Matrix4();
//    rMatrix.setIdentity();
//    rMatrix.setRotation(new AxisAngle4f(x,y,z,radians * 0.2f ));//*  RMX.PI_OVER_180));
//    //		_rMatrix.transpose();
//    
//    //		_quaternion.set(new AxisAngle4f(v.x,v.y,v.z,degrees * 0.1f));
//    Vector3 p = this.position();
//    this.mul(rMatrix);
//    this.setPosition(p);
    
//}



void Transform::translate(Vector4 v) {
    _localMatrix = GLKMatrix4TranslateWithVector4(_localMatrix, v);
}


Vector3 Transform::left() {
    return GLKVector3Make(_localMatrix.m00,
                          _localMatrix.m01,
                          _localMatrix.m02
                          );
}

Vector3 Transform::up() {
    return GLKVector3Make(_localMatrix.m10,
                          _localMatrix.m11,
                          _localMatrix.m12
                          );
}

Vector3 Transform::forward() {
    return GLKVector3Make(_localMatrix.m20,
                          _localMatrix.m21,
                          _localMatrix.m22
                          );
}




Vector3 Transform::localEulerAngles() {
    return GLKVector3Make (atan2f(-_localMatrix.m20, _localMatrix.m00),
                           asinf ( _localMatrix.m10),
                           atan2f(-_localMatrix.m12, _localMatrix.m11)
                           );
}

Quaternion Transform::rotation() {
    this->TODO();
    return GLKQuaternionMakeWithMatrix4(_localMatrix);
}

Quaternion Transform::localRotation() {
    return GLKQuaternionMakeWithMatrix4(_localMatrix);
}

Vector3 Transform::eulerAngles() {
    //		_rotation.set(this.worldMatrix());
    return localEulerAngles();
}


//Vector3 Transform::localEulerAngles() {
//    Matrix4 m = this->worldMatrix();
//    _eulerAngles.x = atan2f( m.m22, m.m23);
//    _eulerAngles.y = atan2f(-m.m21, Math.sqrt(m.m22 * m.m22 + m.m23 * m.m23));
//    _eulerAngles.z = atan2f( m.m11, m.m01);
//    return _eulerAngles;
//}


Matrix4 Transform::localMatrix() {
    return _localMatrix;
}



GameNode * Transform::setNode(GameNode * node) {
//    if (this->getNode() != null)// && this->getNode() != node)
        throw new invalid_argument("Transform can only be assigned once: " + this->Object::ToString());
//    node->setTransform(this);
//    return   null;
}


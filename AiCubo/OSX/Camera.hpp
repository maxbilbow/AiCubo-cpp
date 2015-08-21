//
//  Camera.hpp
//  RMXKit
//
//  Created by Max Bilbow on 30/07/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>

#endif /* Camera_hpp */

//#import "ASingleton.h"
//#import "Values.h"
namespace RMX {
    class Camera : public ASingleton<Camera> {

    public:
        
        GLKVector3 eye() {
            return GLKVector3Make(this->modelView.m00, this->modelView.m10, this->modelView.m20);
        }
        
        GLKVector3 center() {
            return GLKVector3Make(this->modelView.m01, this->modelView.m11, this->modelView.m21);
        }
        
        GLKVector3 up() {
            return GLKVector3Make(this->modelView.m02, this->modelView.m12, this->modelView.m22);
        }
        
        GLKMatrix4 modelView = GLKMatrix4Identity;
        
    };
}
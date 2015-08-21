//
//  Behaviour.hpp
//  RMXKit
//
//  Created by Max Bilbow on 19/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef Behaviour_hpp
#define Behaviour_hpp

#include <stdio.h>

#endif /* Behaviour_hpp */



namespace rmx {
    class Behaviour : public NodeComponent {
    protected:
        bool enabled;
    public:
       
        Behaviour() {
            this->enabled = true;
        }
        
        bool isEnabled(){
            return this->enabled;
        }
        
        void setEnabled(bool enabled) {
            this->enabled = enabled;
        }
        virtual void update(){}
        virtual void lateUpdate(){}
    };
    class SpriteBehaviour : public Behaviour {
    public:
        void SendMessage(std::string message, void * args = null, SendMessageOptions options = DoesNotRequireReceiver) override {
            
            this->getNode()->getTransform()->move(Y,10);
            std::cout << this->getNode()->getTransform()->localMatrix();
        }
    };
    
}
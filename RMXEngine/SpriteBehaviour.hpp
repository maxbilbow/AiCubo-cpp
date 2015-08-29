//
//  SpriteBehaviour.hpp
//  RMXKit
//
//  Created by Max Bilbow on 26/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef SpriteBehaviour_hpp
#define SpriteBehaviour_hpp

#include <stdio.h>

#endif /* SpriteBehaviour_hpp */


namespace rmx {
    class SpriteBehaviour : public Behaviour {
    public:
        void SendMessage(std::string message, void * args = nullptr, SendMessageOptions options = DoesNotRequireReceiver) override;
    };
}
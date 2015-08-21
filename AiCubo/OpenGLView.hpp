//
//  OpenGLView.hpp
//  RMXKit
//
//  Created by Max Bilbow on 29/07/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGLView_hpp
#define OpenGLView_hpp

#include <stdio.h>

#endif /* OpenGLView_hpp */

namespace RMX {
    class OpenGLView {
    public:
        static int Run(int argc, char * argv[]);

        static void reshape (int width, int height) ;
        static void display (void);
        
    };
}
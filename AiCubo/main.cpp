//
//  main.cpp
//  RMXKit
//
//  Created by Max Bilbow on 28/07/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

//#import <iostream>
//#import "Tests.h"
//#import "RMXKit.h"

//#import "RMXEngine.hpp"
//#import "LinkedList.h"
//#import "Dictionary.h"
//#import "ASingleton.h"
//#import "Object.h"
#define GLFW
#include "RMXEngine.hpp"

#import "AiCubo.hpp"
//#import "OpenGLView.h"

using namespace std;
using namespace rmx;






int run(int argc, char * argv[]) {
    
    
    AiCubo().run();
//    runTest2();
//    RMXLinkedListTest();
//    RMXDictionaryTest();
//    RMXObjectCloneTest();
//    RMXEventListenerTest();
//    RMXPrintableTest();
//    RMXObjectCountInitAndDeinitTest();
//    RMXBehaviourTest();
    
    return 0;
}

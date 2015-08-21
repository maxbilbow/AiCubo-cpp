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

#import "Includes.h"

#import "Scene.hpp"

#import "GameNode.hpp"
#import "Delegates.hpp"
#import "PhysicsBody.hpp"
#import "Transform.hpp"
#import "Behaviour.hpp"
#import "glfw3.h"
#import "GameView.hpp"
#import "Geometry.hpp"
#import "GameController.hpp"


//#import "OpenGLView.h"

using namespace std;
using namespace rmx;






int main(int argc, char * argv[]) {

    GameController::getInstance()->run();
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

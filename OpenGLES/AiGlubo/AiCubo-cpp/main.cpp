//
//  main.cpp
//  AiCubo-cpp
//
//  Created by Max Bilbow on 29/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

//#define GLFW
//#include "RMXKit.h"

#include "RMXEngine.hpp"
//#include "AiCubo.hpp"
using namespace std;
using namespace rmx;
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
//    AiCubo().run();
    
    set<GameNode*> stuff = set<GameNode*>();
    stuff.insert(new GameNode());
    stuff.insert(new GameNode());
    stuff.insert(new GameNode());
    stuff.insert(new GameNode());
    stuff.insert(new GameNode());
    
    for (set<GameNode*>::iterator i = stuff.begin(); i != stuff.end(); i++) {
        cout << *i << endl;
    }

    
    return 0;
}

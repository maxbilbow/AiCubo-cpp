//
//  Tools.c
//  RMXKit
//
//  Created by Max Bilbow on 30/07/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//
#include <stdlib.h>
#include "Tools.h"

using namespace rmx;

float * Tools::RandomColor() {
    float * rCol = new float[4];
    //rCol.x = (rand() % 100)/10;
    for (int i = 0; i<3; ++i)
        rCol[i] = ((float)(rand() % 800))/500;
    
    rCol[3] = 1.0;//{ ( ,(rand() % 100)/10,(rand() % 100)/10, 1.0 };
    //if (rCol.v[2] == rCol.z) NSLog(@"Fuck me!");
    return rCol;
}


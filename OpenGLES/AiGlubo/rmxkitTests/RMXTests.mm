//
//  RMXTests.c
//  AiCubo
//
//  Created by Max Bilbow on 18/10/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#define DEBUG 1
#import "Includes.h"
#import "TestCase.hpp"
#import "Buttons.hpp"
#import "ButtonsTest.hpp"
#import "RMXTests.h"
#import <Foundation/Foundation.h>

using namespace rmx;

@implementation RMXTests

+ (void)start
{
    ButtonsTest::run();
    Bugger::getInstance()->printToTerminal();
}
@end
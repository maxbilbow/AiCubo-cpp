//
//  RMXCpp.m
//  AiCubo
//
//  Created by Max Bilbow on 17/10/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Debug.hpp"
#import "Object.h"
#import <map>
#import <list>
#import <iostream>
#import "RMXCpp.h"
using namespace rmx;
@implementation RMXCpp


+ (void)logMessage:(NSString *)message from:(NSString *)from withID:(NSString *)logId
{
    Bugger::getInstance()->log([message cString], [from cString], [logId cString]);
}

+ (void)printLogToTerminal
{
    Bugger::getInstance()->printToTerminal();
}
@end
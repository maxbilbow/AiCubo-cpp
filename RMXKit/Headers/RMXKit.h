/*
 *  RMXKit.h
 *  RMXKit
 *
 *  Created by Max Bilbow on 28/07/2015.
 *  Copyright © 2015 Rattle Media Ltd. All rights reserved.
 *
 */

#define as_string(x) #x




//#pragma message("WARNING: You need to implement DEPRECATED for this compiler")

//#import "LinkedList.h"
//#import "Dictionary.h"
#import <list>
#import <map>
#import <set>
#import <list>
#import <iostream>
#import "stacktrace.h"
#import "NotificationCenter.h"

#import "Object.h"

#import "Debug.hpp"

//#import "ASingleton.h"
namespace rmx {
    class Unfinised : public Printable{
    protected:
        void TODO() {
            throw new std::invalid_argument("Method not yet implemented: " + this->ToString());
        }
//        virtual std::string ToString(){ return "";}
    };
    
    
}
//#import "Behaviour.hpp"

/*
 *   @author Max Bilbow, 15-08-04 16:08:32
 *
 *   @brief RMXKit.h
 *   RMXKit
 *   @since <#0.1#>
 *
 *   Created by Max Bilbow on 28/07/2015.
 *   Copyright © 2015 Max Bilbow. All rights reserved.
 *
 */
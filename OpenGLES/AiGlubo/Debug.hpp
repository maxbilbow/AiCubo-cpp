//
//  Debug.hpp
//  AiCubo
//
//  Created by Max Bilbow on 17/10/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef Debug_hpp
#define Debug_hpp

#include <stdio.h>
#import "Object.h"
#import <map>
#import <list>
#import <iostream>

#define RMX_LOG_INITIALIZE "START_UP"
#define RMX_LOG_DEFAULT    "DEFAULT"

namespace rmx {
    

    class Bugger {
        std::string current = RMX_LOG_INITIALIZE;
        std::map<std::string, std::list<std::string>*> logs;
        static Bugger * instance;
//        set<string> keys;
        Bugger();

        
    public:
        static Bugger * getInstance();
    
    
        void printToTerminal(bool evenIfVoid = false);
        void flush();
        
        /**
         * returns the current log as a string.
         */
        std::string getCurrentLog();
    
        void switchTo(std::string logID);
        
        void switchToDefault()
        {
            switchTo(RMX_LOG_DEFAULT);
        }
        
        virtual std::string ClassName() {
            return "rmx::Bugger";
        }
        
        virtual void addDebugGroup(std::string name);
        /**
         * Called after initial setup
         */
        void printToTerminalAfterStartUpInfoAndSwitchToDefault() {
            this->printToTerminal();
            this->switchToDefault();
        }

        void log(std::string message, rmx::Printable * fromClass, std::string fromMethod = "", std::string logID = RMX_LOG_DEFAULT);
        
        void log(std::string message, std::string from, std::string logID = RMX_LOG_DEFAULT);
    
        static void note(std::string message = nullptr, int maxTrace = 0);
        
    };
    
    void log(std::string message, rmx::Printable * fromClass, std::string fromMethod = "", std::string logID = RMX_LOG_DEFAULT);
    
    void log(std::string message, std::string from, std::string logID = RMX_LOG_DEFAULT);
    
    
    void logVector(float * arr, int size, rmx::Printable * fromClass, std::string fromMethod = "", std::string logID = RMX_LOG_DEFAULT);
    
    void logVector(float * arr, int size, std::string from, std::string logID = RMX_LOG_DEFAULT);
    
    
    void logMatrix(float * arr, int width, rmx::Printable * fromClass, std::string fromMethod = "", std::string logID = RMX_LOG_DEFAULT);

    void logMatrix(float * arr, int width, std::string from, std::string logID = RMX_LOG_DEFAULT);
}



#endif /* Debug_hpp */

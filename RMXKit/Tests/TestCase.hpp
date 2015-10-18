//
//  TestCase.hpp
//  AiCubo
//
//  Created by Max Bilbow on 18/10/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef TestCase_hpp
#define TestCase_hpp

#include <stdio.h>
//#import <math.h>


//#import "stacktrace.h"
#define String std::string
#define Tests std::map<String, bool>
namespace rmx {
    class TestCase : public Printable {
        int total = 0;
        int passes = 0;
        int warnings = 0;
        int fails = 0;
        
        Tests tests = std::map<String, bool>();
        String currentTest;
        bool finished = false;
        
    public:
        
        TestCase() {
            Bugger::getInstance()->printToTerminalAfterStartUpInfoAndSwitchToDefault();
        }
        
        ~TestCase() {
            if (!finished)
                finish();
        }
        

        void finish() {
            finished = true;
            log(report());
            Bugger::getInstance()->printToTerminal();
        }
        String report() {
            total = passes = fails = 0;
            for (Tests::iterator t = tests.begin(); t != tests.end(); ++t ) {
                total++;
                String testName = t->first;
                bool success = t->second;
                std::cout << testName << ": " << (success ? "SUCCESS" : "FAILED") << std::endl;
                if (success)
                    passes++;
                else
                    fails++;
            }
                
            float percent = total == 0 ? 0 : (int) (roundf((float)passes / total) * 100);
            String result = "passed: ";
            result += std::to_string(passes);
            result += ", warnings: ";
            result += std::to_string(warnings);
            result += ", failed: ";
            result += std::to_string(fails);
            result += ". Success: ";
            result += std::to_string(percent) + "%.";
            return result;
        }
        
        void warning(String string)
        {
            std::cout << "WARNING [" << currentTest << "]: " << string << std::endl;
            warnings++;
        }
        
        void startTest(String name) {
            currentTest = name;
            tests[name] = true;
            log("begin: " + name);
        }
        
        bool assertTrue(bool assert)
        {
            if (!assert) {
                std::cout << "FAILED [" << currentTest << "] " << std::endl;
                print_stacktrace();
//                throw std::invalid_argument("FAILED [" + currentTest + "] ");
                tests[currentTest] = false;
            }
            return assert;
        }
        
        
        void fail(std::exception * e = nullptr) {
            assertTrue(false);
            if (e != nullptr)
                std::cout << e->what() << std::endl;
        }
        
        virtual void setUp(String testName) {
            startTest(testName);
        }
        
        virtual void tearDown() {
            log("end: " + currentTest);
        }

        void log(String message)
        {
            std::cout << ClassName() << " >> " << message << std::endl;
            rmx::log(message, this);
        }
//        virtual void runTests(){
//            rmx::log("Should never end up here", this);
//            finish();
//        }
        
        virtual String ClassName() override {
            return "rmx::TestCase";
        }
    };
}

#undef String
#endif /* TestCase_hpp */

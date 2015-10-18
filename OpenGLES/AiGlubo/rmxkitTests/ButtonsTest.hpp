//
//  ButtonsTest.hpp
//  AiCubo
//
//  Created by Max Bilbow on 18/10/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef ButtonsTest_hpp
#define ButtonsTest_hpp

#include <stdio.h>

namespace rmx {
    class ButtonsTest : public TestCase {
        
    public:
        Buttons * buttons;
        
        void testAddButton();
        
        void testGetButtonByName();
        
        void testGetButtonsByKey();
        
        virtual void runTests();
        
        virtual void setUp(std::string name) override;
        
        virtual void tearDown() override;
        static void run() {
            ButtonsTest* t = new ButtonsTest();
            t->runTests();
            delete t;
        }
        
        virtual std::string ClassName() override {
            return "rmx::ButtonsTest";
        }
        
    };
}
#endif /* ButtonsTest_hpp */

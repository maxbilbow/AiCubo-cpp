//
//  ButtonsTest.cpp
//  AiCubo
//
//  Created by Max Bilbow on 18/10/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#include "Includes.h"

#include "TestCase.hpp"
#include "Buttons.hpp"
#include "ButtonsTest.hpp"

#define FORWARD "fwd"
#define BACK "bck"
#define JUMP "jmp"

using namespace rmx;
using namespace std;


void ButtonsTest::testAddButton()
{
    
}

void ButtonsTest::testGetButtonByName()
{

}

void ButtonsTest::testGetButtonsByKey()
{

}


void callAButtonByName(ButtonsTest * test)
{
    test->buttons->getButton(FORWARD)->func(1,2,3);
}

void callAButtonByKey(ButtonsTest * test)
{
    
    (*test->buttons->getButtons(RMX_KEY_W)->begin())->func(1,2,3);
}

void printStuff(int a, int b, float c)
{
    cout << "FORWARD: " << a << ", " << b << ", " << c  << endl;
}

void ButtonsTest::setUp(string name)
{

    TestCase::setUp(name);
    
    try {
        buttons = new Buttons();
        buttons->setButton(FORWARD, RMX_KEY_W)->func = printStuff;
    } catch (exception e) {
        fail(&e);
        exit(-1);
    }
}
void ButtonsTest::tearDown()
{
    buttons = nullptr;
}

void ButtonsTest::runTests()
{
    setUp(as_string(testAddButton));
    try {
        testAddButton();
    } catch (exception e) {
        fail(&e);
    }
    tearDown();
    
    setUp(as_string(testGetButtonByName));
    try {
        testGetButtonByName();
    } catch (exception e) {
        fail(&e);
    }
    tearDown();
    
    setUp(as_string(testGetButtonsByKey));
    try {
        testGetButtonsByKey();
    } catch (exception e) {
        fail(&e);
    }
    tearDown();
    
    setUp(as_string(callAButtonByName));
    try {
        callAButtonByName(this);
    } catch (exception e) {
        fail(&e);
    }
    tearDown();
    
    setUp(as_string(callAButtonByKey));
    try {
        callAButtonByName(this);
    } catch (exception e) {
        fail(&e);
    }
    tearDown();
    
}
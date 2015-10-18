//
//  Buttons.cpp
//  AiCubo
//
//  Created by Max Bilbow on 18/10/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#include "Includes.h"
#include "Buttons.hpp"


using namespace std;
using namespace rmx;

typedef std::set<Button*> ButtonSet;

void Button::unassigned(int state, int mods, float force)
{
    std::cout << "Unassigned Key was sent state: " << state << ", mods: " << mods << ", force: " << force << std::endl;
    print_stacktrace();
}

Buttons* Buttons::instance = nullptr;


Buttons::Buttons(){
    this->buttonsByName = map<string, Button*>();
    this->buttonsByKey = map<int, set<Button*>*>();
    buttonsByKey[-1] = new set<Button*>();
}

Buttons* Buttons::getInstance()
{
    return instance != nullptr ? instance : instance = new Buttons();
}

Button * Buttons::getButton(string name)
{
    Button * btn = buttonsByName[name];
    if (btn != nullptr) {
        btn->name = name;
        return btn;
    } else {
        return setButton(name);
    }
    
}

set<Button*> * Buttons::getButtons(int keyMap)
{
    set<Button*>* btns = buttonsByKey[keyMap];
    if (btns != nullptr)
        return btns;
    else
        return buttonsByKey[keyMap] = new set<Button*>();
    
}

Button * Buttons::setButton(string name, std::string description, int keyMap)
{
    return setButton(name, keyMap, description);
}

Button * Buttons::setButton(string name, int keyMap, string description)
{
    Button * btn = buttonsByName[name];
    if (btn == nullptr) {
        btn = buttonsByName[name] = new Button();
    } else {
        getButtons(btn->keyMap)->erase(btn);
    }
    btn->name = name;
    btn->description = description;
    btn->keyMap = keyMap;
    getButtons(keyMap)->emplace(btn);
    return btn;
}


void Buttons::invoke(int key, int state, int mods)
{
    invoke(key, state, mods, 1);
}

void Buttons::invoke(int key, int state, int mods, float force)
{
    ButtonSet* btns = getButtons(key);
    for (ButtonSet::iterator i = btns->begin(); i != btns->end(); ++i)
        (*i)->func(state,mods,force);
}


void Buttons::invoke(std::string name, int state, int mods)
{
    getButton(name)->func(state, mods, state == RMX_RELEASE ? 0 : 1);
}

void Buttons::invoke(std::string name, float force, int mods)
{
    getButton(name)->func(force != 0 ? RMX_PRESS : RMX_RELEASE, mods, force);
}


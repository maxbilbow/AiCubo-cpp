//
//  Debug.cpp
//  AiCubo
//
//  Created by Max Bilbow on 17/10/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#include <iostream>
#include <list>
#include <map>
#include <set>
using namespace std;
#include "Object.h"
#include "Debug.hpp"
#include "stacktrace.h"
#include "RMXTypes.h"
#include "RMXMath.h"


using namespace rmx;

Bugger * Bugger::instance = nullptr;

Bugger::Bugger()
{
    logs = map<string, list<string>*>();
    logs[RMX_LOG_INITIALIZE] = new list<string>();
//    logs[RMX_LOG_DEFAULT] = new list<string>();
}

void Bugger::addDebugGroup(string groupId)
{
    logs[groupId] = new list<string>();
}
Bugger * Bugger::getInstance()
{
    return instance != nullptr ? instance : (instance = new Bugger());
}

string Bugger::getCurrentLog()
{
    list<string> * log = this->logs[current];
    if (log == nullptr || log->empty()) {
        return "";
    }
    string output = "\n"+ClassName()+"::BEGIN LOG >>>>>>> " + current + " <<<<<<<<";
    
    for(list<string>::iterator i = log->begin(); i != log->end(); ++i)
        output += "\n" + *i;
    
    output += "\n<< END OF LOG: " + current + " <<<<<<<<";
    return output;
}

void Bugger::printToTerminal(bool evenIfVoid)
{
    string log = this->getCurrentLog();
    if (!log.empty()) {
        cout << log << endl;
        logs[current]->clear();
    } else if (evenIfVoid)
        cout << ClassName() << " >> No Logs" << endl;
}

void Bugger::switchTo(string logID)
{
    current = logID;
    list<string> * log = logs[logID];
    if (log == nullptr) {
        logs[logID] = log = new list<string>();
    }
    
    log->emplace_front("<><><> Switching to RMLog: "+ logID +" <><><>");
    
}

void Bugger::log(string message, Printable * fromClass, string fromMethod, string logID)
{
    #ifdef DEBUG
    string thisLog = "   - " + fromClass->ClassName() + "::" + fromMethod + " >> " + message;
    list<string> * log = logs[logID];
    if (log == nullptr) {
        logs[logID] = log = new list<string>();
    }
    log->emplace_back(thisLog);
    #endif
}

void Bugger::log(std::string message, std::string from, std::string logID)
{
#ifdef DEBUG
    string thisLog = "   - " + from + " >> " + message;
    list<string> * log = logs[logID];
    if (log == nullptr) {
        logs[logID] = log = new list<string>();
    }
    log->emplace_back(thisLog);
#endif
}

void Bugger::note(string message, int maxTrace)
{
    cout << message << endl;
    print_stacktrace(stderr, maxTrace + 1);
}

void rmx::log(string message, Printable * fromClass, string fromMethod, string logID)
{
    Bugger::getInstance()->log(message, fromClass, fromMethod, logID);
}

void rmx::log(string message, string from, string logID)
{
    Bugger::getInstance()->log(message, from, logID);
}



void rmx::logVector(float * arr, int size, Printable * fromClass, string fromMethod, string logID)
{
    string message = "v: ";
    for (int i = 0; i<size; ++i)
        message += to_string(arr[i]) + ", ";
    Bugger::getInstance()->log(message, fromClass, fromMethod, logID);
}

void rmx::logVector(float *arr, int size, std::string from, string logID)
{
    string message = "v: ";
    for (int i = 0; i<size; ++i)
        message += to_string(arr[i]) + ", ";
    Bugger::getInstance()->log(message, from, logID);
}

void rmx::logMatrix(float * arr, int width, rmx::Printable * fromClass, string fromMethod, string logID)
{
    string message = "mat:";
    for (int row = 0; row < width; ++row) {
        message += "\n    - ";
        for (int i = 0; i<width; ++i)
            message += to_string(arr[i]) + ", ";
        
    }
    Bugger::getInstance()->log(message, fromClass, fromMethod, logID);
}

void logMatrix(float * arr, int width, string from, string logID)
{
    string message = "mat:";
    for (int row = 0; row < width; ++row) {
        message += "\n    - ";
        for (int i = 0; i<width; ++i)
            message += to_string(arr[i]) + ", ";
        
    }
    Bugger::getInstance()->log(message, from, logID);
}

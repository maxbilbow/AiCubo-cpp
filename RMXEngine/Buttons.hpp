//
//  Buttons.hpp
//  AiCubo
//
//  Created by Max Bilbow on 18/10/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef Buttons_hpp
#define Buttons_hpp

#include <stdio.h>
#endif /* Buttons_hpp */



namespace rmx {
    struct Button {
        std::string name;
        std::string description = "Unknown";
        
        int keyMap = -1;
        int state = 0;
        
        /*!
         * A percentage of press for buttons that are active. If
         */
        float force = 0;
        
        /*!
         * for variable functions
         * params are state, mods and force respectively
         */
        void (*func)(int, int, float) = unassigned;
        
    private:
        static void unassigned(int state, int mods, float force);
        
        
        
    };
    
    class Buttons : public Printable {
        static Buttons * instance;
        std::map<std::string, Button*> buttonsByName;
        std::map<int, std::set<Button*> *> buttonsByKey;
        

        
    public:
        Buttons();
        static Buttons * getInstance();

        Button * setButton(std::string name, int keyMap, std::string description = "");
        
        Button * setButton(std::string name, std::string description = "", int keyMap = -1);
        
        Button * getButton(std::string name);
        
        std::set<Button*> * getButtons(int keyMap);
        
        void invoke(int key, int state, int mods);
        
        void invoke(int key, int state, int mods, float force);
        
        void invoke(std::string name, int state, int mods);
        
        void invoke(std::string name, float force, int mods);
        
        virtual std::string ClassName() override {
            return "rmx::Buttons";
        }
    };
    
}

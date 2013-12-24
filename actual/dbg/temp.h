#pragma once

#include <string>
#include "symbol.h"

namespace Temp{

    class Temp 
    {
    public: 
        Temp(){
            name = "TEMP#" + std::to_string(currId++);
        }

        Temp(const std::string& s){
            name = s;
        }

        std::string& getName() {
            return name;
        }

    private:
        
        std::string name;
        static int currId;
    }; 

    class Label 
    {
    public:
        Label(){
            name = "LABEL#" + std::to_string(currId++);
        }

        Label(const std::string& s){
            name = s;
        }
        
        std::string& getName() {
            return name;
        }

    private:
        std::string name;
        static int currId;
    };

    class LabelList
    {
    public:
        const Label* label;
        const LabelList* rest;

        LabelList(const Label* lb, const LabelList* rest) : label(lb), rest(rest) {}

    };
    
}

#pragma once

#include "symbol.h"

namespace Temp{

    class Temp 
    {
    public: 
        Temp(){
            std::stringstream s;
            s << "T" << currId;
            name.str();
            currId++;
        };
        Temp(const std::string s){
            name = s;
        };
        
        std::string name;
        static int currId;
    }; // Temp::currId = 1;

    class Label 
    {
    public:
        Label(){
            std::stringstream s;
            s << "L" << currId;
            name.str();
            currId++;
        };
        Label(const std::string s){
            name = s;
        };
        
        std::string name;
        static int currId;
    };
    
    //public class TempList {...}
    //public class LabelList {...}
}

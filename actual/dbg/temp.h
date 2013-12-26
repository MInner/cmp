#pragma once

#include <string>
#include <sstream>  
#include "symbol.h"

namespace Temp{
    template <typename T> 
    std::string NumberToString(T Number)
    {
        std::stringstream ss;
        ss << Number;
        return ss.str();
    }    

    class Temp 
    {
    public: 
        Temp(){
            name = "TEMP#" + NumberToString(curId++);
        }

        Temp(const std::string& s){
            name = s;
        }
        
        static int curId;
    
        std::string name;
    }; 

    class Label 
    {
    public:
        Label(){
            name = "LABEL#" + NumberToString(curId++);
        }

        Label(const std::string& s){
            name = s;
        }
    
        std::string name;
    private:
        static int curId;
    };

    class LabelList
    {
    public:
        const Label* label;
        const LabelList* rest;

        LabelList(const Label* lb, const LabelList* rest = NULL) : label(lb), rest(rest) {}

    };
    
}

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
        std::string name;

        Temp(){
            name = "TEMP#" + NumberToString(curId++);
        }

        static const Temp* getTemp(const std::string& s)
        {
            if (m.count(s))
            {
                return m[s];
            }
            else
            {
                auto t = new Temp(s);
                m[s] = t;
                return t;
            }
        }

    private:
        static std::map<const std::string, const Temp*> m;
        Temp(const std::string& s){
            name = s;
        }
        
        static int curId;
    
    }; 

    class TempList {
    public:
        const Temp* temp;
        const TempList* next;

        TempList(const Temp* tp, const TempList* next = NULL) : temp(tp), next(next) {}
        TempList(const Temp* t1, const Temp* t2)
        {
            temp = t1;
            next = new TempList(t2);
        }
        TempList(const Temp* t1, const Temp* t2, const Temp* t3)
        {
            temp = t1;
            next = new TempList(t2, t3);
        }

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

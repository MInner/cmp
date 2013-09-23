#include "vartable.h"
#include <map>
#include <iostream>

VarTable::VarTable(){
    //var = new map<string,int>();
}

int VarTable::getVar(const string name){
    if (this->var.count(name) == 0){
            cout << "there is no var " << name << endl;
    } else {
        return var[name];
    }
}

void VarTable::setVar(const string name, const int val){
    var[name] = val;
}

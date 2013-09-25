
#include <map>
#include <iostream>

#include "Vartable.h"

using std::cout;
using std::endl;

VarTable::VarTable(){ }

int VarTable::getVar(const string name) const{
    if (this->var.count(name) == 0){
        cout << "there is no var " << name << endl;
        return 0;
    } else {
        return var.at(name);
    }
}

void VarTable::setVar(const string name, const int val){
    var[name] = val;
}

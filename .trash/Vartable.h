#pragma once

#include <string>
#include <map>

using std::string;
using std::map;

class VarTable
{
public:
    VarTable();
    int getVar(const string name) const;
    void setVar(const string name, const int val);
private:
    map<string,int> var;
};

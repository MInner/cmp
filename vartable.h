#ifndef VARTABLE_H_INCLUDED
#define VARTABLE_H_INCLUDED

#include <string>
#include <map>

using namespace std;

class VarTable
{
public:
    VarTable();
    int getVar(const string name);
    void setVar(const string name, const int val);
private:
    map<string,int> var;
};

#endif // VARTABLE_H_INCLUDED

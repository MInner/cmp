#ifndef VARTABLE_H_INCLUDED
#define VARTABLE_H_INCLUDED

#include <string>

class VarTable
{
public:
    VarTable();
    const int get(const string name);
    void set(const string name, const int val);

};

#endif // VARTABLE_H_INCLUDED

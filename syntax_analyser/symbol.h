#pragma once

#include <string>
#include <map>
#include <iostream>

using std::ostream;

class Symbol
{
	static std::map<std::string, const Symbol*> storage;
	Symbol(std::string _str);
	std::string str;
public:
	static const Symbol* getSymbol(const std::string&);
	friend ostream& operator<<(ostream& os, const Symbol*& s);
	friend ostream& operator<<(ostream& os, Symbol*& s);

};

ostream& operator<<(ostream& os, const Symbol*& s);
ostream& operator<<(ostream& os, Symbol*& s);
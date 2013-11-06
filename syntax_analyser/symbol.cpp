#include "symbol.h"
#include <map>
#include <string>
#include <iostream>

std::map<std::string, const Symbol*> Symbol::storage = std::map<std::string, const Symbol*>();

const Symbol* Symbol::getSymbol(const std::string& str)
{
	if (storage.find(str) == storage.end())
	{
		Symbol* s = new Symbol(str);
		storage[str] = s;
		return s;
	} else {
		return storage[str];
	}
}

Symbol::Symbol(std::string _str)
{
	str = _str;
}

ostream& operator<<(ostream& os, const Symbol*& s)
{
	os << s->str;
	return os; 
}
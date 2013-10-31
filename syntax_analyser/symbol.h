#include <string>
#include <map>

class Symbol
{
	static std::map<std::string, Symbol*> storage;
	Symbol();
public:
	static const Symbol* getSymbol(std::string);
};
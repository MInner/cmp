#pragma once

#include "symbol.h"

class NameGenerator 
{
public:
	static std::string gen(const Symbol* cl, const Symbol* meth)
	{
		return "@@" + cl->getStr() + "__" + meth->getStr();
	}

	static std::string gen(const std::string& cl, const std::string& meth)
	{
		return "@@" + cl + "__" + meth;
	}
};
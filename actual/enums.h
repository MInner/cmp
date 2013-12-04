#pragma once

#include "symbol.h"


namespace Type
{

	enum Type { 
		INT_ARR,
		BOOL, 
		STRING,
		INT
	};

}

struct TypeData
{
	bool isInternal; // is internal type
	Type::Type internalType;
	const Symbol* customType;
};

namespace Arithm
{
	enum Arithm { 
		PLUS,
		MINUS, 
		MUL,
		DIV
	};
}

namespace Logic
{
enum Logic { 
	L_AND,
	L_LT, 
	L_NOT	
};
}
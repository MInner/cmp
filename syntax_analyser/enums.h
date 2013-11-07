#pragma once

namespace Type
{

enum Type { 
	INT_ARR,
	BOOL, 
	STRING,
	INT
};

union AnyType
{
	Type internaltype;
	Symbol* name;
};

}

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
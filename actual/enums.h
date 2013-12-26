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

//other constants:
/*
BINOP.PLUS, BINOP.MINUS, BINOP.MUL, BINOP.DIV, BINOP.AND,
BINOP.OR, BINOP.LSHIFT, BINOP.RSHIFT, BINOP.ARSHIFT, BINOP.XOR;
CJUMP.EQ, CJUMP.NE, CJUMP.LT, CJUMP.GT, CJUMP.LE,
CJUMP.GE, CJUMP.ULT, CJUMP.ULE, CJUMP.UGT, CJUMP.UGE;
*/
namespace IRTree
{
	namespace OPERATOR
	{
    enum BINOP {
	    PLUS,
	    MINUS, 
	    MUL,
	    DIV,
	    AND1,
	    OR, 
	    LSHIFT,
	    RSHIFT,
	    ARSHIFT,
	    XOR
    };

    enum CONDOP { 
        EQ,
        NE, 
        LT1, 
        GT, 
        LE,
        GE, 
        ULT, 
        ULE, 
        UGT, 
        UGE
    };
	}

}

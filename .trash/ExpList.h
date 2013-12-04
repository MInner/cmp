#pragma once
#include <string>
#include "all.h"
#include <assert.h>

struct ExpList {
	ExpList( const Exp* exp_, const ExpList* expList_ ): exp( exp_ ), expList( expList_ )
    {
        assert( exp_ != 0 );
    }
	const Exp* const exp;
	const ExpList* const expList;
};

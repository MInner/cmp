#ifndef EXPLIST
#define EXPLIST

#include <string>
#include "all.h"

class ExpList {
public:
	ExpList( const Exp* exp_, const ExpList* expList_ );
	const Exp* const exp;
	const ExpList* const expList;
};

#endif

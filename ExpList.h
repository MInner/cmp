#ifndef EXPLIST
#define EXPLIST

#include <string>

class ExpList {
public:
	ExpList( const Exp* exp_, const ExpList* expList_ );
private:
	const Exp* const exp;
	const ExpList* const expList;
};

#endif

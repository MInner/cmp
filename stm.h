
#include "Exp.h"

#ifndef STMH
#define STMH

#include <assert.h>
#include <string>

using namespace std::string;

class Statement {
public:
	virtual ~Statement();
};

class CompoundStatement : public Statement {
public:
	CompoundStatement( const Statement* first, const Statement* second );
private:
	const Statement* const firstStm;
	const Statement* const secondStm;
};

// AssignStm
class AssignStm : public Statement {
public:
	AssignStm( const string id, const Exp* exp );
private:
	const string const idP;
	const Exp* const expP;
};

#endif

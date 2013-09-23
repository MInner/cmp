#include <assert.h>
#include <string>
#include "ExpList.h"
#include "Exp.h"

using namespace std;

class Statement {
public:
	// Виртуальный деструктор т.к. предполагается наследование
	virtual ~Statement() {}
};

// Правило CompoundStm
class CompoundStatement::CompoundStatement : public Statement {
public:
	CompoundStatement( const Statement* first, const Statement* second ) :
	firstStm( first ), secondStm( second )
	{
		assert( firstStm != 0 );
		assert( secondStm != 0 );
	}

private:
	const Statement* const firstStm;
	const Statement* const secondStm;
};

// AssignStm
class AssignStm : public Statement {
public:
	AssignStm( const string id, const Exp* exp ) :
	id( id ), exp( exp )
	{
		assert( id != "" );
		assert( exp != 0 );
	}

private:
	const string id;
	const Exp* const exp;
};

// PrintStm
class PrintStm : public Statement {
public:
	PrintStm( const ExpList* expList) :
	expList( expList )
	{
		assert( expList != 0 );
	}

private:
	const ExpList* expList;
};



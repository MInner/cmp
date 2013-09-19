#include <assert.h>
#include <String>

using namespace std;

class Statement {
public:
	// Виртуальный деструктор т.к. предполагается наследование
	virtual ~Statement();
};

// Правило CompoundStm
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


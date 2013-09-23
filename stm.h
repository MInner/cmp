#ifndef STMH
#define STMH

#include "Exp.h"
#include "all.h"

#include <assert.h>
#include <string>

using std::string;

class Statement {
public:
    virtual const VarTable* Exec(const VarTable* table) const = 0;
	virtual ~Statement();
};

class CompoundStatement : public Statement {
public:
	CompoundStatement( const Statement* first, const Statement* second );
	const VarTable* Exec(const VarTable* table) const;
private:
	const Statement* const firstStm;
	const Statement* const secondStm;
};

class AssignStm : public Statement {
public:
	AssignStm( const string id, const Exp* exp );
	const VarTable* Exec(const VarTable* table) const;
private:
	const string id;
	const Exp* const exp;
};

class PrintStm : public Statement {
public:
	PrintStm( const ExpList* expList);
	const VarTable* Exec(const VarTable* table) const;
private:
	const ExpList* expList;
};

#endif

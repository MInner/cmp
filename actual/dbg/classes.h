#pragma once

#include <string>
#include <iostream>
#include "visitor.h"
#include "enums.h"
#include "interfaces.h"
#include "symbol.h"

using std::cout;

#define nullptr 0

// Expression

class ArithmExp : public IExpression
{
public:
	
	ArithmExp(const Arithm::Arithm op_, const IExpression* left_, const IExpression* right_, int line_, int column_):
		op(op_), left(left_), right(right_), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}

	const Arithm::Arithm op;
	const IExpression* left;
	const IExpression* right;
	const int line;
	const int column;

};

class LogicExp : public IExpression
{
public:
	
	LogicExp(const Logic::Logic op_, const IExpression* left_, const IExpression* right_, int line_, int column_):
		left(left_), op(op_), right(right_), line(line_), column(column_) {}
	LogicExp(const Logic::Logic op_, const IExpression* left_, int line_, int column_):
		left(left_), op(op_), right(nullptr), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}

	const IExpression* left;
	const Logic::Logic op;
	const IExpression* right;
	const int line;
	const int column;

};

class IntVal : public IExpression
{
public:
	IntVal(const int val_, int line_, int column_):
		val(val_), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}

	const int val;
	const int line;
	const int column;
};

class BoolVal : public IExpression
{
public:
	BoolVal(const bool val_, int line_, int column_):
		val(val_), line(line_), column(column_)  {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const bool val;
	const int line;
	const int column;
};

class IdExp : public IExpression
{
public:
	IdExp(const Symbol* id_, int line_, int column_):
		id(id_), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const Symbol* id;
	const int line;
	const int column;
};

class NewExp : public IExpression
{
public:
	NewExp(const Symbol* id_, int line_, int column_):
		id(id_), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}

	const Symbol* id;
	const int line;
	const int column;
};


// ?!!!!!!
class ThisExp : public IExpression
{
public:
	ThisExp(int line_, int column_):
	line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}

	const int line;
	const int column;
};

class LenExp : public IExpression
{
public:
	LenExp(const IExpression* exp_, int line_, int column_):
		exp(exp_), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}

	const int line;
	const int column;
	const IExpression*  exp;
};

class CallMethodExp : public IExpression
{
public:
	CallMethodExp(const IExpression* exp_, const Symbol* id_,
		const IExpressionList* list_, int line_, int column_):
		exp(exp_), id(id_), list(list_), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}

	const IExpression* exp;
	const Symbol* id;
	const IExpressionList* list;
	const int line;
	const int column;
};

class NewIntArrExp : public IExpression
{
public:
	NewIntArrExp(const IExpression* exp_, int line_, int column_):
		exp(exp_), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}

	const IExpression*  exp;
	const int line;
	const int column;
};

class ArrValExp : public IExpression
{
public:
	ArrValExp(const IExpression* exp_, const IExpression*  idExp_, int line_, int column_):
		exp(exp_), idExp(idExp_), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const IExpression*  exp;
	const IExpression*  idExp;
	const int line;
	const int column;
};

// Statement

class BlockStm : public IStatement
{
public:
	BlockStm(const IStatements* stms_, int line_, int column_):
		stms(stms_), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}

	const int line;
	const int column;
	const IStatements*  stms;
};

class AssignStm : public IStatement
{
public:
	const int line;
	const int column;
	
	AssignStm(const IAssignment* assign_, int line_, int column_):
		assign(assign_), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const IAssignment*  assign;
};

class PrintStmPrintStm : public IStatement
{
public:
	const int line;
	const int column;
	
	PrintStmPrintStm(const IExpression* exp_, int line_, int column_):
		exp(exp_), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const IExpression*  exp;
};

class WhileStm : public IStatement
{
public:
	const int line;
	const int column;
	
	WhileStm(const IExpression* exp_, const IStatement*  stm_, int line_, int column_):
		exp(exp_), stm(stm_), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const IExpression*  exp;
	const IStatement*  stm;
};

class IfElseStm : public IStatement
{
public:
	const int line;
	const int column;
	
	IfElseStm(const IExpression* exp_, const IStatement*  stm_,
		const IStatement*  elseStm_, int line_, int column_):
		exp(exp_), stm(stm_), elseStm(elseStm_), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const IExpression*  exp;
	const IStatement*  stm;
	const IStatement*  elseStm;
};

class AssignArrStm : public IStatement
{
public:
	AssignArrStm(const Symbol* id_, const IExpression* exp_, const IExpression*  newexp_, 
		int line_, int column_):
		exp(exp_), newexp(newexp_), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}

	const Symbol* id;
	const IExpression*  exp;
	const IExpression* newexp;
	const int line;
	const int column;
};

// StatementsImpl  AssignmentImpl expressionListImpl

class ExpressionListImpl : public IExpressionList
{
public:
	ExpressionListImpl(const IExpression* exp_, const IExpressionList*  list_, int line_, int column_):
		exp(exp_), list(list_), line(line_), column(column_) {}
	ExpressionListImpl(const IExpression* exp_, int line_, int column_):
		exp(exp_), list(nullptr), line(line_), column(column_) {}
	ExpressionListImpl(int line_, int column_):
		exp(NULL), list(nullptr), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const IExpression*  exp;
	const IExpressionList*  list;
	const int line;
	const int column;
};

class StatementsImpl : public IStatements
{
public:
	const int line;
	const int column;
	
	StatementsImpl(const IStatement* stm_, const IStatements*  list_, int line_, int column_):
		stm(stm_), list(list_), line(line_), column(column_) {}
	StatementsImpl(int line_, int column_):
		stm(NULL), list(nullptr), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const IStatement*  stm;
	const IStatements*  list;
};

class AssignmentImpl : public IAssignment
{
public:
	const int line;
	const int column;
	
	AssignmentImpl(const Symbol* id_, const IExpression* exp_, int line_, int column_):
		id(id_), exp(exp_), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const Symbol* id;
	const IExpression*  exp;
};

// InternalType ArguementsImpl ArguementImpl

class ArguementImpl : public IArguement
{
public:
	const int line;
	const int column;

	ArguementImpl(const IType* type_, const Symbol* id_, int line_, int column_):
		type(type_), id(id_), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const IType*  type;
	const Symbol* id;
};

class ArguementsImpl : public IArguements
{
public:
	const int line;
	const int column;

	ArguementsImpl(const IArguement* arg_, const IArguements*  list_, int line_, int column_):
		arg(arg_), list(list_), line(line_), column(column_) {}
	ArguementsImpl(int line_, int column_):
		arg(NULL), list(nullptr), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}

	const IArguement*  arg;
	const IArguements*  list;
};


class InternalType : public IType
{
public:
	const int line;
	const int column;

	InternalType(const Type::Type type_, int line_, int column_):
		type(type_), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}

	bool isInternal() const
	{
		return true;
	}

	const Type::Type type;
};

class CustomType : public IType
{
public:
	const int line;
	const int column;

	CustomType(const Symbol* type_, int line_, int column_):
		type(type_), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}

	bool isInternal() const
	{
		return false;
	}

	const Symbol* type;

};

// VarDeclarationsImpl VarDeclarationImpl MethodDeclarationsImpl MethodDeclarationImpl

class VarDeclarationImpl : public IVarDeclaration
{
public:
	const int line;
	const int column;
	
	VarDeclarationImpl(const IType* type_, const Symbol* id_, int line_, int column_):
		type(type_), id(id_), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const IType*  type;
	const Symbol* id;
};

class VarDeclarationsImpl : public IVarDeclarations
{
public:
	const int line;
	const int column;
	
	VarDeclarationsImpl(const IVarDeclaration* dec_, const IVarDeclarations*  list_,
		int line_, int column_):
		dec(dec_), list(list_), line(line_), column(column_) {}
	VarDeclarationsImpl(int line_, int column_):
		dec(NULL), list(nullptr), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const IVarDeclaration*  dec;
	const IVarDeclarations*  list;
};

class MethodDeclarationsImpl : public IMethodDeclarations
{
public:
	const int line;
	const int column;
	
	MethodDeclarationsImpl(const IMethodDeclaration* dec_, const IMethodDeclarations*  list_, int line_, int column_):
		dec(dec_), list(list_), line(line_), column(column_) {}
	MethodDeclarationsImpl(int line_, int column_):
		dec(NULL), list(nullptr), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}

	const IMethodDeclaration*  dec;
	const IMethodDeclarations*  list;
};

class MethodDeclarationImpl : public IMethodDeclaration
{
public:
	const int line;
	const int column;
	
	MethodDeclarationImpl(const IType*  type_, const Symbol* id_,
		const IArguements*  args_, const IVarDeclarations*  vars_,
		const IStatements*  statements_,	const IExpression*  exp_, 
		int line_, int column_):
		type(type_), id(id_), args(args_), vars(vars_),
		statements(statements_), exp(exp_), line(line_), column(column_){}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}

	const IType*  type;
	const Symbol* id;
	const IArguements*  args;
	const IVarDeclarations*  vars;
	const IStatements*  statements;
	const IExpression*  exp;
};

// MainClassImpl ClassDeclarationsImpl ClassDeclarationImpl

class ClassDeclarationsImpl : public IClassDeclarations
{
public:
	const int line;
	const int column;
	
	ClassDeclarationsImpl(const IClassDeclaration* dec_, const IClassDeclarations*  list_, int line_, int column_):
		dec(dec_), list(list_), line(line_), column(column_) {}
	ClassDeclarationsImpl(int line_, int column_):
		dec(NULL), list(nullptr), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const IClassDeclaration*  dec;
	const IClassDeclarations*  list;
};

class ClassDeclarationImpl : public IClassDeclaration
{
public:
	const int line;
	const int column;
	
	ClassDeclarationImpl(const Symbol* id_, const Symbol* extId_,
		const IVarDeclarations*  vars_, const IMethodDeclarations*  methods_,
		int line_, int column_):
		id(id_), extId(extId_), vars(vars_), methods(methods_), line(line_), column(column_) {}
	ClassDeclarationImpl(const Symbol* id_, const IVarDeclarations*
		vars_, const IMethodDeclarations*  methods_, int line_, int column_):
		id(id_), extId(NULL), vars(vars_), methods(methods_), line(line_), column(column_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const Symbol* id;
	const Symbol* extId;
	const IVarDeclarations*  vars;
	const IMethodDeclarations*  methods;
};

class ProgramImpl : public IProgram
{
public:
	const static ProgramImpl* me;
	const int line;
	const int column;
	ProgramImpl(const IMainClass* cl_, const IClassDeclarations*  decs_, int line_, int column_):
		cl(cl_), decs(decs_), line(line_), column(column_) 
		{ me = this;}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}

public:
	const IMainClass* cl;
	const IClassDeclarations*  decs;
};

class MainClassImpl : public IMainClass
{
public:
	const int line;
	const int column;
	
	MainClassImpl(const Symbol* id_, const Symbol* argId_,
		const IStatement*  stm_, int line_, int column_):
		id(id_), argId(argId_), stm(stm_), line(line_), column(column_)  {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}

	const Symbol* id;
	const Symbol* argId;
	const IStatement*  stm;
};
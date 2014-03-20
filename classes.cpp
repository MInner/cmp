#include <string>
#include <iostream>

#include "classes.h"

using std::cout;

// Expression
ArithmExp::ArithmExp(const Arithm::Arithm op_, const IExpression* left_, const IExpression* right_, int line_, int column_):
	op(op_), left(left_), right(right_), line(line_), column(column_) {}

int ArithmExp::Accept(IVisitor* v) const
{
	return v->visit(this);
}


LogicExp::LogicExp(const Logic::Logic op_, const IExpression* left_, const IExpression* right_, int line_, int column_):
	left(left_), op(op_), right(right_), line(line_), column(column_) {}
LogicExp::LogicExp(const Logic::Logic op_, const IExpression* left_, int line_, int column_):
	left(left_), op(op_), right(nullptr), line(line_), column(column_) {}

int LogicExp::Accept(IVisitor* v) const
{
	return v->visit(this);
}

IntVal::IntVal(const int val_, int line_, int column_):
	val(val_), line(line_), column(column_) {}

int IntVal::Accept(IVisitor* v) const
{
	return v->visit(this);
}

BoolVal::BoolVal(const bool val_, int line_, int column_):
	val(val_), line(line_), column(column_)  {}

int BoolVal::Accept(IVisitor* v) const
{
	return v->visit(this);
}

IdExp::IdExp(const Symbol* id_, int line_, int column_):
	id(id_), line(line_), column(column_) {}

int IdExp::Accept(IVisitor* v) const
{
	return v->visit(this);
}

NewExp::NewExp(const Symbol* id_, int line_, int column_):
	id(id_), line(line_), column(column_) {}

int Accept(IVisitor* v) const
{
	return v->visit(this);
}

// ?!!!!!!
ThisExp::ThisExp(int line_, int column_):
line(line_), column(column_) {}

int ThisExp::Accept(IVisitor* v) const
{
	return v->visit(this);
}

LenExp::LenExp(const IExpression* exp_, int line_, int column_):
	exp(exp_), line(line_), column(column_) {}

int LenExp::Accept(IVisitor* v) const
{
	return v->visit(this);
}

CallMethodExp::CallMethodExp(const IExpression* exp_, const Symbol* id_,
	const IExpressionList* list_, int line_, int column_):
	exp(exp_), id(id_), list(list_), line(line_), column(column_) {}

int CallMethodExp::Accept(IVisitor* v) const
{
	return v->visit(this);
}

NewIntArrExp::NewIntArrExp(const IExpression* exp_, int line_, int column_):
	exp(exp_), line(line_), column(column_) {}

int NewIntArrExp::Accept(IVisitor* v) const
{
	return v->visit(this);
}

ArrValExp::ArrValExp(const IExpression* exp_, const IExpression*  idExp_, int line_, int column_):
	exp(exp_), idExp(idExp_), line(line_), column(column_) {}

int ArrValExp::Accept(IVisitor* v) const
{
	return v->visit(this);
}

// Statement

BlockStm::BlockStm(const IStatements* stms_, int line_, int column_):
	stms(stms_), line(line_), column(column_) {}

int BlockStm::Accept(IVisitor* v) const
{
	return v->visit(this);
}

AssignStm::AssignStm(const IAssignment* assign_, int line_, int column_):
	assign(assign_), line(line_), column(column_) {}

int AssignStm::Accept(IVisitor* v) const
{
	return v->visit(this);
}

PrintStmPrintStm::PrintStmPrintStm(const IExpression* exp_, int line_, int column_):
	exp(exp_), line(line_), column(column_) {}

int PrintStmPrintStm::Accept(IVisitor* v) const
{
	return v->visit(this);
}

WhileStm::WhileStm(const IExpression* exp_, const IStatement*  stm_, int line_, int column_):
	exp(exp_), stm(stm_), line(line_), column(column_) {}

int WhileStm::Accept(IVisitor* v) const
{
	return v->visit(this);
}

IfElseStm::IfElseStm(const IExpression* exp_, const IStatement*  stm_,
	const IStatement*  elseStm_, int line_, int column_):
	exp(exp_), stm(stm_), elseStm(elseStm_), line(line_), column(column_) {}

int IfElseStm::Accept(IVisitor* v) const
{
	return v->visit(this);
}

AssignArrStm::AssignArrStm(const Symbol* id_, const IExpression* exp_, const IExpression*  newexp_, 
	int line_, int column_):
	id(id_), exp(exp_), newexp(newexp_), line(line_), column(column_) {}

int AssignArrStm::Accept(IVisitor* v) const
{
	return v->visit(this);
}

// StatementsImpl  AssignmentImpl expressionListImpl

ExpressionListImpl::ExpressionListImpl(const IExpression* exp_, const IExpressionList*  list_, int line_, int column_):
	exp(exp_), list(list_), line(line_), column(column_) {}
ExpressionListImpl::ExpressionListImpl(const IExpression* exp_, int line_, int column_):
	exp(exp_), list(nullptr), line(line_), column(column_) {}
ExpressionListImpl::ExpressionListImpl(int line_, int column_):
	exp(NULL), list(nullptr), line(line_), column(column_) {}

int ExpressionListImpl::Accept(IVisitor* v) const
{
	return v->visit(this);
}

StatementsImpl::StatementsImpl(const IStatement* stm_, const IStatements*  list_, int line_, int column_):
	stm(stm_), list(list_), line(line_), column(column_) {}
StatementsImpl::StatementsImpl(int line_, int column_):
	stm(NULL), list(nullptr), line(line_), column(column_) {}

int StatementsImpl::Accept(IVisitor* v) const
{
	return v->visit(this);
}


AssignmentImpl::AssignmentImpl(const Symbol* id_, const IExpression* exp_, int line_, int column_):
	id(id_), exp(exp_), line(line_), column(column_) {}

int AssignmentImpl::Accept(IVisitor* v) const
{
	return v->visit(this);
}

// InternalType ArguementsImpl ArguementImpl

ArguementImpl::ArguementImpl(const IType* type_, const Symbol* id_, int line_, int column_):
	type(type_), id(id_), line(line_), column(column_) {}

int ArguementImpl::Accept(IVisitor* v) const
{
	return v->visit(this);
}

ArguementsImpl::ArguementsImpl(const IArguement* arg_, const IArguements*  list_, int line_, int column_):
	arg(arg_), list(list_), line(line_), column(column_) {}
ArguementsImpl::ArguementsImpl(int line_, int column_):
	arg(NULL), list(nullptr), line(line_), column(column_) {}

int ArguementsImpl::Accept(IVisitor* v) const
{
	return v->visit(this);
}




InternalType::InternalType(const Type::Type type_, int line_, int column_):
	type(type_), line(line_), column(column_) {}

int InternalType::Accept(IVisitor* v) const
{
	return v->visit(this);
}

bool InternalType::isInternal() const
{
	return true;
}


CustomType::CustomType(const Symbol* type_, int line_, int column_):
	type(type_), line(line_), column(column_) {}

int CustomType::Accept(IVisitor* v) const
{
	return v->visit(this);
}

bool CustomType::isInternal() const
{
	return false;
}


// VarDeclarationsImpl VarDeclarationImpl MethodDeclarationsImpl MethodDeclarationImpl


VarDeclarationImpl::VarDeclarationImpl(const IType* type_, const Symbol* id_, int line_, int column_):
	type(type_), id(id_), line(line_), column(column_) {}

int VarDeclarationImpl::Accept(IVisitor* v) const
{
	return v->visit(this);
}


VarDeclarationsImpl::VarDeclarationsImpl(const IVarDeclaration* dec_, const IVarDeclarations*  list_,
	int line_, int column_):
	dec(dec_), list(list_), line(line_), column(column_) {}
VarDeclarationsImpl::VarDeclarationsImpl(int line_, int column_):
	dec(NULL), list(nullptr), line(line_), column(column_) {}

int VarDeclarationsImpl::Accept(IVisitor* v) const
{
	return v->visit(this);
}


MethodDeclarationsImpl::MethodDeclarationsImpl(const IMethodDeclaration* dec_, const IMethodDeclarations*  list_, int line_, int column_):
	dec(dec_), list(list_), line(line_), column(column_) {}
MethodDeclarationsImpl(int line_, int column_):
	dec(NULL), list(nullptr), line(line_), column(column_) {}

int MethodDeclarationsImpl::Accept(IVisitor* v) const
{
	return v->visit(this);
}


MethodDeclarationImpl::MethodDeclarationImpl(const IType*  type_, const Symbol* id_,
	const IArguements*  args_, const IVarDeclarations*  vars_,
	const IStatements*  statements_,	const IExpression*  exp_, 
	int line_, int column_):
	type(type_), id(id_), args(args_), vars(vars_),
	statements(statements_), exp(exp_), line(line_), column(column_){}

int MethodDeclarationImpl::Accept(IVisitor* v) const
{
	return v->visit(this);
}

// MainClassImpl ClassDeclarationsImpl ClassDeclarationImpl


ClassDeclarationsImpl::ClassDeclarationsImpl(const IClassDeclaration* dec_, const IClassDeclarations*  list_, int line_, int column_):
	dec(dec_), list(list_), line(line_), column(column_) {}
ClassDeclarationsImpl::ClassDeclarationsImpl(int line_, int column_):
	dec(NULL), list(nullptr), line(line_), column(column_) {}

int ClassDeclarationsImpl::Accept(IVisitor* v) const
{
	return v->visit(this);
}


ClassDeclarationImpl::ClassDeclarationImpl(const Symbol* id_, const Symbol* extId_,
	const IVarDeclarations*  vars_, const IMethodDeclarations*  methods_,
	int line_, int column_):
	id(id_), extId(extId_), vars(vars_), methods(methods_), line(line_), column(column_) {}
ClassDeclarationImpl::ClassDeclarationImpl(const Symbol* id_, const IVarDeclarations*
	vars_, const IMethodDeclarations*  methods_, int line_, int column_):
	id(id_), extId(NULL), vars(vars_), methods(methods_), line(line_), column(column_) {}

int ClassDeclarationImpl::Accept(IVisitor* v) const
{
	return v->visit(this);
}

ProgramImpl::ProgramImpl(const IMainClass* cl_, const IClassDeclarations*  decs_, int line_, int column_):
	cl(cl_), decs(decs_), line(line_), column(column_) 
	{ me = this;}

int ProgramImpl::Accept(IVisitor* v) const
{
	return v->visit(this);
}


MainClassImpl::MainClassImpl(const Symbol* id_, const Symbol* argId_,
	const IStatement*  stm_, int line_, int column_):
	id(id_), argId(argId_), stm(stm_), line(line_), column(column_)  {}

int MainClassImpl::Accept(IVisitor* v) const
{
	return v->visit(this);
}
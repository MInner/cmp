
// #include "enums.h"
#include <string>
#include <iostream>

using std::cout;

#define nullptr 0

// Expression

class ArithmExp : public IExpression
{
public:
	ArithmExp(const Arithm::Arithm op_, const IExpression* left_, const IExpression* right_): 
		left(left_), op(op_), right(right_) {cout<<"A";}
private:
	const Arithm::Arithm op;
	const IExpression* left;	
	const IExpression* right;
};

class LogicExp : public IExpression
{
public:
	LogicExp(const Logic::Logic op_, const IExpression* left_, const IExpression* right_): 
		left(left_), op(op_), right(right_) {cout<<"A";}
	LogicExp(const Logic::Logic op_, const IExpression* left_): 
		left(left_), op(op_), right(nullptr) {cout<<"A";}

private:
	const Logic::Logic op;
	const IExpression* left;	
	const IExpression* right;
};

class IntVal : public IExpression
{
public:
	IntVal(const int val_): 
		val(val_) {cout<<"A";}	

private:
	const int val;
};

class BoolVal : public IExpression
{
public:
	BoolVal(const bool val_): 
		val(val_) {cout<<"A";}	

private:
	const bool val;
};

class IdExp : public IExpression
{
public:
	IdExp(const std::string id_): 
		id(id_) {cout<<"A";}	

private:
	const std::string id;
};

class NewExp : public IExpression
{
public:
	NewExp(const std::string id_): 
		id(id_) {cout<<"A";}	

private:
	const std::string id;
};

class ThisExp : public IExpression
{
public:
	ThisExp(const std::string val_): 
		val(val_) {cout<<"A";}	

private:
	const std::string val;
};

class LenExp : public IExpression
{
public:
	LenExp(const IExpression* exp_): 
		exp(exp_) {cout<<"A";}	

private:
	const IExpression*  exp;
};

class CallMethodExp : public IExpression
{
public:
	CallMethodExp(const IExpression* exp_, const std::string id_, 
		const IExpressionList* list_): 
		exp(exp_), id(id_), list(list_) {cout<<"A";}
private:
	const IExpression* exp;
	const std::string id;	
	const IExpressionList* list;
};

class NewIntArrExp : public IExpression
{
public:
	NewIntArrExp(const IExpression* exp_): 
		exp(exp_) {cout<<"A";}	

private:
	const IExpression*  exp;
};

class ArrValExp : public IExpression
{
public:
	ArrValExp(const IExpression* exp_, const IExpression*  inExp_): 
		exp(exp_), inExp(inExp_) {cout<<"A";}	

private:
	const IExpression*  exp;
	const IExpression*  inExp;
};

// Statement

class BlockStm : public IStatement
{
public:
	BlockStm(const IStatements* stms_): 
		stms(stms_) {cout<<"A";}	

private:
	const IStatements*  stms;
};

class AssignStm : public IStatement
{
public:
	AssignStm(const IAssignment* assign_): 
		assign(assign_) {cout<<"A";}	

private:
	const IAssignment*  assign;
};

class PrintStmPrintStm : public IStatement
{
public:
	PrintStmPrintStm(const IExpression* exp_): 
		exp(exp_) {cout<<"A";}	

private:
	const IExpression*  exp;
};

class WhileStm : public IStatement
{
public:
	WhileStm(const IExpression* exp_, const IStatement*  stm_): 
		exp(exp_), stm(stm_) {cout<<"A";}	

private:
	const IExpression*  exp;
	const IStatement*  stm;
};

class IfElseStm : public IStatement
{
public:
	IfElseStm(const IExpression* exp_, const IStatement*  stm_, 
		const IStatement*  elseStm_): 
		exp(exp_), stm(stm_), elseStm(elseStm_) {cout<<"A";}	

private:
	const IExpression*  exp;
	const IStatement*  stm;
	const IStatement*  elseStm;
};

class AssignArrStm : public IStatement
{
public:
	AssignArrStm(const std::string id_, const IExpression* exp_, const IStatement*  stm_): 
		exp(exp_), stm(stm_) {cout<<"A";}	

private:
	const std::string id;
	const IExpression*  exp;
	const IStatement*  stm;
};

// StatementsImpl  AssignmentImpl expressionListImpl

class ExpressionListImpl : public IExpressionList
{
public:
	ExpressionListImpl(const IExpression* exp_, const IExpressionList*  list_): 
		exp(exp_), list(list_) {cout<<"A";}	
	ExpressionListImpl(const IExpression* exp_): 
		exp(exp_), list(nullptr) {cout<<"A";}
	ExpressionListImpl(): 
		exp(NULL), list(nullptr) {cout<<"A";}

private:
	const IExpression*  exp;
	const IExpressionList*  list;
};

class StatementsImpl : public IStatements
{
public:
	StatementsImpl(const IStatement* stm_, const IStatements*  list_): 
		stm(stm_), list(list_) {cout<<"A";}		
	StatementsImpl(): 
		stm(NULL), list(nullptr) {cout<<"A";}

private:
	const IStatement*  stm;
	const IStatements*  list;
};

class AssignmentImpl : public IAssignment
{
public:
	AssignmentImpl(const std::string id_, const IExpression* exp_): 
		id(id_), exp(exp_) {cout<<"A";}	

private:
	const std::string id;
	const IExpression*  exp;
};

// InternalType ArguementsImpl ArguementImpl

class ArguementImpl : public IArguement
{
public:
	ArguementImpl(const IType* type_, const std::string id_): 
		type(type_), id(id_) {cout<<"A";}	

private:
	const IType*  type;
	const std::string id;	
};

class ArguementsImpl : public IArguements
{
public:
	ArguementsImpl(const IArguement* arg_, const IArguements*  list_): 
		arg(arg_), list(list_) {cout<<"A";}		
	ArguementsImpl(): 
		arg(NULL), list(nullptr) {cout<<"A";}

private:
	const IArguement*  arg;
	const IArguements*  list;
};


class InternalType : public IType
{
public:
	InternalType(const Type::Type type_): 
		type(type_) {cout<<"A";}
private:
	const Type::Type type;
};

// VarDeclarationsImpl VarDeclarationImpl MethodDeclarationsImpl MethodDeclarationImpl

class VarDeclarationImpl : public IVarDeclaration
{
public:
	VarDeclarationImpl(const IType* type_, const std::string id_): 
		type(type_), id(id_) {cout<<"A";}	

private:
	const IType*  type;
	const std::string id;	
};

class VarDeclarationsImpl : public IVarDeclarations
{
public:
	VarDeclarationsImpl(const IVarDeclaration* dec_, const IVarDeclarations*  list_): 
		dec(dec_), list(list_) {cout<<"A";}		
	VarDeclarationsImpl(): 
		dec(NULL), list(nullptr) {cout<<"A";}

private:
	const IVarDeclaration*  dec;
	const IVarDeclarations*  list;
};

class MethodDeclarationsImpl : public IMethodDeclarations
{
public:
	MethodDeclarationsImpl(const IMethodDeclaration* dec_, const IMethodDeclarations*  list_): 
		dec(dec_), list(list_) {cout<<"A";}		
	MethodDeclarationsImpl(): 
		dec(NULL), list(nullptr) {cout<<"A";}

private:
	const IMethodDeclaration*  dec;
	const IMethodDeclarations*  list;
};

class MethodDeclarationImpl : public IMethodDeclaration
{
public:
	MethodDeclarationImpl(const IType*  type_, const std::string id_, 
		const IArguements*  args_, const IVarDeclarations*  vars_,	
		const IStatements*  statements_,	const IExpression*  exp_): 
		type(type_), id(id_), args(args_), vars(vars_),
		statements(statements_), exp(exp_){cout<<"A";}		

private:
	const IType*  type;
	const std::string id;
	const IArguements*  args;
	const IVarDeclarations*  vars;
	const IStatements*  statements;
	const IExpression*  exp;
};

// MainClassImpl ClassDeclarationsImpl ClassDeclarationImpl

class ClassDeclarationsImpl : public IClassDeclarations
{
public:
	ClassDeclarationsImpl(const IClassDeclaration* dec_, const IClassDeclarations*  list_): 
		dec(dec_), list(list_) {cout<<"A";}		
	ClassDeclarationsImpl(): 
		dec(NULL), list(nullptr) {cout<<"A";}

private:
	const IClassDeclaration*  dec;
	const IClassDeclarations*  list;
};

class ClassDeclarationImpl : public IClassDeclaration
{
public:
	ClassDeclarationImpl(const std::string id_, const std::string extId_, 
		const IVarDeclarations*  vars_, const IMethodDeclarations*  methods_): 
		id(id_), extId(extId_), vars(vars_), methods(methods_) {cout<<"A";}		
	ClassDeclarationImpl(const std::string id_, const IVarDeclarations*  
		vars_, const IMethodDeclarations*  methods_): 
		id(id_), extId(NULL), vars(vars_), methods(methods_) {cout<<"A";}

private:
	const std::string id;
	const std::string extId;
	const IVarDeclarations*  vars;
	const IMethodDeclarations*  methods;
};

class ProgramImpl : public IProgram
{
public:
	ProgramImpl(const IMainClass* cl_, const IClassDeclarations*  decs_): 
		cl(cl_), decs(decs_) {cout<<"A";}			

private:	
	const IMainClass* cl;
	const IClassDeclarations*  decs;
};

class MainClassImpl : public IMainClass
{
public:
	MainClassImpl(const std::string id_, const std::string argId_, 
		const IStatement*  stm_): 
		id(id_), argId(argId_), stm(stm_) {cout<<"A";}		
	

private:
	const std::string id;
	const std::string argId;
	const IStatement*  stm;
};

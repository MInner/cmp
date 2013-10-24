#include "interfaces.h"
#include "enums.h"
#include "string"


// Expression

class ArithmExp : public IExpression
{
public:
	ArithmExp(const Arithm op_, const IExpression* left_, const IExpression* right_): 
		left(left_), op(op_), right(right_) {}
private:
	const Arithm op;
	const IExpression* left;	
	const IExpression* right;
};

class LogicExp : public IExpression
{
public:
	LogicExp(const Logic op_, const IExpression* left_, const IExpression* right_): 
		left(left_), op(op_), right(right_) {}
	LogicExp(const Logic op_, const IExpression* left_): 
		left(left_), op(op_), right(nullptr) {}

private:
	const Logic op;
	const IExpression* left;	
	const IExpression* right;
};

class IntVal : public IExpression
{
public:
	IntVal(const int val_): 
		val(val_) {}	

private:
	const int val;
};

class BoolVal : public IExpression
{
public:
	BoolVal(const bool val_): 
		val(val_) {}	

private:
	const bool val;
};

class IdExp : public IExpression
{
public:
	IdExp(const std::string id_): 
		id(id_) {}	

private:
	const std::string id;
};

class NewExp : public IExpression
{
public:
	NewExp(const std::string id_): 
		id(id_) {}	

private:
	const std::string id;
};

class ThisExp : public IExpression
{
public:
	ThisExp(const std::string val_): 
		val(val_) {}	

private:
	const std::string val;
};

class LenExp : public IExpression
{
public:
	LenExp(const IExpression* exp_): 
		exp(exp_) {}	

private:
	const IExpression*  exp;
};

class CallMethodExp : public IExpression
{
public:
	CallMethodExp(const IExpression* exp_, const std::string id_, 
		const IExpressionList* list_): 
		exp(exp_), id(id_), list(list_) {}
private:
	const IExpression* exp;
	const std::string id;	
	const IExpressionList* list;
};

class NewIntArrExp : public IExpression
{
public:
	NewIntArrExp(const IExpression* exp_): 
		exp(exp_) {}	

private:
	const IExpression*  exp;
};

class ArrValExp : public IExpression
{
public:
	ArrValExp(const IExpression* exp_, const IExpression*  inExp_): 
		exp(exp_), inExp(inExp_) {}	

private:
	const IExpression*  exp;
	const IExpression*  inExp;
};

// Statement

class BlockStm : public IStatement
{
public:
	BlockStm(const IStatements* stms_): 
		stms(stms_) {}	

private:
	const IStatements*  stms;
};

class AssignStm : public IStatement
{
public:
	AssignStm(const IAssignment* assign_): 
		assign(assign_) {}	

private:
	const IAssignment*  assign;
};

class PrintStmPrintStm : public IStatement
{
public:
	PrintStmPrintStm(const IExpression* exp_): 
		exp(exp_) {}	

private:
	const IExpression*  exp;
};

class WhileStm : public IStatement
{
public:
	WhileStm(const IExpression* exp_, const IStatement*  stm_): 
		exp(exp_), stm(stm_) {}	

private:
	const IExpression*  exp;
	const IStatement*  stm;
};

class IfElseStm : public IStatement
{
public:
	IfElseStm(const IExpression* exp_, const IStatement*  stm_, 
		const IStatement*  elseStm_): 
		exp(exp_), stm(stm_), elseStm(elseStm_) {}	

private:
	const IExpression*  exp;
	const IStatement*  stm;
	const IStatement*  elseStm;
};

class AssignArrStm : public IStatement
{
public:
	AssignArrStm(const std::string id_, const IExpression* exp_, const IStatement*  stm_): 
		exp(exp_), stm(stm_) {}	

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
		exp(exp_), list(list_) {}	
	ExpressionListImpl(const IExpression* exp_): 
		exp(exp_), list(nullptr) {}
	ExpressionListImpl(): 
		exp(NULL), list(nullptr) {}

private:
	const IExpression*  exp;
	const IExpressionList*  list;
};

class StatementsImpl : public IStatements
{
public:
	StatementsImpl(const IStatement* stm_, const IStatements*  list_): 
		stm(stm_), list(list_) {}		
	StatementsImpl(): 
		stm(NULL), list(nullptr) {}

private:
	const IStatement*  stm;
	const IStatements*  list;
};

class AssignmentImpl : public IAssignment
{
public:
	AssignmentImpl(const std::string id_, const IExpression* exp_): 
		id(id_), exp(exp_) {}	

private:
	const std::string id;
	const IExpression*  exp;
};

// InternalType ArguementsImpl ArguementImpl

class ArguementImpl : public IArguement
{
public:
	ArguementImpl(const IType* type_, const std::string id_): 
		type(type_), id(id_) {}	

private:
	const IType*  type;
	const std::string id;	
};

class ArguementsImpl : public IArguements
{
public:
	ArguementsImpl(const IArguement* arg_, const IArguements*  list_): 
		arg(arg_), list(list_) {}		
	ArguementsImpl(): 
		arg(NULL), list(nullptr) {}

private:
	const IArguement*  arg;
	const IArguements*  list;
};


class InternalType : public IType
{
public:
	InternalType(const Type type_): 
		type(type_) {}
private:
	const Type type;
};

// VarDeclarationsImpl VarDeclarationImpl MethodDeclarationsImpl MethodDeclarationImpl

class VarDeclarationImpl : public IVarDeclaration
{
public:
	VarDeclarationImpl(const IType* type_, const std::string id_): 
		type(type_), id(id_) {}	

private:
	const IType*  type;
	const std::string id;	
};

class VarDeclarationsImpl : public IVarDeclarations
{
public:
	VarDeclarationsImpl(const IVarDeclaration* dec_, const IVarDeclarations*  list_): 
		dec(dec_), list(list_) {}		
	VarDeclarationsImpl(): 
		dec(NULL), list(nullptr) {}

private:
	const IVarDeclaration*  dec;
	const IVarDeclarations*  list;
};
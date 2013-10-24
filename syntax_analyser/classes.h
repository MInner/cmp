#include "interfaces.h"
#include "enums.h"
#include "string"

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


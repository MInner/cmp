#include "interfaces.h"
#include "enums.h"

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
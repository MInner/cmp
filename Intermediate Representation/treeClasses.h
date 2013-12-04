
class CONST : public Exp
{
public:
	CONST(int value_):
		value(value_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const int value;	
};

class NAME : public Exp
{
public:
	NAME(Label label_):
		label(label_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const label* label;	
};

class TEMP : public Exp 
{
public:
	TEMP(const Temp::Temp* temp_):
		temp(temp_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const Temp::Temp* temp	
};

class BINOP : public Exp
{
public:
	BINOP(int binop_, const Exp* left_, const Exp* right_):
		binop(binop_), left(left_), right(right_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const int binop;
	const Exp* left;
	const Exp* right;
};

class MEM : public Exp
{
public:
	MEM(const Exp* exp_):
		exp(exp_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const Exp* exp;
};

class CALL : public Exp
{
public:
	CALL(const Exp* func_, const ExpList* args_) :
		func(func_), args(args_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const Exp* func;
	const ExpList* args;
};

class ESEQ(Stm stm, Exp exp) : public Exp
{
public:
	BINOP(int binop_, const Exp* left_, const Exp* right_):
		binop(binop_), left(left_), right(right_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const int binop;
	const Exp* left;
	const Exp* right;
};

abstract class Stm (управляющие конструкции)
class MOVE(Exp dst, Exp src): MOVE(Temp(t), e) vs MOVE(MEM(e1), e2) : public Stm
class EXP(Exp exp) : public Stm
class JUMP(Exp exp, Temp.LabelList targets) : public Stm
class CJUMP(int relop, Exp left, Exp right, Label iftrue, Label iffalse) : public Stm
class SEQ(Stm left, Stm right) : public Stm
class LABEL(Label label) : public Stm



other classes:
class ExpList(Exp head, ExpList tail)
class StmList(Stm head, StmList tail)
other constants:
BINOP.PLUS, BINOP.MINUS, BINOP.MUL, BINOP.DIV, BINOP.AND,
BINOP.OR, BINOP.LSHIFT, BINOP.RSHIFT, BINOP.ARSHIFT, BINOP.XOR;
CJUMP.EQ, CJUMP.NE, CJUMP.LT, CJUMP.GT, CJUMP.LE,
CJUMP.GE, CJUMP.ULT, CJUMP.ULE, CJUMP.UGT, CJUMP.UGE;


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

class TEMP(Temp.Temp temp) : public Exp
class BINOP(int binop, Exp left, Exp right) : public Exp
class MEM(Exp exp) : public Exp
class CALL(Exp func, ExpList args) : public Exp
class ESEQ(Stm stm, Exp exp) : public Exp

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

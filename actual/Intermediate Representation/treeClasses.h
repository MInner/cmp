namespace IRTree{

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
	CALL(const Exp* func_, const ExpList* args_):
		func(func_), args(args_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const Exp* func;
	const ExpList* args;
};

class ESEQ : public Exp
{
public:
	ESEQ(const Stm* stm_, const Exp* exp_):
		stm(stm_), exp(exp_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const Stm* stm
	const Exp* exp;
};

//abstract class Stm (управляющие конструкции)
//class MOVE(Exp dst, Exp src): MOVE(Temp(t), e) vs MOVE(MEM(e1), e2) 
class MOVE : public Stm
{
public:
	MOVE(const Exp* dst_, const src* src_):
		dst(dst_), src(src_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const int binop;
	const Exp* dst;
	const Exp* src;
};

class EXP : public Stm
{
public:
	EXP(const Exp* exp_):
		exp(exp_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const Exp* exp;
};

class JUMP : public Stm
{
public:
	JUMP(const Exp* exp_, const Temp::LabelList* targets_):
		exp(exp_), targets(targets_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const Exp* exp;
	const Temp::LabelList* targets;
};

class CJUMP : public Stm
{
public:
	CJUMP(int relop_, const Exp* left_, const Exp* right_, const Label* iftrue_, const Label* iffalse_):
		relop(relop_), left(left_), right(right_), iftrue(iftrue_), iffalse(iffalse_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const int relop;
	const Exp* left;
	const Exp* right;
	const Label* iftrue;
	const Label* iffalse;
};

class SEQ : public Stm
{
public:
	SEQ(const Stm* left_, const Stm* right):
		left(left_), right(right_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const Stm* left;
	const Stm* right;
};

class LABEL : public Stm // не уверен что у нас существует класс Label, ну тогда надо создать
{
public:
	LABEL(const Label* label_):
		label(label_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const Label* label;
};


//other classes:
class ExpList
{
public:
	ExpList(const Exp* head_, const ExpList* tail_):
		head(head_), tail(tail_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const Exp* head;
	const ExpList* tail;
};

class StmList
{
public:
	StmList(const Stm* head, const StmList* tail):
		head(head_), tail(tail_) {}

	int Accept(IVisitor* v) const
	{
		return v->visit(this);
	}


	const Stm* head;
	const StmList* tail;
};

} 

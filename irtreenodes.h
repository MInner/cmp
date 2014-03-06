#pragma once

#include "itreevisitor.h"

namespace IRTree {

class CONST : public IExp
{
public:
	CONST(int value_):
		value(value_) {}

	int Accept(ITreeVisitor* v) const
	{
		return v->visit(this);
	}


	const int value;	
};

class NAME : public IExp
{
public:
	NAME(const Temp::Label* label_):
		label(label_) {}

	int Accept(ITreeVisitor* v) const
	{
		return v->visit(this);
	}


	const Temp::Label* label;	
};

class TEMP : public IExp 
{
public:
	TEMP(const Temp::Temp* temp_):
		temp(temp_) {}

	int Accept(ITreeVisitor* v) const
	{
		return v->visit(this);
	}


	const Temp::Temp* temp;
};

class BINOP : public IExp
{
public:
	BINOP(int binop_, const IExp* left_, const IExp* right_):
		binop(binop_), left(left_), right(right_) {}

	int Accept(ITreeVisitor* v) const
	{
		return v->visit(this);
	}


	const int binop;
	const IExp* left;
	const IExp* right;
};

class MEM : public IExp
{
public:
	MEM(const IExp* exp_):
		exp(exp_) {}

	int Accept(ITreeVisitor* v) const
	{
		return v->visit(this);
	}


	const IExp* exp;
};

class CALL : public IExp
{
public:
	CALL(const Temp::Label* func_, const ExpList* args_):
		func(func_), args(args_) {}

	int Accept(ITreeVisitor* v) const
	{
		return v->visit(this);
	}


	const Temp::Label* func;
	const ExpList* args;
};

class ESEQ : public IExp
{
public:
	ESEQ(const IStm* stm_, const IExp* exp_):
		stm(stm_), exp(exp_) {}

	int Accept(ITreeVisitor* v) const
	{
		return v->visit(this);
	}


	const IStm* stm;
	const IExp* exp;
};

//abstract class Stm (управляющие конструкции)
//class MOVE(Exp dst, Exp src): MOVE(Temp(t), e) vs MOVE(MEM(e1), e2) 
class MOVE : public IStm
{
public:
	MOVE(const IExp* dst_, const IExp* src_): dst(dst_), src(src_) {}

	int Accept(ITreeVisitor* v) const
	{
		return v->visit(this);
	}

	const IExp* dst;
	const IExp* src;
};

class EXP : public IStm
{
public:
	EXP(const IExp* exp_):
		exp(exp_) {}

	int Accept(ITreeVisitor* v) const
	{
		return v->visit(this);
	}


	const IExp* exp;
};

class JUMP : public IStm
{
public:
	JUMP(const IExp* exp_, const Temp::LabelList* targets_):
		exp(exp_), targets(targets_) {}

	int Accept(ITreeVisitor* v) const
	{
		return v->visit(this);
	}

	const IExp* exp;
	const Temp::LabelList* targets;
};

class CJUMP : public IStm
{
public:
	CJUMP(int relop_, const IExp* left_, const IExp* right_, const Temp::Label* iftrue_, const Temp::Label* iffalse_):
		relop(relop_), left(left_), right(right_), iftrue(iftrue_), iffalse(iffalse_) {}

	int Accept(ITreeVisitor* v) const
	{
		return v->visit(this);
	}


	const int relop;
	const IExp* left;
	const IExp* right;
	const Temp::Label* iftrue;
	const Temp::Label* iffalse;
};

class SEQ : public IStm
{
public:
	SEQ(const IStm* left_, const IStm* right_):
		left(left_), right(right_) {}

	int Accept(ITreeVisitor* v) const
	{
		return v->visit(this);
	}


	const IStm* left;
	const IStm* right;
};

class LABEL : public IStm 
{
public:
	LABEL(const Temp::Label* label_):
		label(label_) {}

	int Accept(ITreeVisitor* v) const
	{
		return v->visit(this);
	}


	const Temp::Label* label;
};


//other classes:
class ExpList
{
public:
	ExpList(const IExp* head_, const ExpList* tail_ = NULL):
		head(head_), tail(tail_) {}

	int Accept(ITreeVisitor* v) const
	{
		return v->visit(this);
	}


	const IExp* head;
	const ExpList* tail;
};

class StmList
{
public:
	StmList(const IStm* head_, const StmList* tail_ = NULL):
		head(head_), tail(tail_) {}

	int Accept(ITreeVisitor* v) const
	{
		return v->visit(this);
	}


	const IStm* head;
	const StmList* tail;
};

} 

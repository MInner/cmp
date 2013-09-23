#ifndef EXPH
#define EXPH

#include <string>
#include "all.h"
#include "stm.h"
#include "ExpList.h"

using std::string;

class Exp
{
public:
//	virtual int Execute();
	virtual ~Exp();
};

class IdExp : public Exp
{
public:
	IdExp(const string s_);
private:
    const string s;
};

class NumExp : public Exp
{
public:
	NumExp(const int a_);
private:
    const int a;
};

class OpExp : public Exp
{
public:
	OpExp(const Exp* left_, const char b_, const Exp* right_);
private:
    const Exp* left;
	const char b;
	const Exp* right;
};

class EseqExp : public Exp
{
public:
	EseqExp(const Statement* stm_, const Exp* exp_);
private:
	const Statement* stm;
	const Exp* exp;
};


#endif

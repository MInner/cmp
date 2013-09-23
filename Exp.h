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
	virtual int Exec(const VarTable* table) const{};
	virtual ~Exp();
};

class IdExp : public Exp
{
public:
	IdExp(const string s_);
    int Exec(const VarTable* table) const;
private:
    const string s;
};

class NumExp : public Exp
{
public:
	NumExp(const int a_);
	int Exec(const VarTable* table) const;
private:
    const int a;
};

class OpExp : public Exp
{
public:
	OpExp(const Exp* left_, const char b_, const Exp* right_);
	int Exec(const VarTable* table) const;
private:
    const Exp* left;
	const char b;
	const Exp* right;
};

class EseqExp : public Exp
{
public:
	EseqExp(const Statement* stm_, const Exp* exp_);
	int Exec(const VarTable* table) const;
private:
	const Statement* stm;
	const Exp* exp;
};


#endif

#pragma once

#include <string>
#include "all.h"
#include "Statement.h"
#include "ExpList.h"

using std::string;

class Exp
{
public:
	virtual IVPair Exec(const VarTable* table) const = 0;
	virtual ~Exp();
};

class IdExp : public Exp
{
public:
	IdExp(const string s_);
    IVPair Exec(const VarTable* table) const;
private:
    const string s;
};

class NumExp : public Exp
{
public:
	NumExp(const int a_);
	IVPair Exec(const VarTable* table) const;
private:
    const int a;
};

class OpExp : public Exp
{
public:
	OpExp(const Exp* left_, const char b_, const Exp* right_);
	IVPair Exec(const VarTable* table) const;
private:
    const Exp* left;
	const char b;
	const Exp* right;
};

class EseqExp : public Exp
{
public:
	EseqExp(const Statement* stm_, const Exp* exp_);
	IVPair Exec(const VarTable* table) const;
private:
	const Statement* stm;
	const Exp* exp;
};

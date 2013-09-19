#include <string>

using std::string;

class Exp
{
public:
	virtual int Execute();
	virtual ~Exp();
};

class IdExp : public Exp
{
public:
	string s;
	IdExp(string s_);
};

class NumExp : public Exp
{
public:
	int a;
	NumExp(int a_);
};

class OpExp : public Exp
{
public:
	Exp left;
	Exp right;
	char b;

	OpExp(Exp left_, char b_, Exp right_);
};
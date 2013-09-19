#include <string>

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
	const string s;
	IdExp(const string s_);
};

class NumExp : public Exp
{
public:
	const int a;
	NumExp(const int a_);
};

class OpExp : public Exp
{
public:
	const Exp* left;
	const char b;
	const Exp* right;

	OpExp(const Exp* left_, const char b_, const Exp* right_);
};

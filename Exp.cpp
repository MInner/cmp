#include "stm.h"
#include "ExpList.h"
#include "Exp.h"

IdExp::IdExp(const string s_) : s(s_) { }

NumExp::NumExp(const int a_) : a(a_) { }

OpExp::OpExp(const Exp* left_, const char b_, const Exp* right_): left(left_), b(b_), right(right_) {}

EseqExp::EseqExp(const Statement* stm_, const Exp* exp_) {}

Exp::~Exp() {}

#include "Exp.h"

IdExp::IdExp(string s_) : s(s_) { }

NumExp::NumExp(int a_) : a(a_) { }

OpExp::OpExp(Exp left_, char b_, Exp right_): left(left_), b(b_), right(right_) {}
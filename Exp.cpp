#include "Statement.h"
#include "ExpList.h"
#include "Exp.h"
#include "Vartable.h"
#include "all.h"

IdExp::IdExp(const string s_) : s(s_) { }

IVPair IdExp::Exec(const VarTable* table) const{
    return IVPair(table->getVar(this->s), table);
}

NumExp::NumExp(const int a_) : a(a_) { }

IVPair NumExp::Exec(const VarTable* table) const{
    return IVPair(this->a, table);
}

OpExp::OpExp(const Exp* left_, const char b_, const Exp* right_): left(left_), b(b_), right(right_) {}

IVPair OpExp::Exec(const VarTable* table) const{
    int ret;
    switch (this->b){
        case '+':
            ret =  this->left->Exec(table).first + this->right->Exec(table).first; break;
        case '-':
            ret = this->left->Exec(table).first - this->right->Exec(table).first; break;
        case '*':
            ret = this->left->Exec(table).first * this->right->Exec(table).first; break;
        case '/':
            ret = this->left->Exec(table).first / this->right->Exec(table).first; break;
        default:
            throw "No such binop";
    }

    return IVPair(ret, table);

    return IVPair(-1, table);
}

EseqExp::EseqExp(const Statement* stm_, const Exp* exp_): stm(stm_), exp(exp_){}

IVPair EseqExp::Exec(const VarTable* table) const{
    const VarTable* table1 = stm->Exec(table);
    return IVPair(this->exp->Exec(table1).first, table1);
}

Exp::~Exp() {};

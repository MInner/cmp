#include "Statement.h"
#include "ExpList.h"
#include "Exp.h"
#include "Vartable.h"

IdExp::IdExp(const string s_) : s(s_) { }

int IdExp::Exec(const VarTable* table) const{
    return table->getVar(this->s);
}

NumExp::NumExp(const int a_) : a(a_) { }

int NumExp::Exec(const VarTable* table) const{
    return this->a;
}

OpExp::OpExp(const Exp* left_, const char b_, const Exp* right_): left(left_), b(b_), right(right_) {}

int OpExp::Exec(const VarTable* table) const{
    switch (this->b){
        case '+':
            return this->left->Exec(table) + this->right->Exec(table);
        case '-':
            return this->left->Exec(table) - this->right->Exec(table);
        case '*':
            return this->left->Exec(table) * this->right->Exec(table);
        case '/':
            return this->left->Exec(table) / this->right->Exec(table);
    }
    throw "No such binop";
    return -1;
}

EseqExp::EseqExp(const Statement* stm_, const Exp* exp_): stm(stm_), exp(exp_){}

int EseqExp::Exec(const VarTable* table) const{
    const VarTable* table1 = stm->Exec(table);
    return this->exp->Exec(table1);
}

Exp::~Exp() {};

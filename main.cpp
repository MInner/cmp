#include <iostream>
#include "all.h"
#include "Exp.h"
#include "stm.h"
#include "ExpList.h"
#include "vartable.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    //  a = 5 + 3; b = ( print( a, a - 1), 10*a); print( b )

    //------assign a------------------
    NumExp* a5 = new NumExp(5);
    NumExp* a3 = new NumExp(3);
    OpExp* firPlus = new OpExp(a5, '+', a3);
    AssignStm* assignA = new AssignStm("a", firPlus);
    //------Last exp list----------------------
    IdExp* aId = new IdExp("a");
    NumExp* a1 = new NumExp(1);
    OpExp* lastExpMinus = new OpExp(aId, '-', a1);
    ExpList* lastExpList = new ExpList(lastExpMinus, NULL);
    //-----First Print stm------------------------
    IdExp* leftAId = new IdExp("a");
    ExpList* pairExpList = new ExpList(leftAId, lastExpList);
    PrintStm* firPrintStm = new PrintStm(pairExpList);
    //------Second Print stm-------------------------
    IdExp* bId = new IdExp("b");
    ExpList* bExpList = new ExpList(bId, NULL);
    PrintStm* secPrintStm = new PrintStm(bExpList);
    //------EseqExp--------------------
    IdExp* rightAId = new IdExp("a");
    NumExp* a10 = new NumExp(10);
    OpExp* expTimes = new OpExp(a10, 'x', rightAId);
    EseqExp* eseqExp = new EseqExp(firPrintStm, expTimes);
    //-------cmpStm----------------------------
    AssignStm* assignB = new AssignStm("b", eseqExp);
    CompoundStatement* cmpStm = new CompoundStatement(assignB, secPrintStm);
    //---------------topStm------------------
    CompoundStatement* topStm = new CompoundStatement(assignA, cmpStm);

    delete topStm;

    return 0;
}

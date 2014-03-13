#pragma once

#include "irtreevisitor.h"
#include "irtreenodes.h"

namespace IRTree
{

class StmExpList
{
public:
  StmExpList(const IStm* s, const ExpList* e) {stm=s; exps=e;}

  const IStm* stm;
  const ExpList* exps;

};

class Canon
{
public:

 bool isNop(const IStm* a) {
   const EXP* exp = dynamic_cast<const EXP*>(a);
   if (exp)
   {
        return (dynamic_cast<const CONST*>(exp->exp));
   }
 }

 const IStm* seq(const IStm* a,const IStm* b) {
    if (isNop(a)) return b;
    else if (isNop(b)) return a;
    else return new SEQ(a,b);
 }

 bool commute(const IStm* a,const IExp* b) {
    return isNop(a)
        || dynamic_cast<const NAME*>(b)
        || dynamic_cast<const CONST*>(b);
 }

 const IStm* do_stm(const SEQ* s) {  // частный слуйчай пропускаем реордер
	return seq(do_stm(s->left), do_stm(s->right)); // сразу идем в дочерние узлы
 }

 const IStm* do_stm(const MOVE* s) {
    const TEMP* tmp = dynamic_cast<const TEMP*>(s->dst);
    const CALL* call = dynamic_cast<const CALL*>(s->src);
    const ESEQ* eseq = dynamic_cast<const ESEQ*>(s->dst);

    if (tmp && call) // распознаем патерн temp - move - call
    {
        return reorder_stm(new MOVECALL(tmp, call));// засовываем его в особый новый узел
    }
    else if (eseq)
    {
        return do_stm(new SEQ(eseq->stm, new MOVE(eseq->exp, s->src)));
    }
    else
    {
        return reorder_stm(s);
    }
 }

 const IStm* do_stm(const EXP* s) {
     const CALL* call = dynamic_cast<const CALL*>(s->exp);
	if (call)
	{
        return reorder_stm(new EXPCALL(call));
	}
	else
	{
	    return reorder_stm(s);
	}
 }

 const IStm* do_stm(const IStm* s) {
     const SEQ* seq = dynamic_cast<const SEQ*>(s);
     const MOVE* move = dynamic_cast<const MOVE*>(s);
     const EXP* exp = dynamic_cast<const EXP*>(s);

     if (seq)
     {
        return do_stm(seq);
     }
     else if (move)
     {
         return do_stm(move);
     }
     else if (exp)
     {
         return do_stm(exp);
     }
     else
     {
         return reorder_stm(s);
     }
 }

 const IStm* reorder_stm(const IStm* s) {
     const StmExpList* x = reorder(s->kids());
     return seq(x->stm, s->build(x->exps));
 }


 const ESEQ* do_exp(const ESEQ* e) {
      const IStm* stms = do_stm(e->stm);
      const ESEQ* b = do_exp(e->exp);
      return new ESEQ(seq(stms,b->stm), b->exp);
  }

 const ESEQ* do_exp (const IExp* e) {
    const ESEQ* eseq = dynamic_cast<const ESEQ*>(e);
    if (eseq)
    {
        return do_exp(eseq);
    }
    else
    {
        return reorder_exp(e);
    }
 }

 const ESEQ* reorder_exp (const IExp* e) {
     const StmExpList* x = reorder(e->kids());
     return new ESEQ(x->stm, e->build(x->exps));
 }
/**/


 const StmExpList* reorder(const ExpList* exps) {
     if (exps==nullptr)
     {
         return new StmExpList(new EXP(new CONST(0)),NULL);
     }
     else
     {
        const IExp* a = exps->head;
        const CALL* call = dynamic_cast<const CALL*>(a);
        if (call)
        {
            const Temp::Temp* t = new Temp::Temp();
            const IExp* e = new ESEQ(new MOVE(new TEMP(t), call), new TEMP(t));
            return reorder(new ExpList(e, exps->tail));
        }
        else
        {
            const ESEQ* aa = do_exp(a);
            const StmExpList* bb = reorder(exps->tail);
            if (commute(bb->stm, aa->exp))
            {
                return new StmExpList(seq(aa->stm,bb->stm),
                        new ExpList(aa->exp,bb->exps));
            }
            else
            {
                const Temp::Temp* t = new Temp::Temp();
                return new StmExpList(
                  seq(aa->stm,
                    seq(new MOVE(new TEMP(t),aa->exp),
                     bb->stm)),
                  new ExpList(new TEMP(t), bb->exps));
            }
       }
     }
 }


 const StmList* linear(const SEQ* s, const StmList* l) {
      return linear(s->left,linear(s->right,l));
 }

 const StmList* linear(const IStm* s, const StmList* l) {
    const SEQ* seq = dynamic_cast<const SEQ*>(s);
    if (seq)
    {
        return linear(seq, l);
    }
    else
    {
        return new StmList(s,l);
    }
 }

 const StmList* linearize(const IStm* s) {
    return linear(do_stm(s), NULL);
 }

 const IStm* getLinearTree(const IStm* s) { // лишний шаг только для визуализации
    const StmList* list = linearize(s);
    const IStm* ret = list->head;
    for(const StmList* currStm = list->tail; currStm != nullptr; currStm = currStm->tail) {
        ret = new SEQ(ret, currStm->head);
    }
    return ret;
 }

 CodeFragment* linearCF(const CodeFragment* mainCodeFragment) {
    CodeFragment* currentCodeFragment = new CodeFragment(mainCodeFragment->frame);
	CodeFragment* newCF = currentCodeFragment;
	for(auto currentOldCodeFragment = mainCodeFragment;
	        currentOldCodeFragment != nullptr; currentOldCodeFragment = currentOldCodeFragment->next )
	{
	    if (const IExp* ret = currentOldCodeFragment->retval)
			{
			    const ESEQ* eseq = dynamic_cast<const ESEQ*>(ret);
				currentCodeFragment->body = getLinearTree(
                    new SEQ( new EXP(currentOldCodeFragment->retval),
                        new MOVE(new TEMP(new Temp::Temp("RV")), eseq->exp)
				)
                );
                currentCodeFragment->retval = NULL;
			}
			else
			{
				assert(currentCodeFragment->body); // never used
				currentCodeFragment->body = getLinearTree(
                    new SEQ(currentCodeFragment->body,
                        new MOVE(new TEMP(new Temp::Temp("RV")), new CONST(0))
				)
                );
			}

        currentCodeFragment->stmlist = linearize(currentCodeFragment->body);

		if (currentOldCodeFragment->next)
		{
			CodeFragment* newFragment = new CodeFragment(currentOldCodeFragment->next->frame);
			currentCodeFragment->next = newFragment;
			currentCodeFragment = newFragment;
		}

	}
	return newCF;
 }

};

}
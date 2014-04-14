#pragma once

#include "irtreevisitor.h"
#include "irtreenodes.h"
#include <vector>

namespace IRTree
{

class StmExpList
{
public:
  StmExpList(const IStm* s, const ExpList* e) {stm=s; exps=e;}

  const IStm* stm;
  const ExpList* exps;

};

class Block
{
public:
  //Block(): stms(NULL), next(nullptr), labelName(NULL), jumpName(NULL) {}

  std::vector<const IStm*>* stms;
  Block* next;
  Block* prev;
  std::string labelName;
  std::string jumpName;
  bool isCJump;
};

class Canon
{
public:

 Block* generateBlocks(const StmList* list){
    Block* firstBlock = new Block();
    firstBlock->stms =  new std::vector<const IStm*>();
    firstBlock->prev = nullptr;
    Block* currentBlock = firstBlock;
    Block* newBlock;
    for(const StmList* currStm = list; true; currStm = currStm->tail) {
        const LABEL* label = dynamic_cast<const LABEL*>(currStm->head);
        const CJUMP* cjump = dynamic_cast<const CJUMP*>(currStm->head);
        const JUMP*  jump  = dynamic_cast<const  JUMP*>(currStm->head);
        if (label) {
           newBlock = new Block();
           newBlock->stms =  new std::vector<const IStm*>();
           currentBlock->next = newBlock;
           newBlock->prev = currentBlock;
           newBlock->next = nullptr;

           newBlock->stms->push_back(label);
           newBlock->labelName = std::string(label->label->name);

           currentBlock = newBlock;

        } else if (jump) {
            currentBlock->isCJump = false;
            currentBlock->stms->push_back(jump);

            const NAME* jLabel = dynamic_cast<const NAME*>(jump->exp);
            if (jLabel){
                currentBlock->jumpName = jLabel->label->name;
            } else {
                assert(0);
            }
        } else if (cjump) {
            currentBlock->isCJump = true;
            currentBlock->stms->push_back(cjump);

            currentBlock->jumpName = cjump->iffalse->name;
        } else {
            currentBlock->stms->push_back(currStm->head);
        }

        if (!currStm->tail) {
            break;
        }
    }

    return firstBlock;
 }

Block* getLastBlock(Block* firstBlock){
    for(Block* currBl = firstBlock; currBl != nullptr; currBl = currBl->next) {
        if (!currBl->next) {
            return currBl;
        }
    }
}


Block* findBlockByJumpName(std::string name, Block* firstBlock){
    for(Block* currBl = firstBlock; currBl != nullptr; currBl = currBl->next) {
        if (currBl->jumpName == name) {
            return currBl;
        }
    }
}


Block* findBlockByLabelName(std::string name, Block* firstBlock){
    for(Block* currBl = firstBlock; currBl != nullptr; currBl = currBl->next) {
        //std::cout << currBl->labelName << std::endl;
        if (currBl->labelName == name) {
            return currBl;
        }
    }
}

void swapBlocks(Block* f, Block* s){
    Block* a = new Block();
    std::cout << "1 " << f->labelName << " " << s->labelName << " I'm here \n";
    a->stms = f->stms;
    f->stms = s->stms;
    s->stms = a->stms;

    a->isCJump = f->isCJump;
    f->isCJump = s->isCJump;
    s->isCJump = a->isCJump;

    a->labelName = f->labelName;
    f->labelName = s->labelName;
    s->labelName = a->labelName;

    a->jumpName = f->jumpName;
    f->jumpName = s->jumpName;
    s->jumpName = a->jumpName;
}

void reorderBlocks(Block* firstBlock) {
   //Block* a = findBlockByLabelName("start", firstBlock);
   //Block* a = findBlockByJumpName("finish", firstBlock);
   // swapBlocks(firstBlock, getLastBlock(firstBlock));
   //int b;
   //b = 7;
   for(Block* currBl = firstBlock; currBl != nullptr; currBl = currBl->next) {
        //std::cout << currBl->labelName << std::endl;
        if (currBl->isCJump) {
            Block* b = findBlockByLabelName(currBl->jumpName, firstBlock);
            swapBlocks(currBl->next, b);
        }
    }
}

const StmList* combineBlocks(Block* lastBlock) {
    const StmList* list = nullptr;
    for(Block* currBl = lastBlock; currBl != nullptr; currBl = currBl->prev) {
        for(int i = currBl->stms->size() - 1; i >=0 ; i--) {
            list = new StmList(currBl->stms->at(i), list);
        }
    }
    return list;
}

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

 const IStm* getLinearTree1(const IStm* s) { // лишний шаг только для визуализации
    const StmList* list = linearize(s);

    bool inBlock = true;
    const IStm* ret = list->head;
    const LABEL* label = dynamic_cast<const LABEL*>(ret);
    if (!label) {
        ret = new SEQ(new LABEL(new Temp::Label("start")), ret);
    }

    for(const StmList* currStm = list->tail; currStm != nullptr; currStm = currStm->tail) {
        const LABEL* label = dynamic_cast<const LABEL*>(currStm->head);
        const CJUMP* cjump = dynamic_cast<const CJUMP*>(currStm->head);
        const JUMP*  jump  = dynamic_cast<const  JUMP*>(currStm->head);
        if (label) {
            if (inBlock) {
                ret = new SEQ(ret, new SEQ(new JUMP(label), currStm->head));
            } else {
                inBlock = true;
                ret = new SEQ(ret, currStm->head);
            }
        } else if (jump || cjump) {
            if (inBlock) {
                inBlock = false;
                ret = new SEQ(ret, currStm->head);
            } else {
                assert(0); // no sense
            }
        } else {
            ret = new SEQ(ret, currStm->head);
        }
        if (currStm->tail == NULL){
            const LABEL* rl = new LABEL(new Temp::Label("finish"));
            ret = new SEQ(ret, new JUMP(rl));
        }
    }

    if (list->tail == nullptr) {
        const LABEL* rl = new LABEL(new Temp::Label("finish"));
        ret = new SEQ(ret, new JUMP(rl));
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
				currentCodeFragment->body = getLinearTree1(
                    new SEQ( new EXP(currentOldCodeFragment->retval),
                        new MOVE(new TEMP(new Temp::Temp("RV")), eseq->exp)
				)
                );
                currentCodeFragment->retval = NULL;
			}
			else
			{
				assert(currentCodeFragment->body); // never used
				currentCodeFragment->body = getLinearTree1(
                    new SEQ(currentCodeFragment->body,
                        new MOVE(new TEMP(new Temp::Temp("RV")), new CONST(0))
				)
                );
			}

        currentCodeFragment->stmlist = linearize(currentCodeFragment->body);
        Block* b = generateBlocks(currentCodeFragment->stmlist);
        reorderBlocks(b);
        Block* lb = getLastBlock(b);
        currentCodeFragment->stmlist = combineBlocks(lb);

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

#pragma once

#include "irtreevisitor.h"
#include "irtreenodes.h"

#include <iostream>

#define log(str) std::cout << padding << std::string(padding++, '-') << "|: " << str << std::endl;

#define end() padding--;

namespace IRTree
{

class IRTreeLineorisatorVisitor : public ITreeVisitor 
{
public:
	IRTreeLineorisatorVisitor(): stmtmp(0), exptmp(0), newCF(0), padding(0) {}

	virtual ~IRTreeLineorisatorVisitor() {}

	CodeFragment* getOptimizedCodeFramgent()
	{
		return newCF;
	}

	int visit(const CodeFragment* codeFragment)
	{
		log("CF");
		CodeFragment* currentCodeFragment = new CodeFragment(codeFragment->frame);
		newCF = currentCodeFragment;
		for(auto currentOldCodeFragment = codeFragment; 
		        currentOldCodeFragment != nullptr; currentOldCodeFragment = currentOldCodeFragment->next ) 
		{
			currentOldCodeFragment->retval->Accept( this );
			currentCodeFragment->retval = exptmp;
			if (currentOldCodeFragment->next)
			{
				CodeFragment* newFragment = new CodeFragment(currentOldCodeFragment->next->frame);
				currentCodeFragment->next = newFragment;
				currentCodeFragment = newFragment;
			}

		}
		end();
	}

	int visit(const CONST* n)
	{
		log("CONST");
		exptmp = n;
		end();
	}

	int visit(const NAME* n)
	{
		log("NAME");
		exptmp = n;
		end();
	}
	
	int visit(const TEMP* n)
	{
		log("TEMP");
		exptmp = n;
		end();
	}
	
	int visit(const BINOP* n)
	{
		log("BINOP");
		n->left->Accept( this );
		const IExp* tmp_left = exptmp;
		n->right->Accept( this );
		const IExp* tmp_right = exptmp;
		exptmp = new BINOP(n->binop, tmp_left, tmp_right);
		end();
	}
	
	int visit(const MEM* n)
	{
		log("MEM");
		n->exp->Accept( this );
		exptmp = new MEM(exptmp);
		end();
	}
	
	int visit(const CALL* n)
	{
		log("CALL");
		ExpList* arg_el = NULL;
		if( n->args != nullptr ) {
			n->args->Accept( this );
			arg_el = explisttmp;
		}
		exptmp = new CALL(n->func, arg_el);
		end();
	}
	
	int visit(const ESEQ* n)
	{
		log("ESEQ");
		n->stm->Accept( this );
		n->exp->Accept( this );
		exptmp = new ESEQ(stmtmp, exptmp);
		// TODO here
		end();
	}

	int visit(const MOVE* n)
	{
		log("MOVE");
		n->dst->Accept( this );
		const IExp* dst = exptmp;
		n->src->Accept( this );
		const IExp* src = exptmp;

		// MOVE(dist, ESEQ(s, e))
		if (const ESEQ* esq = dynamic_cast<const ESEQ*>(src))
		{
			std::cout << "Found MOVE(dist, ESEQ(s, e))" << std::endl;
			const IStm* s = esq->stm;
			const IExp* e = esq->exp;
			if (comutate(s, dst))
			{
				stmtmp = new SEQ(s, new MOVE(dst, e)); // SEQ(s, MOVE(dist, e))
				return 0;
			}
			else
			{
				Temp::Temp* t1 = new Temp::Temp();
				stmtmp = new SEQ(
					new MOVE(
						new TEMP(t1), 
						dst),
					new SEQ(
						s,
						new MOVE(
							new TEMP(t1),
							e
						)
					)
				);
				return 0;
				// SEQ( MOVE (TEMP1, dist) , SEQ( s, MOVE (TEMP1, e) ) )
			}
		}

		stmtmp = new MOVE(dst, src);
		end();
	}
	
	int visit(const EXP* n)
	{
		log("EXP");
		n->exp->Accept( this );
		stmtmp = new EXP(exptmp);
		end();
	}
	
	int visit(const JUMP* n)
	{
		log("JUMP");
		n->exp->Accept( this );
		stmtmp = new JUMP(exptmp, n->targets);
		end();
	}
	
	int visit(const CJUMP* n)
	{
		log("CJUMP");
		n->left->Accept(this);
		const IExp* tmp_left = exptmp;
		n->right->Accept(this);
		const IExp* tmp_right = exptmp;
		stmtmp = new CJUMP(n->relop, tmp_left, tmp_right, n->iftrue, n->iffalse);
		end();
	}
	
	int visit(const SEQ* n)
	{
		log("SEQ");
		n->left->Accept(this);
		const IStm* tmp_left = stmtmp;

		n->right->Accept(this);
		const IStm* tmp_right = stmtmp;

		// SEQ( SEQ(a,b) , c ) => SEQ(a, SEQ(b, c) )
		if (const SEQ* s1 = dynamic_cast<const SEQ*>(tmp_left)) // SEQ(a,b) = s1
		{
			const SEQ* s2 = dynamic_cast<const SEQ*>(tmp_right);
			if ( !s2 ) // c != SEQ
			{
				std::cout << "Found SEQ( SEQ(a,b) , c ) " << std::endl;
				stmtmp = new SEQ(s1->left, new SEQ(s1->right, tmp_right) );
				return 0;
				// n = NULL;
			}	
		}
		stmtmp = new SEQ(tmp_left, tmp_right);
		end();
	}
	
	int visit(const LABEL* n)
	{
		log("LABEL");
		stmtmp = n;
		end();
	}

	int visit(const ExpList* expList)
	{
		log("ExpList");
		if (expList != NULL)
		{
			ExpList* el = new ExpList(NULL);
			ExpList* first = el;
			for( auto exp = expList; exp != nullptr && exp->head != nullptr; exp = exp->tail ) {
				exp->head->Accept(this);
				el->head = exptmp;
				if (exp->tail)
				{
					ExpList* newExpList = new ExpList(NULL);
					el->tail = newExpList;
					el = newExpList;
				}
				else
				{
					el->tail = NULL;
				}
			}
			explisttmp = first;
		}
		else
			explisttmp = NULL;
		end();
	}
	
	int visit(const StmList* stmList)
	{
		log("StmList");
		StmList* sl = new StmList(NULL);
		for( auto stm = stmList; stm != nullptr && stm->head != nullptr; stm = stm->tail ) {
			stm->head->Accept(this);
			sl->head = stmtmp;
			sl = new StmList(NULL, sl);
		}
		end();
	}

	bool comutate(const IStm* s, const IExp* e)
	{
		return false;
		// stub here !
	}

private:
	const IStm* stmtmp;
	const IExp* exptmp;
	CodeFragment* newCF;
	ExpList* explisttmp;
	int padding;
};

}

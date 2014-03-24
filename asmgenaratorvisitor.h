#pragma once

#include "irtreevisitor.h"
#include "irtreenodes.h"
#include "asmfragment.h"

#include <iostream>

#define log(str) std::cout << padding << std::string(padding++, '-') << "|: " << str << std::endl;

#define end() padding--;

namespace Assemble
{

class AsmGenaratorVisitor : public IRTree::ITreeVisitor
{
public:
	AsmGenaratorVisitor(): padding(0) {}

	virtual ~AsmGenaratorVisitor() {}

	int visit(const IRTree::CodeFragment* codeFragment)
	{
		for(auto currentCodeFragment = codeFragment; 
		        currentCodeFragment != nullptr; currentCodeFragment = currentCodeFragment->next ) 
		{
			auto newasmf = new AsmFragment();
			if (!root)
				root = newasmf;

			// keep writing here !te
			
			log("CF" + currentCodeFragment->frame->getName()->name);
			currentCodeFragment->stmlist->Accept( this );
			end();
		}
	}

	int visit(const IRTree::CONST* n)
	{
		log("CONST");
		Temp::Temp* t = new Temp::Temp();

		end();
	}

	int visit(const IRTree::NAME* n)
	{
		log("NAME");
		end();
	}
	
	int visit(const IRTree::TEMP* n)
	{
		log("TEMP");
		end();
	}
	
	int visit(const IRTree::BINOP* n)
	{
		log("BINOP");
		n->left->Accept( this );
		n->right->Accept( this );
		// 
		end();
	}
	
	int visit(const IRTree::MEM* n)
	{
		log("MEM");
		if (auto e = dynamic_cast<const IRTree::BINOP*>(n->exp))
		{
			if (auto r = dynamic_cast<const IRTree::CONST*>(e->right))
			{
				// MEM(BINOP(op, exp, CONST(c))) => MOV t0, [t1 op c] % (TEMP, exp) => t0
			}
		}

		// MEM(a) => MOV t0, [t1] % (TEMP, exp) => to
		n->exp->Accept( this );
		end();
	}
	
	int visit(const IRTree::CALL* n)
	{
		log("CALL");
	    n->args->Accept( this ); // packed here
	    // CALL funcname => RV
		end();
	}
	
	int visit(const IRTree::ESEQ* n)
	{
		log("ESEQ");
		n->stm->Accept( this );
		n->exp->Accept( this );
		end();
	}

	int visit(const IRTree::MOVE* n)
	{
		log("MOVE");
		if (auto l = dynamic_cast<const IRTree::MEM*>(n->dst))
		{
			if (auto r = dynamic_cast<const IRTree::MEM*>(n->src))
			{
				// MOVE(MEM(a), MEM(b)) => MOV t0, [t1]; MOV [t2], t0 % (TEMP, a, b) => NULL
			}
			else
			{
				// MOVE(MEM(a), b) => MOV [t0], t1 % (a, b) => NULL
			}
		}
		else
		{
			if (auto r = dynamic_cast<const IRTree::MEM*>(n->src))
			{
				if (auto b = dynamic_cast<const IRTree::BINOP*>(r->exp))
				{
					if (auto br = dynamic_cast<const IRTree::CONST*>(b->right))
					{
						// MOVE(a, MEM(BINOP(op, exp, CONST(c)))) => MOV t0, [t1 op c] % (a, exp) => NULL
					}
				}
				else
				{
					// MOVE(a, MEM(b)) => MOV t0, [t1] % (a, b) => NULL 
				}
			}
			else
			{
				// MOVE (a, b) => MOV t0, t1 % (a, b) => NULL
			}
		}

		if (auto r = dynamic_cast<const IRTree::CONST*>(n->src))
		{
			// MOVE ( a, CONST(c) ) => MOV t0, c % (a) => NULL
		}
		n->dst->Accept(this);
		n->src->Accept(this);
		end();
	}
	
	int visit(const IRTree::EXP* n)
	{
		log("EXP");
		n->exp->Accept( this );
		// => NOP => NULL
		end();
	}
	
	int visit(const IRTree::JUMP* n)
	{
		log("JUMP");
		n->exp->Accept( this );
		// => JMP t0 % (exp) => NULL
		end();
	}
	
	int visit(const IRTree::CJUMP* n)
	{
		log("CJUMP");
		n->left->Accept(this);
		n->right->Accept(this);
		// CMP t0, t1 % (left, right)
		switch( n->relop )
		{
			case 0: // ==
				// JE truelabela
				break;
			case 1: // !=
				break;
			case 2: // <
				break;
			case 3: // >
				break;
			case 4: // <=
				break;
			case 5: // >=
				break;
		}
		end();
	}
		
	int visit(const IRTree::LABEL* n)
	{
		log("LABEL");
		// => label :
		end();
	}

	int visit(const IRTree::ExpList* expList)
	{
		log("ExpList");
		if (expList != NULL)
		{
			for( auto exp = expList; exp != nullptr && exp->head != nullptr; exp = exp->tail ) {
				exp->head->Accept(this);
				// => PUSH t0 % (exp) => NULL
			}
		}
		end();
	}
	
	int visit(const IRTree::StmList* stmList)
	{
		log("StmList");
		for( auto stm = stmList; stm != nullptr && stm->head != nullptr; stm = stm->tail ) {
			stm->head->Accept(this);
		}
		end();
	}

	int visit(const IRTree::SEQ* s) {}
	int visit(const IRTree::MOVECALL* s) {}
	int visit(const IRTree::EXPCALL* s) {}


private:
	int padding;
	AsmFragment* root;
	AsmFragment* asmf;
};

}
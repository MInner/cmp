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
		end();
	}
	
	int visit(const IRTree::MEM* n)
	{
		log("MEM");
		n->exp->Accept( this );
		end();
	}
	
	int visit(const IRTree::CALL* n)
	{
		log("CALL");
	    n->args->Accept( this );
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
		n->dst->Accept(this);
		n->src->Accept(this);
		end();
	}
	
	int visit(const IRTree::EXP* n)
	{
		log("EXP");
		n->exp->Accept( this );
		end();
	}
	
	int visit(const IRTree::JUMP* n)
	{
		log("JUMP");
		n->exp->Accept( this );
		end();
	}
	
	int visit(const IRTree::CJUMP* n)
	{
		log("CJUMP");
		n->left->Accept(this);
		n->right->Accept(this);
		end();
	}
		
	int visit(const IRTree::LABEL* n)
	{
		log("LABEL");
		end();
	}

	int visit(const IRTree::ExpList* expList)
	{
		log("ExpList");
		if (expList != NULL)
		{
			for( auto exp = expList; exp != nullptr && exp->head != nullptr; exp = exp->tail ) {
				exp->head->Accept(this);
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
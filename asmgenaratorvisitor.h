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
	AsmGenaratorVisitor(): padding(0), root(0), curasmf(0) {}

	virtual ~AsmGenaratorVisitor() {}

	int visit(const IRTree::CodeFragment* codeFragment)
	{
		for(auto currentCodeFragment = codeFragment; 
		        currentCodeFragment != nullptr; currentCodeFragment = currentCodeFragment->next ) 
		{
			auto newasmf = new AsmFragment();
			if (!root)
			{
				root = newasmf;
				curasmf = newasmf;
			}
			else
			{
				curasmf->next = newasmf;
				curasmf = newasmf;
			}
			
			log("CF" + currentCodeFragment->frame->getName()->name);
			currentCodeFragment->stmlist->Accept( this );

			end();
		}
	}

	int visit(const IRTree::CONST* n)
	{
		log("CONST");
		// CONST(c) => MOVE d0, c => d0
		Temp::Temp* d0 = new Temp::Temp();
		std::ostringstream ss;
		ss << "MOV d0, " << n->value;
		curasmf->addInstruction(
			new Assemble::MOVE(ss.str().c_str(), 
								NULL, 
								new Temp::TempList(d0)
			)
		);
		tmp = d0;
		end();
	}

	int visit(const IRTree::NAME* n)
	{
		log("NAME");
		end();
	}
	
	int visit(const IRTree::TEMP* n)
	{
		// TEMP(t) => // => t
		log("TEMP");
		tmp = n->temp;
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
		if (auto b = dynamic_cast<const IRTree::BINOP*>(n->exp))
		{
			if (auto c = dynamic_cast<const IRTree::CONST*>(b->right))
			{
				// MEM(BINOP(op, exp, CONST(c))) => MOV d0, [u0 op c] % (u0 = exp // d0 = TEMP) => d0
				if (b->binop == 0) // +
				{
					Temp::Temp* d0 = new Temp::Temp();
					b->left->Accept(this);
					auto u0 = tmp;
					std::ostringstream ss;
					ss << "MOV d0, [t0 + " << c->value << ']';
					curasmf->addInstruction(new Assemble::MOVE(ss.str().c_str(), 
											new Temp::TempList(u0), 
											new Temp::TempList(d0)));
					tmp = d0;
					return 0;
				}
			}
		}

		// MEM(a) => MOV d0, [u0] % (exp // TEMP) => d0
		Temp::Temp* d0 = new Temp::Temp();
		n->exp->Accept( this );
		auto u0 = tmp;
		curasmf->addInstruction(new Assemble::MOVE("MOV d0, [t0]", 
								new Temp::TempList(u0), 
								new Temp::TempList(d0)));
		tmp = d0;
		end();
	}
	
	int visit(const IRTree::CALL* n)
	{
		log("CALL");
	    n->args->Accept( this ); // packed here
	    // CALL funcname => RV
	    std::ostringstream ss;
	    ss << "CALL " << n->func->name;
	    curasmf->addInstruction(new Assemble::ASM(ss.str().c_str(), 
	    											NULL, 
	    											NULL));

	    tmp = new Temp::Temp("RV");
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
		if (auto m1 = dynamic_cast<const IRTree::MEM*>(n->dst))
		{
			if (auto m2 = dynamic_cast<const IRTree::MEM*>(n->src))
			{
				std::cout << "MOVE(MEM(a), MEM(b)) => MOV t0, [t1]; MOV [t2], t0 | (TEMP, a, b) => NULL" << std::endl;

				assert(false); //stub
			}
			else
			{
				if (auto bn = dynamic_cast<const IRTree::BINOP*>(m1->exp))
				{
					if (auto br = dynamic_cast<const IRTree::CONST*>(bn->right))
					{
						if (bn->binop == 0)//+
						{
							if (auto c2 = dynamic_cast<const IRTree::CONST*>(n->src))
							{
								std::cout << "MOVE(MEM(BINOP(exp, op, CONST(c))), CONST(c2)) => MOV [u0 op c], c2 | (exp) => NULL" << std::endl;
								bn->left->Accept(this);
								auto exp = tmp;
								std::ostringstream ss;
								ss << "MOV [u0 + " << br->value << "], " << c2->value; 
								curasmf->addInstruction(new Assemble::MOVE(ss.str().c_str(), new Temp::TempList(exp), NULL));
								tmp = NULL;
								return 0;
							}
							else
							{
								std::cout << "MOVE(MEM(BINOP(exp, op, CONST(c))), a) => MOV [u0 op c], u1 | (exp, a) => NULL" << std::endl;
								n->src->Accept(this);
								auto a = tmp;
								bn->left->Accept(this);
								auto exp = tmp;
								std::ostringstream ss;
								ss << "MOV [u0 + " << br->value << "], u1"; 
								curasmf->addInstruction(new Assemble::MOVE(ss.str().c_str(), new Temp::TempList(exp, a), NULL));
								tmp = NULL;
								return 0;
							}
						}
					}
				}
				else
				{
					std::cout << "MOVE(MEM(a), b) => MOV [u0], u1 | (a, b) => NULL" << std::endl;

					m1->exp->Accept(this);
					auto a = tmp;
					n->src->Accept(this);
					auto b = tmp;
					curasmf->addInstruction(new Assemble::MOVE("MOV [u0], u1", new Temp::TempList(a, b), NULL));
					tmp = NULL;
					return 0;
				}
			}
		}
		else
		{
			if (auto r = dynamic_cast<const IRTree::MEM*>(n->src))
			{
				if (auto bn = dynamic_cast<const IRTree::BINOP*>(r->exp))
				{
					if (auto br = dynamic_cast<const IRTree::CONST*>(bn->right))
					{
						if (bn->binop == 0) // +
						{
							std::cout << "MOVE(a, MEM(BINOP(op, exp, CONST(c)))) => MOV u0, [u1 op c] | (a, exp) => NULL" << std::endl;

							n->dst->Accept(this);
							auto a = tmp;
							bn->left->Accept(this);
							auto exp = tmp;
							std::ostringstream ss;
							ss << "MOV u0, [u1 + " << br->value << "]"; 
							curasmf->addInstruction(new Assemble::MOVE(ss.str().c_str(), new Temp::TempList(a, exp), NULL));
							tmp = NULL;
							return 0;
						}

					}
				}
				else
				{
					std::cout << "MOVE(a, MEM(b)) => MOV t0, [t1] | (a, b) => NULL" << std::endl;

					n->dst->Accept(this);
					auto a = tmp;
					r->exp->Accept(this);
					auto b = tmp;
					curasmf->addInstruction(new Assemble::MOVE("MOVE t0, [t1]", new Temp::TempList(a, b), NULL));
					tmp = NULL;
					return 0;
				}
			}
		}

		if (auto c = dynamic_cast<const IRTree::CONST*>(n->src))
		{
			std::cout << "MOVE (a, CONST(c)) => MOV t0, c | (a) => NULL" << std::endl;
			std::ostringstream ss;
			ss << "MOVE t0, " << c->value;
			n->dst->Accept(this);
			curasmf->addInstruction(new Assemble::MOVE(ss.str().c_str(), new Temp::TempList(tmp), NULL));
			tmp = NULL;
			return 0;
		}

		std::cout << "MOVE (a, b) => MOV t0, t1 | (a, b) => NULL" << std::endl;
		n->dst->Accept(this);
		auto a = tmp;
		n->src->Accept(this);
		auto b = tmp;
		curasmf->addInstruction(new Assemble::MOVE("MOVE t0, t1", new Temp::TempList(a, b), NULL));
		tmp = NULL;

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
		if (auto nm = dynamic_cast<const IRTree::NAME*>(n->exp))
		{
			std::cout << "JUMP (NAME (n)) => JMP n => NULL" << std::endl;
			std::ostringstream ss;
			ss << "JMP " << nm->label->name;
			curasmf->addInstruction(new Assemble::ASM(ss.str().c_str(), NULL, NULL));
			tmp = NULL;
			return 0;
		}
		n->exp->Accept( this );
		std::cout << "JUMP(exp) => JMP t0 | (exp) => NULL" << std::endl;
		curasmf->addInstruction(new Assemble::ASM("JMP u0", new Temp::TempList(tmp), NULL));
		tmp = NULL;
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
		curasmf->addInstruction(new Assemble::LABEL(n->label));
		end();
	}

	int visit(const IRTree::ExpList* expList)
	{
		log("ExpList");
		if (expList != NULL)
		{
			for( auto exp = expList; exp != nullptr && exp->head != nullptr; exp = exp->tail ) {
				if ( auto c = dynamic_cast<const IRTree::CONST*>(exp->head) )
				{
					std::cout << "func ( .. CONST c .. ) => PUSH c => NULL" << std::endl;
					std::ostringstream ss;
					ss << "PUSH " << c->value;
					curasmf->addInstruction(new Assemble::ASM(ss.str().c_str(), NULL, NULL));
					tmp = NULL;
					continue;
				}

				exp->head->Accept(this);
				std::cout << "func ( .. exp .. ) => PUSH t0 | (exp) => NULL" << std::endl;
				curasmf->addInstruction(new Assemble::ASM("PUSH u0", new Temp::TempList(tmp), NULL));
				tmp = NULL;
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
	AsmFragment* curasmf;
	const Temp::Temp* tmp;
};

}
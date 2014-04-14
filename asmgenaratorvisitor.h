#pragma once

#include "irtreevisitor.h"
#include "irtreenodes.h"
#include "asmfragment.h"

#include <iostream>

//#define log(str) std::cout << padding << std::string(padding++, '-') << "|: " << str << std::endl;
#define log(str)

// #define debug(str) std::cout << str << std::endl;
#define debug(str) ; 

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
			
			debug("!!!--------- CF: " << currentCodeFragment->frame->getName()->name << "------------!!!");
			currentCodeFragment->stmlist->Accept( this );

		}
	}

	int visit(const IRTree::CONST* n)
	{
		log("CONST");
		debug("// CONST(c) => MOVE d0, c => d0");
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
		// it souldn't be here
		assert(false);
		log("NAME");
		end();
	}
	
	int visit(const IRTree::TEMP* n)
	{
		debug("// TEMP(t) => // => t");
		log("TEMP");
		tmp = n->temp;
		end();
	}
	
	int visit(const IRTree::BINOP* n)
	{
		log("BINOP");
		debug("// a BINOP b => MOVE d0, a; MOVE d1, b; BINOP d0, d1; MOVE d2, d0 => d2");
		n->left->Accept( this );
		auto a = tmp;
		n->right->Accept( this );
		auto b = tmp;
		auto d0 = new Temp::Temp();
		switch ( n->binop )
		{
			case 0: // +
				curasmf->addInstruction(new Assemble::MOVE("MOVE d0, u0", new Temp::TempList(a), new Temp::TempList( d0 ) ));
				curasmf->addInstruction(new Assemble::MOVE("ADD u0, u1", new Temp::TempList(d0), new Temp::TempList( b ) ));
				// now the sum lives in d0: ADD u0, u1 => u0 = u0 + u1
				tmp = d0;
				return 0;
			case 1: // -
				curasmf->addInstruction(new Assemble::MOVE("MOVE d0, u0", new Temp::TempList(a), new Temp::TempList( d0 ) ));
				curasmf->addInstruction(new Assemble::MOVE("SUB u0, u1", new Temp::TempList(d0), new Temp::TempList( b ) ));
				// now the sub lives in d0: ADD u0, u1 => u0 = u0 + u1
				tmp = d0;
				return 0;
			case 2: // *
				curasmf->addInstruction(new Assemble::MOVE("MOVE AL, u0", new Temp::TempList(a) ));
				curasmf->addInstruction(new Assemble::MOVE("MUL u0", new Temp::TempList(b) ));
				curasmf->addInstruction(new Assemble::MOVE("MOVE d0, AX", NULL, new Temp::TempList(d0) ));
				tmp = d0;
				return 0;
			default:
				// souldn't be here
				assert(false);
		}
		end();
	}
	
	int visit(const IRTree::MEM* n)
	{
		log("MEM");
		if (auto b = dynamic_cast<const IRTree::BINOP*>(n->exp))
		{
			if (auto c = dynamic_cast<const IRTree::CONST*>(b->right))
			{
				debug( "// MEM(BINOP(op, exp, CONST(c))) => MOV d0, [u0 op c] | (u0 = exp // d0 = TEMP) => d0 " );
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

		debug( "// MEM(a) => MOV d0, [u0] | (exp // TEMP) => d0" );
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
	    debug("// CALL funcname => RV")
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
		// it souldn't be here
		assert(false);
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
				debug("// MOVE(MEM(a), MEM(b)) => MOV t0, [t1]; MOV [t2], t0 | (TEMP, a, b) => NULL")

				m1->exp->Accept(this);
				auto a = tmp;
				m2->exp->Accept(this);
				auto b = tmp;
				auto t0 = new Temp::Temp();
				curasmf->addInstruction(new Assemble::MOVE("MOV [d0], u0", new Temp::TempList(a), new Temp::TempList(t0)));
				curasmf->addInstruction(new Assemble::MOVE("MOV [u0], u1", new Temp::TempList(b, t0), NULL));
				tmp = NULL;
				return 0;
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
								debug("// MOVE(MEM(BINOP(exp, op, CONST(c))), CONST(c2)) => MOV [u0 op c], c2 | (exp) => NULL")
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
								debug("// MOVE(MEM(BINOP(exp, op, CONST(c))), a) => MOV [u0 op c], u1 | (exp, a) => NULL")
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
					debug("// MOVE(MEM(a), b) => MOV [u0], u1 | (a, b) => NULL")

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
							debug("// MOVE(a, MEM(BINOP(op, exp, CONST(c)))) => MOV u0, [u1 op c] | (a, exp) => NULL")

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
					debug("// MOVE(a, MEM(b)) => MOV t0, [t1] | (a, b) => NULL")

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
			debug("// MOVE (a, CONST(c)) => MOV t0, c | (a) => NULL")
			std::ostringstream ss;
			ss << "MOVE t0, " << c->value;
			n->dst->Accept(this);
			curasmf->addInstruction(new Assemble::MOVE(ss.str().c_str(), new Temp::TempList(tmp), NULL));
			tmp = NULL;
			return 0;
		}

		debug("// MOVE (a, b) => MOV t0, t1 | (a, b) => NULL")
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
			debug("// JUMP (NAME (n)) => JMP n => NULL")
			std::ostringstream ss;
			ss << "JMP " << nm->label->name;
			curasmf->addInstruction(new Assemble::ASM(ss.str().c_str(), NULL, NULL));
			tmp = NULL;
			return 0;
		}
		n->exp->Accept( this );
		debug("// JUMP(exp) => JMP t0 | (exp) => NULL")
		curasmf->addInstruction(new Assemble::ASM("JMP u0", new Temp::TempList(tmp), NULL));
		tmp = NULL;
		end();
	}
	
	int visit(const IRTree::CJUMP* n)
	{
		log("CJUMP");
		n->left->Accept(this);
		auto a = tmp;
		n->right->Accept(this);
		auto b = tmp;
		debug("// CMP t0, t1 | (left, right); J(E, NE, L ..) truelabel ")
		
		curasmf->addInstruction(new Assemble::ASM("CMP u0, u1", new Temp::TempList(a, b), NULL));
		std::ostringstream ss;
		switch( n->relop )
		{
			case 0: // ==
				ss << "JE " << n->iftrue->name;
				break;
			case 1: // !=
				ss << "JNE " << n->iftrue->name;
				break;
			case 2: // <
				ss << "JL " << n->iftrue->name;
				break;
			case 3: // >
				ss << "JG " << n->iftrue->name;
				break;
			case 4: // <=
				ss << "JLE " << n->iftrue->name;
				break;
			case 5: // >=
				ss << "JGE " << n->iftrue->name;
				break;
		}
		curasmf->addInstruction(new Assemble::ASM(ss.str().c_str()));
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
					debug("// func ( .. CONST c .. ) => PUSH c => NULL")
					std::ostringstream ss;
					ss << "PUSH " << c->value;
					curasmf->addInstruction(new Assemble::ASM(ss.str().c_str(), NULL, NULL));
					tmp = NULL;
					continue;
				}

				exp->head->Accept(this);
				debug("// func ( .. exp .. ) => PUSH t0 | (exp) => NULL")
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

	AsmFragment* getRootAsmFragment()
	{
		return root;
	}

private:
	int padding;
	AsmFragment* root;
	AsmFragment* curasmf;
	const Temp::Temp* tmp;
};

}
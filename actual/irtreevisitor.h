#pragma once

#include "visitor.h"
#include "fwdclasses.h"
#include <iostream>
#include <string>
#include "codefragment.h"
#include "frame.h"
#include "namegenerator.h"
#include "wrapper.h"
#include "treeInterfaces.h"
#include "symbolstable.h"

#include <typeinfo>

class IRTreeVisitor : public IVisitor
{
public:

	const IFrameFactory* frameFactory;
	Wrapper::IRTreeWrapper* wrapper;
	IRTree::CodeFragment* curFragment;
	IRTree::CodeFragment* mainFragment;
	const Symbol* curClassName;
	const Symbol* curMethodName;
	ClassTable* classTable;

	std::map<const Symbol*, int> curMethodArgumentsShifts;
	std::map<const Symbol*, int> curMethodLocalVariablesShifts;

	IRTree::ExpList* curExpList;

	IRTreeVisitor(IFrameFactory* _fac, ClassTable* table) : frameFactory(_fac), classTable(table) {}

	IRTree::CodeFragment* getMainFragment()
	{
		return mainFragment;
	}

	int visit(const ArithmExp* n)
	{
		if(n->left) { n->left->Accept(this); }
		const IRTree::IExp* l = wrapper->ToExp();
		if(n->right) { n->right->Accept(this); }
		const IRTree::IExp* r = wrapper->ToExp();
		wrapper = new Wrapper::ExpWrapper( new IRTree::BINOP(n->op, l, r) );

		return 0;
	}

	int visit(const LogicExp* n)
	{
		if(n->left) { n->left->Accept(this); }
		const IRTree::IExp* l = wrapper->ToExp();
		if(n->right) { n->right->Accept(this); }
		const IRTree::IExp* r = wrapper->ToExp();
		wrapper = new Wrapper::ExpWrapper( new IRTree::BINOP(n->op, l, r) );

		return 0;
	}
	
	int visit(const IntVal* n)
	{

		return 0;
	}
	
	int visit(const BoolVal* n)
	{

		return 0;
	}
	
	int visit(const IdExp* n)
	{
		const Symbol* name = n->id;
		if( curMethodLocalVariablesShifts.count( name ) ) 
		{
			wrapper = new Wrapper::ExpWrapper( 
				curFragment
					->frame->localVarByShift(curMethodLocalVariablesShifts[name])
					->Exp(curFragment->frame->framePointer() ) 
			);
		} else if( curMethodArgumentsShifts.count(name) ) 
		{
			wrapper = new Wrapper::ExpWrapper( 
				curFragment
					->frame->argByShift(curMethodArgumentsShifts[name])
					->Exp(curFragment->frame->framePointer() ) 
			);
		} else {
			const IRTree::IExp* thisExp = 
				curFragment->frame->argByShift( 0 )->Exp(curFragment->frame->framePointer() );

			wrapper = new Wrapper::ExpWrapper( 
				new IRTree::MEM( 
					new IRTree::BINOP( 
						IRTree::OPERATOR::PLUS, 
						thisExp,
						new IRTree::CONST( 
							curFragment->frame->wordSize() 
							* ( 1 + classTable->getClass( curClassName )->getFiledShift( name ) ) 
						) 
					)
				)
			);
		}

		return 0;
	}
	int visit(const NewExp* n)
	{
		wrapper = new Wrapper::ExpWrapper( 
			curFragment->frame->externalCall( 
				"malloc",
				new IRTree::ExpList( 
					new IRTree::CONST( 
						curFragment->frame->wordSize() * ( 1 + classTable->getClass( n->id )->getSize() ) 
					)
				) 
			)
		);

		return 0;
	}
	int visit(const ThisExp* n)
	{
		wrapper = new Wrapper::ExpWrapper( 
			curFragment->frame->argByShift(0)->Exp(curFragment->frame->framePointer() ) 
		);
		return 0;
	}
	int visit(const LenExp* n)
	{

		if(n->exp) { n->exp->Accept(this); }
		wrapper = new Wrapper::ExpWrapper( 
			new IRTree::MEM ( 
				new IRTree::BINOP(
					IRTree::OPERATOR::MINUS,
					wrapper->ToExp(),
					new IRTree::CONST( curFragment->frame->wordSize() )
				)
			)
		);
		return 0;
	}
	int visit(const CallMethodExp* n)
	{
		ClassInfo* curClassInfo = classTable->getClass( curClassName );
		MethodInfo* curMethodInfo = curClassInfo->getMethod( curMethodName );
		const Symbol* type = TypeCheckerVisitor::getExpressionType( 
			classTable,
			curClassInfo,
			curMethodInfo, 
			n->exp 
		); 
		if(n->exp) { n->exp->Accept(this); }
		const IRTree::IExp* object = wrapper->ToExp();

		if(n->list) { n->list->Accept(this); }
		wrapper = new Wrapper::ExpWrapper( 
			new IRTree::CALL( 
				new Temp::Label( NameGenerator::gen(type, n->id) ),
				new IRTree::ExpList( object, curExpList ) 
			) 
		);

		curExpList = NULL;
		
		
		return 0;
	}
	int visit(const NewIntArrExp* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		wrapper = new Wrapper::ExpWrapper(
			new IRTree::BINOP( 
				IRTree::OPERATOR::PLUS, 
				curFragment->frame->externalCall(
					"malloc",
					new IRTree::ExpList( 
						new IRTree::BINOP(
							IRTree::OPERATOR::MUL,
							new IRTree::CONST( curFragment->frame->wordSize() ),
							new IRTree::BINOP(
								IRTree::OPERATOR::PLUS,
								new IRTree::CONST(1),
								wrapper->ToExp()
							) 
						)
					) 
				),
				new IRTree::CONST( curFragment->frame->wordSize () )
			)
		);
		return 0;
	}
	int visit(const ArrValExp* n)
	{
		if(n->idExp) { n->idExp->Accept(this); }
		const IRTree::IExp* id = wrapper->ToExp();
		if(n->exp) { n->exp->Accept(this); }
		wrapper = new Wrapper::ExpWrapper( 
			new IRTree::MEM( 
				new IRTree::BINOP(
					IRTree::OPERATOR::PLUS, 
					wrapper->ToExp(),
					new IRTree::BINOP(
						IRTree::OPERATOR::MUL,
						id,
						new IRTree::CONST ( curFragment->frame->wordSize() )
					)
				) 
			)
		);
		return 0;
	}
	int visit(const BlockStm* n)
	{
		// NOP 
		if(n->stms) { n->stms->Accept(this); }
		return 0;
	}
	int visit(const AssignStm* n)
	{
		// NOP
		if(n->assign) { n->assign->Accept(this); }
		return 0;
	}
	int visit(const PrintStmPrintStm* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		wrapper = new Wrapper::ExpWrapper( curFragment->frame->externalCall("print", curExpList) );
		curExpList = NULL;
		return 0;
	}
	
	int visit(const WhileStm* n)
	{
		const Temp::Label* exitLabel = new Temp::Label();
		const Temp::Label* enterLabel = new Temp::Label();
		const Temp::Label* nextLabel = new Temp::Label();
		const Temp::LabelList* nextLabelList = new Temp::LabelList( nextLabel );

		if(n->stm) { n->stm->Accept(this); }
		const IRTree::IStm* body = wrapper->ToStm();

		if(n->exp) { n->exp->Accept(this); }

		wrapper = new Wrapper::StmWrapper( 
			new IRTree::SEQ (
				new IRTree::SEQ (
					new IRTree::LABEL(nextLabel), 
					wrapper->ToConditional(enterLabel, exitLabel) ), 
				new IRTree::SEQ (
					new IRTree::SEQ (
						new IRTree::SEQ (
							new IRTree::LABEL(enterLabel), 
							body),
						new IRTree::JUMP (
							new IRTree::NAME(nextLabel), 
							nextLabelList) ),
					new IRTree::LABEL(exitLabel)
				)
			)
		);

		return 0;
	}
	
	int visit(const IfElseStm* n)
	{

		const Temp::Label* endl = new Temp::Label();
		const Temp::Label* truel = new Temp::Label();
		const Temp::Label* flasel = new Temp::Label();
		const Temp::LabelList* endllist = new Temp::LabelList( endl );

		if(n->stm) { n->stm->Accept(this); }
		const IRTree::IStm* trueStm = new IRTree::SEQ(
			new IRTree::LABEL(truel),
			new IRTree::SEQ( 
				wrapper->ToStm(), 
				new IRTree::JUMP( new IRTree::NAME(endl),  endllist) 
			)
		);

		if(n->elseStm) { n->elseStm->Accept(this); }
		const IRTree::IStm* falseStm = new IRTree::SEQ(
			new IRTree::LABEL(flasel),
			new IRTree::SEQ( 
				wrapper->ToStm(), 
				new IRTree::JUMP( new IRTree::NAME(endl),  endllist) 
			)
		);

		if(n->exp) { n->exp->Accept(this); }
		wrapper = new Wrapper::StmWrapper( 
			new IRTree::SEQ(
				wrapper->ToConditional(truel, flasel),
				new IRTree::SEQ(
					new IRTree::SEQ(trueStm, falseStm),
					new IRTree::LABEL(endl)
				)
			)
		);

		return 0;
	}

	int visit(const AssignArrStm* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		const IRTree::IExp* index = wrapper->ToExp();
		if(n->newexp) { n->newexp->Accept(this); }
		wrapper = new Wrapper::StmWrapper(
			new IRTree::MOVE(
				new IRTree::MEM( 
					new IRTree::BINOP(
						IRTree::OPERATOR::PLUS, 
						new IRTree::NAME( new Temp::Label(n->id->getStr() ) ),
						new IRTree::BINOP(
							IRTree::OPERATOR::MUL, 
							index, 
							new IRTree::CONST( curFragment->frame->wordSize() ) 
						)
					)
				),
				wrapper->ToExp()
			)
		);
		return 0;
	}
	int visit(const ExpressionListImpl* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		const IRTree::IExp* e = wrapper->ToExp();

		if(n->list) { n->list->Accept(this); }
		curExpList = new IRTree::ExpList(e, curExpList);

		return 0;
	}

	int visit(const StatementsImpl* n)
	{
		const IRTree::IStm* left = NULL;
		const IRTree::IStm* right = NULL;

		if(n->stm) 
		{ 
			n->stm->Accept(this); 
			left = wrapper->ToStm();
		}

		if(n->list) 
		{
			n->list->Accept(this);
			right = wrapper->ToStm();
		}

		if (left && right) {
			wrapper = new Wrapper::StmWrapper( new IRTree::SEQ(left, right) );
			return 0;
		}

		if (left) {
			wrapper = new Wrapper::StmWrapper( left );
			return 0;
		}

		if (right) {
			wrapper = new Wrapper::StmWrapper( right );
			return 0;
		}

		wrapper = new Wrapper::StmWrapper( new IRTree::EXP( new IRTree::CONST( 0 ) ) );

		return 0;
	}
	
	int visit(const AssignmentImpl* n)
	{
		(new IdExp(n->id, 0, 0))->Accept(this); // it's interesting what to write as line and column here
		const IRTree::IExp* var = wrapper->ToExp();
		if(n->exp) { n->exp->Accept(this); }
		wrapper = new Wrapper::StmWrapper( new IRTree::MOVE(var, wrapper->ToExp()));
		return 0;
	}

	int visit(const ArguementImpl* n)
	{
		int newshift = curMethodArgumentsShifts.size() + 1;
		curMethodArgumentsShifts[n->id] = newshift;
		wrapper = new Wrapper::StmWrapper( 
			new IRTree::SEQ(
				wrapper->ToStm(),
				new IRTree::MOVE(
					curFragment->frame->argByShift(newshift)->Exp( curFragment->frame->framePointer() ),
					new IRTree::CONST(0) 
				)
			)
		);

		// if(n->type) { n->type->Accept(this); }
		return 0;
	}

	int visit(const ArguementsImpl* n)
	{
		if(n->arg) { n->arg->Accept(this); }
		if(n->list) { n->list->Accept(this); }
		return 0;
	}
	int visit(const InternalType* n)
	{

		return 0;
	}
	int visit(const CustomType* n)
	{

		return 0;
	}
	int visit(const VarDeclarationImpl* n)
	{
		if(n->type) { n->type->Accept(this); }
		int newshift = curMethodLocalVariablesShifts.size();
		curMethodLocalVariablesShifts[n->id] = newshift;
		wrapper = new Wrapper::StmWrapper( 
			new IRTree::SEQ( 
				wrapper->ToStm(), 
				new IRTree::MOVE( 
					curFragment->frame->localVarByShift(newshift)->Exp( curFragment->frame->framePointer() ),
					new IRTree::CONST( 0 ) 
				) 
			)
		);
		return 0;
	}
	int visit(const VarDeclarationsImpl* n)
	{
		if(n->dec) { n->dec->Accept(this); }
		if(n->list) { n->list->Accept(this); }
		return 0;
	}
	int visit(const MethodDeclarationsImpl* n)
	{
		if(n->dec) { n->dec->Accept(this); }
		if(n->list) { n->list->Accept(this); }
		return 0;
	}
	int visit(const MethodDeclarationImpl* n)
	{
		curMethodName = n->id;

		curMethodArgumentsShifts.clear();
		curMethodLocalVariablesShifts.clear();

		if(n->type) { n->type->Accept(this); }
		if(n->args) { n->args->Accept(this); }
		if(n->vars) { n->vars->Accept(this); }
		
		IRTree::CodeFragment* newCodeFragment = new IRTree::CodeFragment( 
			frameFactory->create(NameGenerator::gen(curClassName, curMethodName), 
				curMethodArgumentsShifts.size(), 
				curMethodLocalVariablesShifts.size() 
			) 
		);

		curFragment->next = newCodeFragment;
		curFragment = newCodeFragment;

		wrapper = new Wrapper::StmWrapper( new IRTree::EXP( new IRTree::CONST(0) ));

		if(n->statements) { n->statements->Accept(this); }
		curFragment->body = wrapper->ToStm();

		if(n->exp) { n->exp->Accept(this); }
		curFragment->retval = new IRTree::ESEQ( curFragment->body, wrapper->ToExp() );

		return 0;
	}
	
	int visit(const ClassDeclarationsImpl* n)
	{
		if(n->dec) { n->dec->Accept(this); }
		if(n->list) { n->list->Accept(this); }
		return 0;
	}
	
	int visit(const ClassDeclarationImpl* n)
	{
		curClassName = n->id;
		// ignoring class vars ?
		// if(n->vars) { n->vars->Accept(this); } 
		if(n->methods) { n->methods->Accept(this); }
		curClassName = NULL;
		return 0;
	}
	
	int visit(const ProgramImpl* n)
	{
		if(n->cl) { n->cl->Accept(this); }
		if(n->decs) { n->decs->Accept(this); }
		return 0;
	}

	int visit(const MainClassImpl* n)
	{
		curClassName = Symbol::getSymbol("main");
		classTable->addClass(curClassName, NULL);

		curFragment = new IRTree::CodeFragment( frameFactory->create( NameGenerator::gen( n->id->getStr(), std::string("MAIN") ), 0, 0 ) );
		if(n->stm) { n->stm->Accept(this); }
		curFragment->body = wrapper->ToStm();
		curFragment->retval = new IRTree::ESEQ(curFragment->body, new IRTree::CONST (0) );
		mainFragment = curFragment;
		return 0;
	}
};
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


class IRTreeVisitor : public IVisitor
{
public:

	const IFrameFactory* frameFactory;
	Wrapper::IRTreeWrapper* wrapper;
	IRTree::CodeFragment* curFragment;
	const Symbol* curClassName;
	const Symbol* curMethodName;
	int argnum;
	int varnum;

	IRTreeVisitor(IFrameFactory* _fac) : frameFactory(_fac) {}

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
		if(n->right) { n->right->Accept(this); }
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

		return 0;
	}
	int visit(const NewExp* n)
	{

		return 0;
	}
	int visit(const ThisExp* n)
	{

		return 0;
	}
	int visit(const LenExp* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		return 0;
	}
	int visit(const CallMethodExp* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		if(n->list) { n->list->Accept(this); }
		return 0;
	}
	int visit(const NewIntArrExp* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		return 0;
	}
	int visit(const ArrValExp* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		if(n->idExp) { n->idExp->Accept(this); }
		return 0;
	}
	int visit(const BlockStm* n)
	{
		if(n->stms) { n->stms->Accept(this); }
		return 0;
	}
	int visit(const AssignStm* n)
	{
		if(n->assign) { n->assign->Accept(this); }
		return 0;
	}
	int visit(const PrintStmPrintStm* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		return 0;
	}
	int visit(const WhileStm* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		if(n->stm) { n->stm->Accept(this); }
		return 0;
	}
	int visit(const IfElseStm* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		if(n->stm) { n->stm->Accept(this); }
		if(n->elseStm) { n->elseStm->Accept(this); }
		return 0;
	}
	int visit(const AssignArrStm* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		if(n->newexp) { n->newexp->Accept(this); }
		return 0;
	}
	int visit(const ExpressionListImpl* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		if(n->list) { n->list->Accept(this); }
		return 0;
	}
	int visit(const StatementsImpl* n)
	{
		if(n->stm) { n->stm->Accept(this); }
		if(n->list) { n->list->Accept(this); }
		return 0;
	}
	int visit(const AssignmentImpl* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		return 0;
	}
	int visit(const ArguementImpl* n)
	{
		argnum += 1;
		if(n->type) { n->type->Accept(this); }
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
		varnum += 1;

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

		argnum = 0;
		varnum = 0;

		if(n->type) { n->type->Accept(this); }
		if(n->args) { n->args->Accept(this); }
		if(n->vars) { n->vars->Accept(this); }
		
		IRTree::CodeFragment* newCodeFragment = new IRTree::CodeFragment( 
			frameFactory->create(NameGenerator::gen(curClassName, curMethodName), argnum, varnum) );

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
		curFragment = new IRTree::CodeFragment( frameFactory->create( NameGenerator::gen( n->id->getStr(), std::string("MAIN") ), 0, 0 ) );
		if(n->stm) { n->stm->Accept(this); }
		curFragment->body = wrapper->ToStm();
		curFragment->retval = new IRTree::ESEQ(curFragment->body, new IRTree::CONST (0) );
		return 0;
	}
};
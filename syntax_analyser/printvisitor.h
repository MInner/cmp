#pragma once

#include "visitor.h"
#include "fwdclasses.h"
#include <iostream>
#include <string>

class PrintVisitor : public IVisitor
{
public:

	int padding;

	int visit(const ArithmExp* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "ArithmExp: (" << n->op <<  ")" << std::endl;
		if(n->left) { n->left->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "left::NULL" << std::endl; }
		if(n->right) { n->right->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "right::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/ArithmExp" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const LogicExp* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "LogicExp: (" << n->op <<  ")" << std::endl;
		if(n->left) { n->left->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "left::NULL" << std::endl; }
		if(n->right) { n->right->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "right::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/LogicExp" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const IntVal* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "IntVal: (" << n->val <<  ")" << std::endl;

		std::cout << std::string(padding, ' ') << "/IntVal" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const BoolVal* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "BoolVal: (" << n->val <<  ")" << std::endl;

		std::cout << std::string(padding, ' ') << "/BoolVal" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const IdExp* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "IdExp: (" << n->id <<  ")" << std::endl;

		std::cout << std::string(padding, ' ') << "/IdExp" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const NewExp* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "NewExp: (" << n->id <<  ")" << std::endl;

		std::cout << std::string(padding, ' ') << "/NewExp" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const ThisExp* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "ThisExp: (" << ")" << std::endl;

		std::cout << std::string(padding, ' ') << "/ThisExp" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const LenExp* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "LenExp: (" <<  ")" << std::endl;
		if(n->exp) { n->exp->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "exp::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/LenExp" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const CallMethodExp* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "CallMethodExp: (" << n->id <<  ")" << std::endl;
		if(n->exp) { n->exp->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "exp::NULL" << std::endl; }
		if(n->list) { n->list->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "list::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/CallMethodExp" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const NewIntArrExp* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "NewIntArrExp: (" <<  ")" << std::endl;
		if(n->exp) { n->exp->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "exp::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/NewIntArrExp" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const ArrValExp* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "ArrValExp: (" <<  ")" << std::endl;
		if(n->exp) { n->exp->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "exp::NULL" << std::endl; }
		if(n->idExp) { n->idExp->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "idExp::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/ArrValExp" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const BlockStm* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "BlockStm: (" <<  ")" << std::endl;
		if(n->stms) { n->stms->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "stms::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/BlockStm" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const AssignStm* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "AssignStm: (" <<  ")" << std::endl;
		if(n->assign) { n->assign->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "assign::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/AssignStm" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const PrintStmPrintStm* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "PrintStmPrintStm: (" <<  ")" << std::endl;
		if(n->exp) { n->exp->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "exp::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/PrintStmPrintStm" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const WhileStm* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "WhileStm: (" <<  ")" << std::endl;
		if(n->exp) { n->exp->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "exp::NULL" << std::endl; }
		if(n->stm) { n->stm->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "stm::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/WhileStm" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const IfElseStm* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "IfElseStm: (" <<  ")" << std::endl;
		if(n->exp) { n->exp->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "exp::NULL" << std::endl; }
		if(n->stm) { n->stm->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "stm::NULL" << std::endl; }
		if(n->elseStm) { n->elseStm->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "elseStm::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/IfElseStm" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const AssignArrStm* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "AssignArrStm: (" << n->id <<  ")" << std::endl;
		if(n->exp) { n->exp->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "exp::NULL" << std::endl; }
		if(n->newexp) { n->newexp->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "newexp::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/AssignArrStm" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const ExpressionListImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "ExpressionListImpl: (" <<  ")" << std::endl;
		if(n->exp) { n->exp->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "exp::NULL" << std::endl; }
		if(n->list) { n->list->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "list::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/ExpressionListImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const StatementsImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "StatementsImpl: (" <<  ")" << std::endl;
		if(n->stm) { n->stm->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "stm::NULL" << std::endl; }
		if(n->list) { n->list->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "list::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/StatementsImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const AssignmentImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "AssignmentImpl: (" << n->id <<  ")" << std::endl;
		if(n->exp) { n->exp->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "exp::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/AssignmentImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const ArguementImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "ArguementImpl: (" << n->id <<  ")" << std::endl;
		if(n->type) { n->type->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "type::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/ArguementImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const ArguementsImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "ArguementsImpl: (" <<  ")" << std::endl;
		if(n->arg) { n->arg->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "arg::NULL" << std::endl; }
		if(n->list) { n->list->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "list::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/ArguementsImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const InternalType* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "InternalType: (" << n->type <<  ")" << std::endl;

		std::cout << std::string(padding, ' ') << "/InternalType" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const VarDeclarationImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "VarDeclarationImpl: (" << n->id <<  ")" << std::endl;
		if(n->type) { n->type->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "type::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/VarDeclarationImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const VarDeclarationsImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "VarDeclarationsImpl: (" <<  ")" << std::endl;
		if(n->dec) { n->dec->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "dec::NULL" << std::endl; }
		if(n->list) { n->list->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "list::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/VarDeclarationsImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const MethodDeclarationsImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "MethodDeclarationsImpl: (" <<  ")" << std::endl;
		if(n->dec) { n->dec->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "dec::NULL" << std::endl; }
		if(n->list) { n->list->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "list::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/MethodDeclarationsImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const MethodDeclarationImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "MethodDeclarationImpl: (" << n->id <<  ")" << std::endl;
		if(n->type) { n->type->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "type::NULL" << std::endl; }
		if(n->args) { n->args->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "args::NULL" << std::endl; }
		if(n->vars) { n->vars->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "vars::NULL" << std::endl; }
		if(n->statements) { n->statements->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "statements::NULL" << std::endl; }
		if(n->exp) { n->exp->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "exp::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/MethodDeclarationImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const ClassDeclarationsImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "ClassDeclarationsImpl: (" <<  ")" << std::endl;
		if(n->dec) { n->dec->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "dec::NULL" << std::endl; }
		if(n->list) { n->list->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "list::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/ClassDeclarationsImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const ClassDeclarationImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "ClassDeclarationImpl: (" << n->id << ", " << n->extId <<  ")" << std::endl;
		if(n->vars) { n->vars->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "vars::NULL" << std::endl; }
		if(n->methods) { n->methods->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "methods::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/ClassDeclarationImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const ProgramImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "ProgramImpl: (" <<  ")" << std::endl;
		if(n->cl) { n->cl->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "cl::NULL" << std::endl; }
		if(n->decs) { n->decs->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "decs::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/ProgramImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const MainClassImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "MainClassImpl: (" << n->id << ", " << n->argId <<  ")" << std::endl;
		if(n->stm) { n->stm->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "stm::NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/MainClassImpl" << std::endl;
		padding -= 1;
		return 0;
	}
};
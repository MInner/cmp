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
		n->left->Accept(this);
		n->right->Accept(this);
		std::cout << std::string(padding, ' ') << "/ArithmExp" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const LogicExp* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "LogicExp: (" << n->op <<  ")" << std::endl;
		n->left->Accept(this);
		n->right->Accept(this);
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
		std::cout << std::string(padding, ' ') << "ThisExp: (" << n->val <<  ")" << std::endl;

		std::cout << std::string(padding, ' ') << "/ThisExp" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const LenExp* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "LenExp: (" <<  ")" << std::endl;
		n->exp->Accept(this);
		std::cout << std::string(padding, ' ') << "/LenExp" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const CallMethodExp* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "CallMethodExp: (" << n->id <<  ")" << std::endl;
		n->exp->Accept(this);
		if(n->list) {n->list->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/CallMethodExp" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const NewIntArrExp* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "NewIntArrExp: (" <<  ")" << std::endl;
		n->exp->Accept(this);
		std::cout << std::string(padding, ' ') << "/NewIntArrExp" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const ArrValExp* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "ArrValExp: (" <<  ")" << std::endl;
		n->exp->Accept(this);
		n->inExp->Accept(this);
		std::cout << std::string(padding, ' ') << "/ArrValExp" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const BlockStm* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "BlockStm: (" <<  ")" << std::endl;
		n->stms->Accept(this);
		std::cout << std::string(padding, ' ') << "/BlockStm" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const AssignStm* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "AssignStm: (" <<  ")" << std::endl;
		n->assign->Accept(this);
		std::cout << std::string(padding, ' ') << "/AssignStm" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const PrintStmPrintStm* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "PrintStmPrintStm: (" <<  ")" << std::endl;
		n->exp->Accept(this);
		std::cout << std::string(padding, ' ') << "/PrintStmPrintStm" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const WhileStm* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "WhileStm: (" <<  ")" << std::endl;
		n->exp->Accept(this);
		n->stm->Accept(this);
		std::cout << std::string(padding, ' ') << "/WhileStm" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const IfElseStm* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "IfElseStm: (" <<  ")" << std::endl;
		n->exp->Accept(this);
		n->stm->Accept(this);
		n->elseStm->Accept(this);
		std::cout << std::string(padding, ' ') << "/IfElseStm" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const AssignArrStm* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "AssignArrStm: (" << n->id <<  ")" << std::endl;
		n->exp->Accept(this);
		n->stm->Accept(this);
		std::cout << std::string(padding, ' ') << "/AssignArrStm" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const ExpressionListImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "ExpressionListImpl: (" <<  ")" << std::endl;
		n->exp->Accept(this);
		if(n->list) {n->list->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/ExpressionListImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const StatementsImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "StatementsImpl: (" <<  ")" << std::endl;
		n->stm->Accept(this);
		if(n->list) {n->list->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/StatementsImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const AssignmentImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "AssignmentImpl: (" << n->id <<  ")" << std::endl;
		n->exp->Accept(this);
		std::cout << std::string(padding, ' ') << "/AssignmentImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const ArguementImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "ArguementImpl: (" << n->id <<  ")" << std::endl;
		n->type->Accept(this);
		std::cout << std::string(padding, ' ') << "/ArguementImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const ArguementsImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "ArguementsImpl: (" <<  ")" << std::endl;
		n->arg->Accept(this);
		if(n->list) {n->list->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "NULL" << std::endl; }
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
		n->type->Accept(this);
		std::cout << std::string(padding, ' ') << "/VarDeclarationImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const VarDeclarationsImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "VarDeclarationsImpl: (" <<  ")" << std::endl;
		if(n->dec) {n->list->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "NULL" << std::endl; }
		if(n->list) {n->list->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/VarDeclarationsImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const MethodDeclarationsImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "MethodDeclarationsImpl: (" <<  ")" << std::endl;
		if(n->dec) {n->list->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "NULL" << std::endl; }
		if(n->list) {n->list->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/MethodDeclarationsImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const MethodDeclarationImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "MethodDeclarationImpl: (" << n->id <<  ")" << std::endl;
		n->type->Accept(this);
		n->args->Accept(this);
		n->vars->Accept(this);
		n->statements->Accept(this);
		n->exp->Accept(this);
		std::cout << std::string(padding, ' ') << "/MethodDeclarationImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const ClassDeclarationsImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "ClassDeclarationsImpl: (" <<  ")" << std::endl;
		if(n->dec) {n->list->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "NULL" << std::endl; }
		if(n->list) {n->list->Accept(this); } else { std::cout << std::string(padding + 1, ' ') << "NULL" << std::endl; }
		std::cout << std::string(padding, ' ') << "/ClassDeclarationsImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const ClassDeclarationImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "ClassDeclarationImpl: (" << n->id << ", " << n->extId <<  ")" << std::endl;
		n->vars->Accept(this);
		n->methods->Accept(this);
		std::cout << std::string(padding, ' ') << "/ClassDeclarationImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const ProgramImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "ProgramImpl: (" <<  ")" << std::endl;
		n->cl->Accept(this);
		n->decs->Accept(this);
		std::cout << std::string(padding, ' ') << "/ProgramImpl" << std::endl;
		padding -= 1;
		return 0;
	}

	int visit(const MainClassImpl* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "MainClassImpl: (" << n->id << ", " << n->argId <<  ")" << std::endl;
		n->stm->Accept(this);
		std::cout << std::string(padding, ' ') << "/MainClassImpl" << std::endl;
		padding -= 1;
		return 0;
	}
};
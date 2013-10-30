#pragma once

#include "visitor.h"
#include "fwdclasses.h"
#include <iostream>

class PrintVisitor : public IVisitor
{
public:
	int visit(const ProgramImpl* n)
	{
		std::cout << "ProgramImpl: " << std::endl;

		n->cl->Accept(this);
		n->decs->Accept(this);
		
		return 0;
	}

	int visit(const MainClassImpl* n)
	{
		std::cout << "MainClassImpl: " << std::endl;
		return 0;
	}

	int visit(const ClassDeclarationsImpl* n)
	{
		std::cout << "ClassDeclarationsImpl: " << std::endl;
		return 0;
	}

	int visit(const ClassDeclarationImpl* n)
	{
		std::cout << "ClassDeclarationImpl: " << std::endl;
		return 0;
	}

	int visit(const VarDeclarationsImpl* n)
	{
		std::cout << "VarDeclarationsImpl: " << std::endl;
		return 0;
	}

	int visit(const VarDeclarationImpl* n)
	{
		std::cout << "VarDeclarationImpl: " << std::endl;
		return 0;
	}

	int visit(const MethodDeclarationsImpl* n)
	{
		std::cout << "MethodDeclarationsImpl: " << std::endl;
		return 0;
	}

	int visit(const MethodDeclarationImpl* n)
	{
		std::cout << "MethodDeclarationImpl: " << std::endl;
		return 0;
	}

	int visit(const StatementsImpl* n)
	{
		std::cout << "StatementsImpl: " << std::endl;
		return 0;
	}

	int visit(const BlockStm* n)
	{
		std::cout << "BlockStm: " << std::endl;
		return 0;
	}

	int visit(const AssignStm* n)
	{
		std::cout << "AssignStm: " << std::endl;
		return 0;
	}

	int visit(const IfElseStm* n)
	{
		std::cout << "IfElseStm: " << std::endl;
		return 0;
	}

	int visit(const WhileStm* n)
	{
		std::cout << "WhileStm: " << std::endl;
		return 0;
	}

	int visit(const PrintStmPrintStm* n)
	{
		std::cout << "PrintStmPrintStm: " << std::endl;
		return 0;
	}

	int visit(const AssignArrStm* n)
	{
		std::cout << "AssignArrStm: " << std::endl;
		return 0;
	}

	int visit(const InternalType* n)
	{
		std::cout << "InternalType: " << std::endl;
		return 0;
	}

	int visit(const ArguementsImpl* n)
	{
		std::cout << "ArguementsImpl: " << std::endl;
		return 0;
	}

	int visit(const ArguementImpl* n)
	{
		std::cout << "ArguementImpl: " << std::endl;
		return 0;
	}

	int visit(const AssignmentImpl* n)
	{
		std::cout << "AssignmentImpl: " << std::endl;
		return 0;
	}

	int visit(const ArithmExp* n)
	{
		std::cout << "ArithmExp: " << std::endl;
		return 0;
	}

	int visit(const LogicExp* n)
	{
		std::cout << "LogicExp: " << std::endl;
		return 0;
	}

	int visit(const ArrValExp* n)
	{
		std::cout << "ArrValExp: " << std::endl;
		return 0;
	}

	int visit(const LenExp* n)
	{
		std::cout << "LenExp: " << std::endl;
		return 0;
	}

	int visit(const CallMethodExp* n)
	{
		std::cout << "CallMethodExp: " << std::endl;
		return 0;
	}

	int visit(const IntVal* n)
	{
		std::cout << "IntVal: " << std::endl;
		return 0;
	}

	int visit(const BoolVal* n)
	{
		std::cout << "BoolVal: " << std::endl;
		return 0;
	}

	int visit(const IdExp* n)
	{
		std::cout << "IdExp: " << std::endl;
		return 0;
	}

	int visit(const ThisExp* n)
	{
		std::cout << "ThisExp: " << std::endl;
		return 0;
	}

	int visit(const NewIntArrExp* n)
	{
		std::cout << "NewIntArrExp: " << std::endl;
		return 0;
	}

	int visit(const NewExp* n)
	{
		std::cout << "NewExp: " << std::endl;
		return 0;
	}

	int visit(const ExpressionListImpl* n)
	{
		std::cout << "ExpressionListImpl: " << std::endl;
		return 0;
	}
};
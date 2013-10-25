#pragma once

#include "visitor.h"
#include "fwdclasses.h"
#include <iostream>

class PrintVisitor : public IVisitor
{
public:
	int visit(const ArithmExp* n)
	{
		return 0;
	}

	int visit(const MainClassImpl* n)
	{
		std::cout << "MainClass: " << std::endl;
		return 0;
	}
	
	int visit(const ProgramImpl* pi)
	{
		std::cout << "ProgramImpl: " << std::endl;

		pi->cl->Accept(this);
		pi->decs->Accept(this);
		
		return 0;
	}

	int visit(const ClassDeclarationsImpl* n)
	{
		std::cout << "ClassDeclarationsImpl: " << std::endl;
		return 0;
	}
};
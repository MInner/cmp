#pragma once

#include "fwdclasses.h"

class IVisitor
{
public:
	virtual int visit(const ArithmExp* n) = 0;
	virtual int visit(const MainClassImpl* n) = 0;
	virtual int visit(const ProgramImpl* n) = 0;
	virtual int visit(const ClassDeclarationsImpl* n) = 0;
};
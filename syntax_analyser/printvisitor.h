#pragma once

#include "visitor.h"

class PrintVisitor : public IVisitor
{
public:
	int visit(const ArithmExp* n);
};
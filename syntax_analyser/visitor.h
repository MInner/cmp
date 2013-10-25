#pragma once

class ArithmExp;

class IVisitor
{
public:
	int visit(const ArithmExp* n);
};
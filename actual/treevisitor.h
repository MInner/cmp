#pragma once

#include "fwdclasses.h"

namespace IRTree {

class TreeVisitor : public ITreeVisitor
{
	int visit(const CONST* n)
	{
		return 0;
	}
	int visit(const NAME* n)
	{
		return 0;
	}
	int visit(const TEMP* n)
	{
		return 0;
	}
	int visit(const BINOP* n)
	{
		return 0;
	}
	int visit(const MEM* n)
	{
		return 0;
	}
	int visit(const CALL* n)
	{
		return 0;
	}
	int visit(const ESEQ* n)
	{
		return 0;
	}
	int visit(const MOVE* n)
	{
		return 0;
	}
	int visit(const EXP* n)
	{
		return 0;
	}
	int visit(const JUMP* n)
	{
		return 0;
	}
	int visit(const CJUMP* n)
	{
		return 0;
	}
	int visit(const SEQ* n)
	{
		return 0;
	}
	int visit(const LABEL* n)
	{
		return 0;
	}
	int visit(const ExpList* n)
	{
		return 0;
	}
	int visit(const StmList* n)
	{
		return 0;
	}
};

}
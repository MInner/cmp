pragma once

#include "fwdIRClasses.h"

class IVisitor
{
public:
	virtual int visit(const CONST* n) = 0;
	virtual int visit(const NAME* n) = 0;
	virtual int visit(const TEMP* n) = 0;
	virtual int visit(const BINOP* n) = 0;
	virtual int visit(const MEM* n) = 0;
	virtual int visit(const CALL* n) = 0;
	virtual int visit(const ESEQ* n) = 0;
	virtual int visit(const EXP* n) = 0;
	virtual int visit(const JUMP* n) = 0;
	virtual int visit(const CJUMP* n) = 0;
	virtual int visit(const SEQ* n) = 0;
	virtual int visit(const LABEL* n) = 0;
	virtual int visit(const ExpList* n) = 0;
	virtual int visit(const StmList* n) = 0;
};
#include "treeClasses.h"

class ITreeVisitor
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
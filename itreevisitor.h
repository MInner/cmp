#pragma once

#include "fwdclasses.h"

namespace IRTree {

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
		virtual int visit(const MOVE* n) = 0;
		virtual int visit(const EXP* n) = 0;
		virtual int visit(const JUMP* n) = 0;
		virtual int visit(const CJUMP* n) = 0;
		virtual int visit(const SEQ* n) = 0;
		virtual int visit(const LABEL* n) = 0;
		virtual int visit(const ExpList* n) = 0;
		virtual int visit(const StmList* n) = 0;
        virtual int visit(const MOVECALL* n) = 0;
        virtual int visit(const EXPCALL* n) = 0;
	};

}

#pragma once

#include "frame.h"
#include "treeInterfaces.h"


namespace IRTree {

	class StmList; // forward decl

	class CodeFragment {
	public:
		CodeFragment( const IFrame* _frame ): frame(_frame) {}
		CodeFragment( const IFrame* _frame, const IRTree::IExp* _retval, const IRTree::CodeFragment* _next):
								frame(_frame), retval(_retval), next(_next) {}
		CodeFragment( const IFrame* _frame, const IRTree::IStm* _body, const IRTree::IExp* _retval, const IRTree::CodeFragment* _next):
								frame(_frame), body(_body), retval(_retval), next(_next) {}

		const IFrame* frame;
		const IRTree::IStm* body;
		const IRTree::IExp* retval;
		const IRTree::StmList* stmlist;
		const IRTree::CodeFragment* next;
	};

}

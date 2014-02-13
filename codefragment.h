#pragma once

#include "frame.h"
#include "treeInterfaces.h"

namespace IRTree {

	class CodeFragment {
	public:
		CodeFragment( const IFrame* _frame ): frame(_frame) {}
		const IFrame* frame;
		const IRTree::IStm* body;
		const IRTree::IExp* retval;
		const IRTree::CodeFragment* next;
	};

}
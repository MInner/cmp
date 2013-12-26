#pragma once

#include "irtreevisitor.h"
#include "treeClasses.h"

#include <iostream>

namespace IRTree
{

class IRTreePrintVisitor : public ITreeVisitor 
{
public:
	IRTreePrintVisitor(std::ostream& out_): out(out_),
		clust(0), node(0) {}
		
	virtual ~IRTreePrintVisitor() {}

	int visit(const CodeFragment* codeFragment)
	{
		clust = 0;
		node = 0;
		out << "graph \"\" {" << std::endl;
		for(auto currentCodeFragment = codeFragment; 
		        currentCodeFragment != nullptr; currentCodeFragment = currentCodeFragment->next ) 
		{
			out << "subgraph cluster" << clust++ << " {" << std::endl;
			out << "label=\"" << currentCodeFragment->frame->getName()->name << "\"" << std::endl;
			currentCodeFragment->retval->Accept( this );
			out << "}" << std::endl;
		}
		out << "}" << std::endl;
	}

	int visit(const CONST* n)
	{
		out << "n" << node++ << " [shape=\"ellipse\",color=\"green\",label=\"CONST(" << n->value << ")\"]" << std::endl;
	}

	int visit(const NAME* n)
	{
		out << "n" << node++ << " [shape=\"ellipse\",color=\"green\",label=\"NAME(" << n->label->name << ")\"]" << std::endl;
	}
	
	int visit(const TEMP* n)
	{
		out << "n" << node++ << " [shape=\"ellipse\",color=\"green\",label=\"TEMP(" << n->temp->name << ")\"]" << std::endl;
	}
	
	int visit(const BINOP* n)
	{
		static const char* names[] = { "+", "-", "*", "/", "&&", "||", "<<", ">>", "ARSHIFT", "XOR" };
		const long myNodeNumber = node++;
		out << "n" << myNodeNumber << " [shape=\"ellipse\",color=\"green\",label=\"BINOP(" << names[n->binop] << ")\"]" << std::endl;
		out << "n" << myNodeNumber << " -- n" << node << std::endl;
		n->left->Accept( this );
		out << "n" << myNodeNumber << " -- n" << node << std::endl;
		n->right->Accept( this );
	}
	
	int visit(const MEM* n)
	{
		out << "n" << node++ << " [shape=\"ellipse\",color=\"green\",label=\"MEM\"]" << std::endl;
		out << "n" << node - 1 << " -- n" << node << std::endl;
		n->exp->Accept( this );
	}
	
	int visit(const CALL* n)
	{
		out << "n" << node++ << " [shape=\"box\",color=\"red\",label=\"CALL(" << n->func->name << ")\"]" << std::endl;

		if( n->args != nullptr ) {
			n->args->Accept( this );
		}
	}
	
	int visit(const ESEQ* n)
	{
		long myNodeNumber = node++;
		out << "n" << myNodeNumber << " [shape=\"ellipse\",color=\"green\",label=\"ESEQ\"]" << std::endl;
		out << "n" << myNodeNumber << " -- n" << node << std::endl;
		n->stm->Accept( this );
		out << "n" << myNodeNumber << " -- n" << node << std::endl;
		n->exp->Accept( this );
	}

	int visit(const MOVE* n)
	{
		long myNodeNumber = node++;
		out << "n" << myNodeNumber << " [shape=\"box\",color=\"red\",label=\"MOVE\"]" << std::endl;
		out << "n" << myNodeNumber << " -- n" << node << std::endl;
		n->dst->Accept( this );
		out << "n" << myNodeNumber << " -- n" << node << std::endl;
		n->src->Accept( this );
	}
	
	int visit(const EXP* n)
	{
		out << "n" << node++ << " [shape=\"box\",color=\"red\",label=\"EXP\"]" << std::endl;
		out << "n" << node - 1 << " -- n" << node << std::endl;
		n->exp->Accept( this );
	}
	
	int visit(const JUMP* n)
	{
		long myNodeNumber = node++;
		out << "n" << myNodeNumber << " [shape=\"box\",color=\"red\",label=\"JUMP\"]" << std::endl;
		out << "n" << myNodeNumber << " -- n" << node << std::endl;
		n->exp->Accept( this );
		for( auto labels = n->targets; labels != nullptr && labels->label != nullptr; labels = labels->rest ) {
			out << "n" << myNodeNumber << " -- n" << node << std::endl;
			out << "n" << node++ << " [shape=\"box\",color=\"red\",label=\"" << labels->label->name << "\"]" << std::endl;
		}
	}
	
	int visit(const CJUMP* n)
	{
		static const char* names[] = { "==", "!=", "<", ">", "<=", ">=", "ULT", "ULE", "UGT", "UGE" };
		long myNodeNumber = node++;
		out << "n" << myNodeNumber << " [shape=\"box\",color=\"red\",label=\"CJUMP(" << names[n->relop] << ")\"]" << std::endl;
		out << "n" << myNodeNumber << " -- n" << node << std::endl;
		n->left->Accept(this);
		out << "n" << myNodeNumber << " -- n" << node << std::endl;
		n->right->Accept(this);
		out << "n" << myNodeNumber << " -- n" << node << std::endl;
		out << "n" << node++ << " [shape=\"hexagon\",color=\"blue\",label=\"" << n->iftrue->name << "\"]" << std::endl;
		out << "n" << myNodeNumber << " -- n" << node << std::endl;
		out << "n" << node++ << " [shape=\"hexagon\",color=\"blue\",label=\"" << n->iffalse->name << "\"]" << std::endl;
	}
	
	int visit(const SEQ* n)
	{
		long myNodeNumber = node++;
		out << "n" << myNodeNumber << " [shape=\"box\",color=\"red\",label=\"SEQ\"]" << std::endl;
		out << "n" << myNodeNumber << " -- n" << node << std::endl;
		n->left->Accept(this);
		out << "n" << myNodeNumber << " -- n" << node << std::endl;
		n->right->Accept(this);
	}
	
	int visit(const LABEL* n)
	{
		out << "n" << node++ << " [shape=\"box\",color=\"red\",label=\"LABEL(" << n->label->name << ")\"]" << std::endl;
	}

	int visit(const ExpList* ExpList)
	{
		long parentNode = node - 1;
		for( auto exp = ExpList; exp != nullptr && exp->head != nullptr; exp = exp->tail ) {
			out << "n" << parentNode << " -- n" << node << std::endl;
			exp->head->Accept(this);
		}
	}
	
	int visit(const StmList* stm)
	{
		return 0;
	}

private:
	std::ostream& out;
	long clust;
	long node;
};

}

#pragma once

#include "irtreevisitor.h"
#include "treeClasses.h"

#include <iostream>

namespace IRTree
{

	class IRTreePrintVisitor : public ITreeVisitor {
	public:
		IRTreePrintVisitor( std::ostream& stream ):
			stream( stream ),
			currentCluster( 0 ),
			currentNode( 0 )
		{
		}
		virtual ~IRTreePrintVisitor() {}

		int visit( const CodeFragment* codeFragment )
		{
			currentCluster = 0;
			currentNode = 0;
			stream << "graph \"\" {" << std::endl;
			for( auto currentCodeFragment = codeFragment; currentCodeFragment != nullptr; currentCodeFragment = currentCodeFragment->next ) {
				stream << "subgraph cluster" << currentCluster++ << " {" << std::endl;
				stream << "label=\"" << currentCodeFragment->frame->getName()->name << "\"" << std::endl;
				currentCodeFragment->retval->Accept( this );
				stream << "}" << std::endl;
			}
			stream << "}" << std::endl;
		}

		int visit( const CONST* n )
		{
			stream << "n" << currentNode++ << " [shape=\"oval\",label=\"CONST(" << n->value << ")\"]" << std::endl;
		}

		int visit( const NAME* n )
		{
			stream << "n" << currentNode++ << " [shape=\"oval\",label=\"NAME(" << n->label->name << ")\"]" << std::endl;
		}
		
		int visit( const TEMP* n )
		{
			stream << "n" << currentNode++ << " [shape=\"oval\",label=\"TEMP(" << n->temp->name << ")\"]" << std::endl;
		}
		
		int visit( const BINOP* n )
		{
			static const char* names[] = { "+", "-", "*", "/", "&&", "||", "<<", ">>", "ARSHIFT", "^" };
			const size_t myNodeNumber = currentNode++;
			stream << "n" << myNodeNumber << " [shape=\"oval\",label=\"BINOP(" << names[n->binop] << ")\"]" << std::endl;
			stream << "n" << myNodeNumber << " -- n" << currentNode << std::endl;
			n->left->Accept( this );
			stream << "n" << myNodeNumber << " -- n" << currentNode << std::endl;
			n->right->Accept( this );
		}
		
		int visit( const MEM* n )
		{
			stream << "n" << currentNode++ << " [shape=\"oval\",label=\"MEM\"]" << std::endl;
			stream << "n" << currentNode - 1 << " -- n" << currentNode << std::endl;
			n->exp->Accept( this );
		}
		
		int visit( const CALL* n )
		{
			stream << "n" << currentNode++ << " [shape=\"component\",label=\"CALL(" << n->func->name << ")\"]" << std::endl;
			if( n->args != nullptr ) {
				n->args->Accept( this );
			}
		}
		
		int visit( const ESEQ* n )
		{
			size_t myNodeNumber = currentNode++;
			stream << "n" << myNodeNumber << " [shape=\"oval\",label=\"ESEQ\"]" << std::endl;
			stream << "n" << myNodeNumber << " -- n" << currentNode << std::endl;
			n->stm->Accept( this );
			stream << "n" << myNodeNumber << " -- n" << currentNode << std::endl;
			n->exp->Accept( this );
		}

		int visit( const MOVE* n )
		{
			size_t myNodeNumber = currentNode++;
			stream << "n" << myNodeNumber << " [shape=\"box\",label=\"MOVE\"]" << std::endl;
			stream << "n" << myNodeNumber << " -- n" << currentNode << std::endl;
			n->dst->Accept( this );
			stream << "n" << myNodeNumber << " -- n" << currentNode << std::endl;
			n->src->Accept( this );
		}
		
		int visit( const EXP* n )
		{
			stream << "n" << currentNode++ << " [shape=\"box\",label=\"EXP\"]" << std::endl;
			stream << "n" << currentNode - 1 << " -- n" << currentNode << std::endl;
			n->exp->Accept( this );
		}
		
		int visit( const JUMP* n )
		{
			size_t myNodeNumber = currentNode++;
			stream << "n" << myNodeNumber << " [shape=\"box\",label=\"JUMP\"]" << std::endl;
			stream << "n" << myNodeNumber << " -- n" << currentNode << std::endl;
			n->exp->Accept( this );
			for( auto labels = n->targets; labels != nullptr && labels->label != nullptr; labels = labels->rest ) {
				stream << "n" << myNodeNumber << " -- n" << currentNode << std::endl;
				stream << "n" << currentNode++ << " [shape=\"cds\",label=\"" << labels->label->name << "\"]" << std::endl;
			}
		}
		
		int visit( const CJUMP* n )
		{
			static const char* names[] = { "==", "!=", "<", ">", "<=", ">=", "ULT", "ULE", "UGT", "UGE" };
			size_t myNodeNumber = currentNode++;
			stream << "n" << myNodeNumber << " [shape=\"box\",label=\"JUMP(" << names[n->relop] << ")\"]" << std::endl;
			stream << "n" << myNodeNumber << " -- n" << currentNode << std::endl;
			n->left->Accept( this );
			stream << "n" << myNodeNumber << " -- n" << currentNode << std::endl;
			n->right->Accept( this );
			stream << "n" << myNodeNumber << " -- n" << currentNode << std::endl;
			stream << "n" << currentNode++ << " [shape=\"cds\",label=\"" << n->iftrue->name << "\"]" << std::endl;
			stream << "n" << myNodeNumber << " -- n" << currentNode << std::endl;
			stream << "n" << currentNode++ << " [shape=\"cds\",label=\"" << n->iffalse->name << "\"]" << std::endl;
		}
		
		int visit( const SEQ* n )
		{
			size_t myNodeNumber = currentNode++;
			stream << "n" << myNodeNumber << " [shape=\"box\",label=\"SEQ\"]" << std::endl;
			stream << "n" << myNodeNumber << " -- n" << currentNode << std::endl;
			n->left->Accept( this );
			stream << "n" << myNodeNumber << " -- n" << currentNode << std::endl;
			n->right->Accept( this );
		}
		
		int visit( const LABEL* n )
		{
			stream << "n" << currentNode++ << " [shape=\"box\",label=\"LABEL(" << n->label->name << ")\"]" << std::endl;
		}

		int visit( const ExpList* ExpList )
		{
			size_t parentNode = currentNode - 1;
			for( auto exp = ExpList; exp != nullptr && exp->head != nullptr; exp = exp->tail ) {
				stream << "n" << parentNode << " -- n" << currentNode << std::endl;
				exp->head->Accept( this );
			}
		}

	private:
		std::ostream& stream;
		size_t currentCluster;
		size_t currentNode;
	};

}

#include "printvisitor.h"

class PrintVisitor : public IVisitor
{
public:
	int visit(const ArithmExp* n);
};
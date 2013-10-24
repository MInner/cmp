#include "interfaces.h"

class ArithmExp : public Expression
{
public:
	ArithmExp(Arithm op);    
private:
    const Expression* left;
	const Arithm op;
	const Expression* right;
};
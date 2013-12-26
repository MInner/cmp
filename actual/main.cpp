#include <stdio.h>
#include <iostream>

#include "enums.h"
#include "bi.hpp"
#include "printvisitor.h"
#include "buildtable.h"
#include "typecheckervisitor.h"
#include "classes.h"
#include "symbol.h"
#include "irtreevisitor.h"
#include "irtreeprintvisitor.h"
#include "codefragment.h"
#include "temp.h"

extern int yyparse();

void yyerror(const char* descr){
	printf("%s on line #%d\n", descr, yylloc.first_line);
}

// -- some STATIC things

const ProgramImpl* ProgramImpl::me = 0;
const TypeData BuildTableVisitor::NULLTYPE = TypeData();
const TypeData TypeCheckerVisitor::NULLTYPE = TypeData();
namespace Temp
{
	int Temp::curId = 1;
	int Label::curId = 1;
}

// !- static thigs

int main(void){

	std::cout << "--- Building intermediate representation tree --- " << std::endl;
	yyparse();
	PrintVisitor* pv = new PrintVisitor();
	// ProgramImpl::me->Accept(pv);

	std::cout << "--- Building table --- " << std::endl;
	BuildTableVisitor* rv = new BuildTableVisitor();
	ProgramImpl::me->Accept(rv);
	ClassTable* ctable = rv->curclasstable;

	std::cout << "--- Checking types ---" << std::endl;
	TypeCheckerVisitor* tch = new TypeCheckerVisitor(ctable);
	ProgramImpl::me->Accept(tch);

	std::cout << "--- Building Intermediate tree ---" << std::endl;

	IFrameFactory* fac = new FrameFactory_x86();

	IRTreeVisitor* irvisitor = new IRTreeVisitor(fac);
	ProgramImpl::me->Accept(irvisitor);
	return 0;

}

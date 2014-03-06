#include <stdio.h>
#include <iostream>
#include <fstream>

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
#include "irtreeoptimizationvisitor.h"
#include "irtreelineorisator.h"


extern int yyparse();



// -- some STATIC things

const ProgramImpl* ProgramImpl::me = 0;
const TypeData BuildTableVisitor::NULLTYPE = TypeData();
const TypeData TypeCheckerVisitor::NULLTYPE = TypeData();
namespace Temp
{
	int Temp::curId = 1;
	int Label::curId = 1;
}

int TypeCheckerVisitor::line = 0;

// !- static thigs

void printTree(std::string filename, const IRTree::CodeFragment* cf)
{
	std::ofstream outputFile(filename);
	IRTree::IRTreePrintVisitor* printVisitor2 = new IRTree::IRTreePrintVisitor(outputFile);
    printVisitor2->visit(cf);
    outputFile.close();

}

int main(void){

	std::cout << "--- Building intermediate representation tree --- " << std::endl;
	yyparse();
	PrintVisitor* pv = new PrintVisitor();
	ProgramImpl::me->Accept(pv);

	std::cout << "--- Building table --- " << std::endl;
	BuildTableVisitor* rv = new BuildTableVisitor();
	ProgramImpl::me->Accept(rv);
	ClassTable* ctable = rv->curclasstable;

	std::cout << "--- Checking types ---" << std::endl;
	TypeCheckerVisitor* tch = new TypeCheckerVisitor(ctable);
	ProgramImpl::me->Accept(tch);

	std::cout << "--- Building IR tree ---" << std::endl;

	IFrameFactory* fac = new FrameFactory_x86();

	IRTreeVisitor* irvisitor = new IRTreeVisitor(fac, ctable);
	ProgramImpl::me->Accept(irvisitor);
	const IRTree::CodeFragment* mainCodeFragment = NULL;
	mainCodeFragment = irvisitor->getMainFragment();

	std::cout << "--- Building graphviz tree ---" << std::endl;
	
	printTree("graph.txt", mainCodeFragment);

	std::cout << "--- Calonicial tree optimization ---" << std::endl;

	IRTree::IRTreeOptimizationVisitor* optimizeVisitor = new IRTree::IRTreeOptimizationVisitor();
	optimizeVisitor->visit(mainCodeFragment);
	mainCodeFragment = optimizeVisitor->getOptimizedCodeFramgent();

	printTree("optimized_tree.txt", mainCodeFragment);

	std::cout << "--- Lineasisator tree  ---" << std::endl;

	IRTree::IRTreeLineorisatorVisitor* lineorisatorVisitor = new IRTree::IRTreeLineorisatorVisitor();
	lineorisatorVisitor->visit(mainCodeFragment);
	mainCodeFragment = lineorisatorVisitor->getOptimizedCodeFramgent();

	std::cout << "--- Building optimized graphviz tree ---" << std::endl;

	printTree("linear_tree.txt", mainCodeFragment);
	    
	std::cout << "--- Drawing graphviz tree ---" << std::endl;
	return 0;

}

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <list>

#define PRINTPREASM 1
#define PRINTFGCON 1

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
//#include "irtreeoptimizationvisitor.h"
//#include "irtreelineorisator.h"
#include "canon.h"
#include "forestprintvisitor.h"
#include "asmgenaratorvisitor.h"
#include <set>
#include "flowgraph.h"

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
	// PrintVisitor* pv = new PrintVisitor();
	// ProgramImpl::me->Accept(pv);

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

	std::cout << "--- Calonicial tree ---" << std::endl;
	 
	IRTree::Canon* canon = new IRTree::Canon();  
	IRTree::CodeFragment* newCF = canon->linearCF(mainCodeFragment);

	std::cout << "--- Building canonical graphviz tree ---" << std::endl;

	printTree("linear.txt", newCF);

	std::cout << "--- Building canonical graphviz forest ---" << std::endl;

	std::ofstream of("forest.txt");
	IRTree::IRTreeForestPrintVisitor* forestPrintVisitor = new IRTree::IRTreeForestPrintVisitor(of);
    forestPrintVisitor->visit(newCF);
    of.close();

	std::cout << "--- Generating pre-assembler ---" << std::endl;
	Assemble::AsmGenaratorVisitor* cg = new Assemble::AsmGenaratorVisitor();
	cg->visit(newCF);
	auto rootAsmFragment = cg->getRootAsmFragment();

	std::cout << "--- Building flow-graph --- " << std::endl;

	std::ofstream fgfile("flowgraph.txt");

	auto fgBuilder = new Assemble::FlowGraphBuilder();
	fgBuilder->build(rootAsmFragment);
	fgBuilder->draw(fgfile);

	std::cout << "--- Building a var-graph --- " << std::endl;
	fgBuilder->process();
	
	std::cout << "--- Drawing graphviz trees ---" << std::endl;
	return 0;

}

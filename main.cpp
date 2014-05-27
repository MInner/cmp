#include <stdio.h>
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <boost/iterator/zip_iterator.hpp>
#include <set>
#include <sstream>

#include "snippets.h"

#define PRINTPREASM 1
#define PRINTFGCON 0
#define PRINTVARMAP 1
#define PRINTREGALLOC 0
#define PRINTCOLORING 0

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
#include "flowgraph.h"
#include "register_allocation.h"


extern int yyparse();

// -- some STATIC things



const ProgramImpl* ProgramImpl::me = 0;
const TypeData BuildTableVisitor::NULLTYPE = TypeData();
const TypeData TypeCheckerVisitor::NULLTYPE = TypeData();
namespace Temp
{
	int Temp::curId = 1;
	int Label::curId = 1;
	std::map<const std::string, const Temp*> Temp::m = std::map<const std::string, const Temp*>();
}

namespace Assemble
{
	std::map<const Temp::Temp*, VarGraphNode*> VarGraphNode::m = std::map<const Temp::Temp*, VarGraphNode*>();
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
	Assemble::AsmGenaratorVisitor* asmgen = new Assemble::AsmGenaratorVisitor();
	asmgen->visit(newCF);
	auto rootAsmFragment = asmgen->getRootAsmFragment();

	std::cout << "--- Building flow-graph --- " << std::endl;

	std::ofstream fgfile("flowgraph.txt");
	std::ofstream vargfile("vargraph.txt");

	auto fgBuilder = new Assemble::FlowGraphBuilder();
	fgBuilder->build(rootAsmFragment);
	fgBuilder->draw(fgfile);

	std::cout << "--- Building a var-graph --- " << std::endl;

	std::vector<std::string> regnames = {"AX", "BX", "CX", "DX"};

	auto vg_list = fgBuilder->buildVarGraph();

	std::cout << "Finally" << std::endl;

	auto af = rootAsmFragment;

	list<Assemble::VarGraph*> cvargraph_list;
	for (int i = 0; i < vg_list.size(); i++)
	{
		if (af == 0)
		{
			std::cout << "Strang on sizes of vg, fg, af" << std::endl;
		}

	    std::list<Assemble::VarGraph*>::iterator vg = std::next(vg_list.begin(), i);
	    std::list<Assemble::FlowGraph*>::iterator fg = std::next(fgBuilder->flowgraph_list.begin(), i);

		(*vg)->printGr();
		(*vg)->preColor(regnames);
		(*vg)->draw(vargfile, vg_list);

		auto regAllocator = new RegisterAllocation::RegAllocator();
		auto coloredGraph = regAllocator->colorGraph((*vg),(*fg) , regnames.size());

		cvargraph_list.push_back(coloredGraph);

	    std::ofstream cvargfile("vargraphInColor.txt");
		coloredGraph->draw(cvargfile, cvargraph_list);

		coloredGraph->mapVarsToRegisters(regnames);

		af->writeMappedTemps(coloredGraph->regmapping);
		af->writePrologueEpilogue(regnames);

		af = af->next;
	}

	std::ofstream asmfile("asmfile.txt");

	for (af = rootAsmFragment; af != 0; af = af->next)
	{
		asmfile << af->frame->getName()->name << ":" << std::endl;
		for (auto line : af->code)
		{
			asmfile << "	" << line << std::endl;
		}
	}


	std::cout << "--- End Drawing graphviz trees ---" << std::endl;
	return 0;

}

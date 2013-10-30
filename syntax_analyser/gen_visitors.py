"""
"""

f = open('classes.txt')

data = []

for line in f:
	classline = line.strip()
	first = classline.split("|")[0]
	classname = first.split(" ")[0]
	tovisit = first.strip().split()[1:]
	tocout = classline.split("|")[1].strip().split()
	data.append((classname, tocout, tovisit))

def gen_virtual_functions():
	for (classname, _, _) in data:
		print "virtual int visit(const %s* n) = 0;" % classname
	
def gen_print_visitor():
	pv = open('printvisitor.h', 'w')
	pv.write("""#pragma once

#include "visitor.h"
#include "fwdclasses.h"
#include <iostream>
#include <string>

class PrintVisitor : public IVisitor
{
public:

	int padding;
""")

	for (classname, tocout, tovisit) in data:
		coutexpr = ""
		if len(tocout) > 0:
			coutexpr = ' << ", " << '.join(["n->%s" % x for x in tocout]) + " << "

		visitexprlist = []
		for visel in tovisit:
			if visel != 'list':
				visitexprlist += ["\t\tn->%s->Accept(this);" % visel]
			else:
				visitexprlist += ['\t\tif(n->list) {n->list->Accept(this);}']

		visitexpr = '\n'.join(visitexprlist)

		pv.write("""
	int visit(const %s* n)
	{
		padding += 1;
		std::cout << std::string(padding, ' ') << "%s: (" << %s ")" << std::endl;
%s
		std::cout << std::string(padding, ' ') << "/%s" << std::endl;
		padding -= 1;
		return 0;
	}
""" % (classname, classname, coutexpr, visitexpr, classname) )

	pv.write('};')

def gen_fwdclasses_h():
	fwd = open('fwdclasses.h', 'w')
	fwd.write('#pragma once\n\n')
	for (classname, tocout, tovisit) in data:
		fwd.write('class %s;\n' % classname)

def main():
	gen_print_visitor()

main()
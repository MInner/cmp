f = open('cl.txt')

for line in f:
	classline = line.strip()
	first = classline.split("|")[0]
	classname = first.split(" ")[0]
	tovisit = first.strip().split()[1:]
	tocout = classline.split("|")[1].strip().split()

	# (!!!) virtual functions 
	# print "virtual int visit(const %s* n) = 0;" % classname
	
	# (!!!) functions implementations
	coutexpr = " << ".join(tocout)
	visitexpr = '\n'.join(['\t\tn->%s->Accept(this);' % visel for visel in tovisit])
	print """
	int visit(const %s* n)
	{
		std::cout << "%s: (" << %s << ")" << std::endl;

%s

		return 0;
	}""" % (classname, classname, coutexpr, visitexpr)
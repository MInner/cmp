f = open('cl.txt')

for line in f:
	classname = line.strip()
	# print "virtual int visit(const %s* n) = 0;" % classname
	print """
int visit(const %s* n)
{
	std::cout << "%s: " << std::endl;
	return 0;
}""" % (classname, classname)
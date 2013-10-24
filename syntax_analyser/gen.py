string = open('simple_java.y').read().split('%%')[1];

out = open('interfaces.h', 'w')
union = open('union.h', 'w')
types = open('types.h', 'w')

out.write('#pragma ones \n\n')

string = string.replace('\n', ' ')
string = string.replace('\t', ' ')

parts = string.split(':')[:-1]

classes = [ part.split()[-1] for part in parts ]

union.write("%" + "union { \n")

for cl in classes:
	classname = cl[0].upper()+cl[1:]
	out.write("""class I%s 
{
public: 
	virtual ~I%s() {};
}; \n""" % (classname, classname) )
	union.write("const I%s* %s; \n" % (classname, cl) )
	types.write("%"+"type <%s> %s\n" % (cl, cl))

union.write('} \n')
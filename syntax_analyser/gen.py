string = open('simple_java.y').read().split('%%')[1];

out = open('interfaces.h', 'w')
union = open('union.h', 'w')

string = string.replace('\n', ' ')
string = string.replace('\t', ' ')

parts = string.split(':')[:-1]

classes = [ part.split()[-1] for part in parts ]

union.write("%" + "union { \n")

for cl in classes:
	classname = cl[0].upper()+cl[1:]
	out.write("class %s { virtual %s~() {} }; \n" % (classname, classname) )
	union.write("const %s* %s; \n" % (classname, cl) )

union.write('} \n')
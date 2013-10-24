string = open('simple_java.y').read().split('%%')[1];

out = open('interfaces.h', 'w')

string = string.replace('\n', ' ')
string = string.replace('\t', ' ')

parts = string.split(':')[:-1]

classes = [ part.split()[-1] for part in parts ]

for cl in classes:
	out.write("""class %s { virtual %s~() {} }; \n""" % (cl[0].upper()+cl[1:], cl[0].upper()+cl[1:]))
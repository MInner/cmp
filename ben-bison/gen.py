string = open('file.y').read().split('%%')[1];

out = open('interfaces.h', 'w')

for st in string.split(';'):
 	name = st.split(' ')[0][:-1].strip()
 	if len(name) > 2 :
 		out.write("""class I%s 
{
	virtual ~I%s() {}
};
""" % (name, name) )
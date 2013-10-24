all:
	flex -ofl.cpp file.lex
	# cat union.h > simple_java.y.tml
	cat simple_java.y >> simple_java.y.tml
	bison -obi.cpp -yd simple_java.y -v
	gcc lex.yy.c bi.cpp -o result
	
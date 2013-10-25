all:
	rm -f fl.cpp *.output bi.cpp bi.hpp
	flex -ofl.cpp file.lex
	bison -yd simple_java.y -obi.cpp -v
	g++ main.cpp fl.cpp bi.cpp -o result 2> gcc.log || cat gcc.log | less
	rm -f fl.cpp *.output bi.cpp bi.hpp gcc.log

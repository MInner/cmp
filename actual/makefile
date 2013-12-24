all:
	rm -f fl.cpp *.output bi.cpp bi.hpp tree.txt
	flex -ofl.cpp file.lex
	bison -yd simple_java.y -obi.cpp -v 
	g++ -std=c++0x main.cpp symbol.cpp fl.cpp bi.cpp symbolstable.cpp -o mjv -pedantic-errors 2> gcc.log || cat gcc.log | less
	rm -f fl.cpp bi.cpp bi.hpp gcc.log

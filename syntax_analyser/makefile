all:
	rm -f fl.cpp *.output bi.cpp bi.hpp
	flex -ofl.cpp file.lex
	bison -yd simple_java.y -obi.cpp
	gcc main.cpp fl.cpp bi.cpp -o result
	rm -f fl.cpp *.output bi.cpp bi.hpp

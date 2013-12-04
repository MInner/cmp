rm -f fl.cpp *.output bi.cpp bi.hpp tree.txt
flex -ofl.cpp file.lex
bison -yd simple_java.y -obi.cpp -v
# g++ main.cpp symbol.cpp fl.cpp bi.cpp symbolstable.cpp -o mjv 2> gcc.log || cat gcc.log | less
# rm -f fl.cpp *.output bi.cpp bi.hpp gcc.log

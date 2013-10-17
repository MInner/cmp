#include <iostream>

using namespace std;

int yyparse();

int main()
{
    std::cout << "Gitve me input" << std::endl;
    yyparse();
    return 0;
}

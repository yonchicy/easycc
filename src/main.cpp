
#include <iostream>
#include "../include/node.hpp"
#include "./frontend/parser.hpp"

extern int yyparse();
extern NProgram *programBlock;
int main(int argc,char* argv[]){
    yyparse();
    return 0;
}

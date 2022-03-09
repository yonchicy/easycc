
#include <cstdio>
#include <iostream>
#include "../include/node.hpp"
#include "./frontend/parser.hpp"

extern int yyparse();
extern int     yyrestart(FILE*);
extern FILE *yyin;
extern NProgram *programBlock;
int main(int argc,char* argv[]){
    // 处理input_file
    if (argc<2) {
        yyparse();
        return 0;
    }
    for (int i=1; i<argc; i++) {
        yyin = fopen(argv[i], "r");

        if(!yyin){
            perror(argv[i]);
        }
        yyparse();
    }
    return 0;
}

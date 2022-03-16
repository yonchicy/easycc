
#include <cstdio>
#include <iostream>
#include "../include/error.h"
#include "../include/node.h"
#include "./frontend/parser.hpp"

extern int yyparse();
extern int     yyrestart(FILE*);
extern FILE *yyin;
int yyline;
extern NProgram *programBlock;
int main(int argc,char* argv[]){
    // 处理input_fil
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
    programBlock->gen();
    return 0;
}

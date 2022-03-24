
#include <getopt.h>
#include <cstdio>
#include <iostream>
#include <cstring>
#include "../include/error.h"
#include "../include/node.h"
#include "./frontend/parser.hpp"

extern int yyparse();
extern int     yyrestart(FILE*);
extern FILE *yyin;
int yyline;
extern NProgram *programBlock;
FILE *output;
int main(int argc,char* argv[]){
    // 处理input_fil
    if (argc<2) {
        yyparse();
        return 0;
    }
    char *input_file = nullptr, *output_file = nullptr;
    for(int ch; (ch = getopt(argc, argv, "O:So:")) != -1;)
    {
      switch(ch)
      {
      case 'S':
        break; // 啥也不干，为了测评机
      case 'o':
        output_file = strdup(optarg);
        break;
      case 'O':
        break;
      default:
        break;
      }
    }
    input_file = argv[argc-1];
    yyin = fopen(input_file,"r");
    if(output_file!= nullptr){
      output = fopen(output_file,"w");
    }
    else{
      output = stdout;
    }


    if(!yyin)
      perror(input_file);
    yyparse();
    programBlock->show_ast();
    programBlock->gen();
    return 0;
}

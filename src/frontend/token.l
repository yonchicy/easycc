%option noyywrap nodefault yylineno
%{


#include "parser.tab.h"
#include "parser.hpp"

#define SAVE_TOKEN yylval.string = new std::string(yytext,yyleng)
#define TOKEN(t) (yylval.token=t)
%}


%%
[ \t\n] ;
[0-9]+ SAVE_TOKEN; return TOKEN(TINTEGER);
";" return TOKEN(TSEMICOLOM)
%%

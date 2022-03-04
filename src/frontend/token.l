%option noyywrap nodefault yylineno
%{

#include <string>
#include "../../include/node.hpp"
#include "./parser.hpp"

#define SAVE_TOKEN yylval.string = new std::string(yytext,yyleng)
#define TOKEN(t) (yylval.token=t)
%}


%%

[ \t\n] ;
[0-9]+ SAVE_TOKEN; return TOKEN(TINTEGER);
[a-zA-Z_][a-zA-Z0-9_]* SAVE_TOKEN; return TIDENTIFIER;
";" return TOKEN(TSEMICOLOM);

%%

%option noyywrap yylineno
%{

#include <string>
#include <iostream>
#include "../../include/node.hpp"
#include "./parser.hpp"

#define SAVE_TOKEN yylval.string = new std::string(yytext,yyleng)
#define TOKEN(t) (yylval.token=t)
%}


%%

[ \t\n] ;
[0-9]+  {std::cout<<"get integer\n";SAVE_TOKEN; return TOKEN(TINTEGER);}
"return" {std::cout<<"get return \n";SAVE_TOKEN;return TOKEN(TRETURN);}
"main" {std::cout<<"get main\n";SAVE_TOKEN;return TOKEN(TMAIN);}
"int" {std::cout<<"get int\n";SAVE_TOKEN;return TOKEN(TINT);}

[a-zA-Z_][a-zA-Z0-9_]* {std::cout<<"get identifier\n";SAVE_TOKEN; return TIDENTIFIER;}

";" {std::cout<<"get ;\n";return TOKEN(TSEMICOLOM);}

%%

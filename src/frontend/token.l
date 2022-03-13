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

[ \t\n] {}
[0-9]+  {SAVE_TOKEN; return TINTEGER;}
"return" {return TOKEN(TRETURN);}
"main" {return TOKEN(TMAIN);}
"int" {return TOKEN(TINT);}

[a-zA-Z_][a-zA-Z0-9_]* {SAVE_TOKEN; return TIDENTIFIER;}

";" {return TOKEN(TSEMICOLOM);}
"(" {return TOKEN(TLPAREN);}
")" {return TOKEN(TRPAREN);}
"{" {return TOKEN(TLBPAREN);}
"}" {return TOKEN(TRBPAREN);}
"-" {return TOKEN(TMINUS);}
"!" {return TOKEN(TNOT);}
"~" {return TOKEN(TWAVE);}
<<EOF>> {yyterminate();}
%%

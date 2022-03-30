%option noyywrap yylineno
%{

#include <string>
#include <iostream>
#include "../../include/node.h"
#include "./parser.hpp"
extern int yyline;

#define SAVE_TOKEN yylval.string = new std::string(yytext,yyleng)
#define TOKEN(t) (yylval.token=t)
%}


%%

[ \t] {}
\n {yyline++;}
[0-9]+  {SAVE_TOKEN; return TINTEGER;}
"return" {return TOKEN(TRETURN);}
"int" {return TOKEN(TINT);}

[a-zA-Z_][a-zA-Z0-9_]* {SAVE_TOKEN; return TIDENTIFIER;}

";"  {return TOKEN(TSEMICOLOM);}
"("  {return TOKEN(TLPAREN);}
")"  {return TOKEN(TRPAREN);}
"{"  {return TOKEN(TLBPAREN);}
"}"  {return TOKEN(TRBPAREN);}

"-"  {return TOKEN(TMINUS);}
"!"  {return TOKEN(TNOT);}
"~"  {return TOKEN(TWAVE);}

"+"  {return TOKEN(TPLUS);}
"/"  {return TOKEN(TDIV);}
"*"  {return TOKEN(TMULTI);}
"%"  {return TOKEN(TMOD);}

"<"  {return TOKEN(TL);}
"<=" {return TOKEN(TLE);}
">"  {return TOKEN(TG);}
">=" {return TOKEN(TGE);}
"!=" {return TOKEN(TNE);}
"==" {return TOKEN(TE);}
"&&" {return TOKEN(TLOGAND);}
"||" {return TOKEN(TLOGOR);}

"=" {return TOKEN(TASSIGN);}
<<EOF>> {yyterminate();}
%%

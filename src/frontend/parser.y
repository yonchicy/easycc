%{
    #include "../../include/node.h"
    NFunctionDeclaration *programBlock;
    extern int yylex();
    void yyerror(const char*s){printf("ERROR:%s\n",s);}
%}

%union{
NStatement *stmt;
NExpression *expr;
NIdentifier *ident;
NType *type;
int token;
std::string *string;
}

%token <string> TIDENTIFIER TINTEGER TTYPE
%token <token> TSEMICOLOM

%type <ident> ident
%type <epxr> expr
%type <type> type
%type <stmt> stmt func_decl
%type <token> comparison


%start program

program 
    : function {programBlock = $1;}
        ;
function 
    : type ident '(' ')' '{' stmt '}' {$$=new NFunctionDeclaration(*$1,*$2,*$6);}

type 
    : TTYPE {$$=new NType(*$1); delete $1;}

statement
    : 'return' expr ';' {}

expr:
    :TINTEGER {$$=new NInteger(atoi($1->c_str()));delete $1;}


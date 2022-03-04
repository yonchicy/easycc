%{
    #include "../../include/node.hpp"
    NProgram *programBlock;
    extern int yylex();
    void yyerror(const char*s){printf("ERROR:%s\n",s);}
%}

%union{
NStatement *stmt;
NExpression *expr;
NIdentifier *ident;
NFunctionDeclaration * func_decl;
NType *type;
int token;
std::string *string;
NProgram *program;
}

%token <string> TIDENTIFIER TINTEGER 
%token <token> TSEMICOLOM

%type <expr> expression
%type <type> type
%type <stmt> statement 
%type <func_decl> function
%type <program> program


%start program
%%
program
    : function {programBlock = new NProgram(*$1);}
        ;
function
    : type TIDENTIFIER '(' ')' '{' statement '}' {$$=new NFunctionDeclaration(*$1,*$2,*$6);}
;
type
    : "int" {$$=new NType(std::string("int"));}
;
statement
   : "return" expression ';'{$$ = new NReturnStatement(*$2);}
;
expression
    : TINTEGER {$$=new NInteger(atoi($1->c_str()));delete $1;}
    ;
%%

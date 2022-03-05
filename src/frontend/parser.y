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
%token <token> TMAIN
%token <token> TINT
%token <token> TRETURN TLPAREN TRPAREN TLBPAREN TRBPAREN

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
    : type TMAIN TLPAREN TRPAREN TLBPAREN statement TRBPAREN {$$=new NFunctionDeclaration(*$1,std::string("main"),*$6);}
;
type
    : TINT {$$=new NType(std::string("int"));}
;
statement
   : TRETURN expression TSEMICOLOM {$$ = new NReturnStatement(*$2);}
;
expression
    : TINTEGER {std::cout<<"get expression\n";$$=new NInteger(atoi($1->c_str()));delete $1;}
    ;
%%

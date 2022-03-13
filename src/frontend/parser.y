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
NUnaryBase *unary;
int token;
std::string *string;
NProgram *program;
}

%token <string> TIDENTIFIER TINTEGER  
%token <token> TSEMICOLOM 
%token <token> TMAIN
%token <token> TINT
%token <token> TRETURN TLPAREN TRPAREN TLBPAREN TRBPAREN TMINUS TNOT TWAVE

%type <expr> expression
%type <unary> unary
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
    :unary {$$=new NExpression(*$1);}
unary
    : TINTEGER {$$=new NInteger(atoi($1->c_str()));delete $1;}
    | TMINUS unary {$$ = new NUnary(std::string("-"),*$2);}
    | TNOT unary {$$ = new NUnary(std::string("!"),*$2);}
    | TWAVE unary {$$ = new NUnary(std::string("~"),*$2);}
    ;
%%

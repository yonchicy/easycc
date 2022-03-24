%{
    #include "../../include/node.h"
    NProgram *programBlock;
    extern int yyline;
    extern int yylex();
    void yyerror(const char*s){printf("ERROR:Line:%d\n%s\n",yyline,s);}
%}

%union{
NStatement            *stmt;
NExpression           *expr;
NIdentifier           *ident;
NFunctionDeclaration  * func_decl;
NType                 *type;
NAdditive             *additive;
NMultiplicative       *multiplicative;
NPrimary              *primary;
NUnary                *unary;
std::string           *string;
NProgram              *program;
int                   token;
}

%token  <string>          TIDENTIFIER TINTEGER
%token  <token>           TSEMICOLOM
%token  <token>           TMAIN
%token  <token>           TINT
%token  <token>           TRETURN TLPAREN TRPAREN TLBPAREN TRBPAREN TMINUS TNOT TWAVE TPLUS TDIV TMOD TMULTI

%type   <expr>            expression
%type   <unary>           unary
%type   <type>            type
%type   <stmt>            statement
%type   <func_decl>       function
%type   <program>         program
%type   <additive>        additive
%type   <multiplicative>  multiplicative
%type   <primary>         primary

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
    :additive {$$ = new NExpressionAdditive(*$1);}
    ;
additive
    : multiplicative {$$ = new NAdditiveMultipicative(*$1);}
    | additive TPLUS multiplicative 
        {$$=new NAddtiveOprtMulti(
            *$1,
            std::string("+"),
            $3);}
    | additive TMINUS multiplicative
        {$$=new NAddtiveOprtMulti(
            *$1,
            std::string("-"),
            $3);}
    ;
multiplicative
    :unary {$$=new NMultiplicativeUnary(*$1);}
    | multiplicative TMULTI unary
        {$$=new NMultiplicativeOprtUnary(
                *$1,
                std::string("*"),
                *$3
        );}
    | multiplicative TDIV unary
        {$$=new NMultiplicativeOprtUnary(
                *$1,
                std::string("/"),
                *$3
        );}
    | multiplicative TMOD unary
        {$$=new NMultiplicativeOprtUnary(
                *$1,
                std::string("%"),
                *$3
        );}
;
unary
    : primary{$$=new NUnaryPrimary(*$1);}
    | TMINUS unary {$$ = new NUnaryWithOperator(std::string("-"),*$2);}
    | TNOT unary {$$ = new NUnaryWithOperator(std::string("!"),*$2);}
    | TWAVE unary {$$ = new NUnaryWithOperator(std::string("~"),*$2);}
    ;

primary
    : TINTEGER {$$=new NInteger(atoi($1->c_str()));delete $1;}
    | TLPAREN expression TRPAREN {$$ = new NPrimaryExpression(*$2);}
    ;
%%

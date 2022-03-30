%{
    #include "../../include/node.h"
    NProgram *programBlock;
    extern int yyline;
    extern int yylex();
    void yyerror(const char*s){printf("ERROR:Line:%d\n%s\n",yyline,s);}
%}

%union{
NStatement           *stmt;
NExpression          *expr;
NLogicalOr           *logical_or;
NLogicalAnd          *logical_and;
NEquality            *equality;
NRelational          *relational;
NIdentifier          *ident;
NFunctionDeclaration *func_decl;
NType                *type;
NAdditive            *additive;
NMultiplicative      *multiplicative;
NPrimary             *primary;
NUnary               *unary;
std::string          *string;
NProgram             *program;
int                  token;
}

%token <string>        TIDENTIFIER TINTEGER
%token <token>         TSEMICOLOM
%token <token>         TMAIN
%token <token>         TINT
%token <token>         TRETURN TLPAREN TRPAREN TLBPAREN TRBPAREN TMINUS TNOT TWAVE TPLUS TDIV TMOD TMULTI
%token <token>         TL TLE TG TGE TNE TE TLOGAND TLOGOR

%type <expr>           expression
%type <unary>          unary
%type <type>           type
%type <stmt>           statement
%type <func_decl>      function
%type <program>        program
%type <additive>       additive
%type <multiplicative> multiplicative
%type <primary>        primary

%type <logical_or>     logical_or;
%type <logical_and>    logical_and;
%type <equality>       equality;
%type <relational>     relational;

%start program
%%
program
    : function {programBlock = new NProgram(*$1);}
        ;
function
    : type TIDENTIFIER TLPAREN TRPAREN TLBPAREN statement TRBPAREN {$$=new NFunctionDeclaration(*$1,*$2,*$6);}
;
type
    : TINT {$$=new NType(std::string("int"));}
;
statement
   : TRETURN expression TSEMICOLOM {$$ = new NReturnStatement(*$2);}
;

expression
    : logical_or {$$=new NExpressionLogicalOr($1);}
    ;

logical_or 
    : logical_and{$$=new NLogicalOrAnd($1);}
    | logical_or TLOGOR logical_and {$$=new NLogicalORBinary($1,$3);}
    ;

logical_and

    : equality {$$=new NLogicalAndEquality($1);}
    | logical_and TLOGAND equality{$$=new NLogicalAndBinary($1,$3);}
    ;
equality
    : relational {$$=new NEqualityRelational($1);}
    | equality TE relational{$$=new NEqualityBinary($1,std::string("=="),$3);}
    | equality TNE relational {$$=new NEqualityBinary($1,std::string("!="),$3);}

relational
    :additive {$$ = new NRelationalAdditive($1);}
    | relational TL additive{$$ = new NRelationalBinary($1,std::string("<"),$3);}
    | relational TLE additive{$$ = new NRelationalBinary($1,std::string("<="),$3);}
    | relational TG additive{$$ = new NRelationalBinary($1,std::string(">"),$3);}
    | relational TGE additive{$$ = new NRelationalBinary($1,std::string(">="),$3);}
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

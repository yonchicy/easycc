/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_HOME_YONCHICY_COMPILER_EASYCC_INCLUDE_FRONTEND_PARSER_H_INCLUDED
# define YY_YY_HOME_YONCHICY_COMPILER_EASYCC_INCLUDE_FRONTEND_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TIDENTIFIER = 258,             /* TIDENTIFIER  */
    TINTEGER = 259,                /* TINTEGER  */
    TSEMICOLOM = 260,              /* TSEMICOLOM  */
    TMAIN = 261,                   /* TMAIN  */
    TINT = 262,                    /* TINT  */
    TRETURN = 263,                 /* TRETURN  */
    TLPAREN = 264,                 /* TLPAREN  */
    TRPAREN = 265,                 /* TRPAREN  */
    TLBPAREN = 266,                /* TLBPAREN  */
    TRBPAREN = 267,                /* TRBPAREN  */
    TMINUS = 268,                  /* TMINUS  */
    TNOT = 269,                    /* TNOT  */
    TWAVE = 270,                   /* TWAVE  */
    TPLUS = 271,                   /* TPLUS  */
    TDIV = 272,                    /* TDIV  */
    TMOD = 273,                    /* TMOD  */
    TMULTI = 274,                  /* TMULTI  */
    TL = 275,                      /* TL  */
    TLE = 276,                     /* TLE  */
    TG = 277,                      /* TG  */
    TGE = 278,                     /* TGE  */
    TNE = 279,                     /* TNE  */
    TE = 280,                      /* TE  */
    TLOGAND = 281,                 /* TLOGAND  */
    TLOGOR = 282,                  /* TLOGOR  */
    TASSIGN = 283                  /* TASSIGN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 14 "/home/yonchicy/compiler/easycc/src/frontend/parser.y"

NStatement                *stmt;
NStatements               *stmts;
NAssign               *assignment;
NExpression               *expr;
NLogicalOr                *logical_or;
NLogicalAnd               *logical_and;
NEquality                 *equality;
NRelational               *relational;
NIdentifier               *ident;
NFunctionDeclaration      *func_decl;
NType                     *type;
NAdditive                 *additive;
NMultiplicative           *multiplicative;
NPrimary                  *primary;
NUnary                    *unary;
std::string               *string;
NProgram                  *program;
NDeclaration              *declaration;
int                       token;

#line 114 "/home/yonchicy/compiler/easycc/include/frontend/parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_HOME_YONCHICY_COMPILER_EASYCC_INCLUDE_FRONTEND_PARSER_H_INCLUDED  */

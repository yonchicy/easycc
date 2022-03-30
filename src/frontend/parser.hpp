/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_SRC_FRONTEND_PARSER_HPP_INCLUDED
# define YY_YY_SRC_FRONTEND_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TIDENTIFIER = 258,
    TINTEGER = 259,
    TSEMICOLOM = 260,
    TMAIN = 261,
    TINT = 262,
    TRETURN = 263,
    TLPAREN = 264,
    TRPAREN = 265,
    TLBPAREN = 266,
    TRBPAREN = 267,
    TMINUS = 268,
    TNOT = 269,
    TWAVE = 270,
    TPLUS = 271,
    TDIV = 272,
    TMOD = 273,
    TMULTI = 274,
    TL = 275,
    TLE = 276,
    TG = 277,
    TGE = 278,
    TNE = 279,
    TE = 280,
    TLOGAND = 281,
    TLOGOR = 282
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 9 "src/frontend/parser.y"

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

#line 104 "src/frontend/parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_FRONTEND_PARSER_HPP_INCLUDED  */

/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     LT = 258,
     GT = 259,
     AMP = 260,
     LPAREN = 261,
     VBAR = 262,
     DOT = 263,
     DEBUG = 264,
     NEWLINE = 265,
     TILDE = 266,
     LS = 267,
     SETENV = 268,
     PATH = 269,
     PROMPT = 270,
     CD = 271,
     BYE = 272,
     ALIAS = 273,
     UNALIAS = 274,
     PWD = 275,
     EXTEND = 276,
     ALIASLOOP = 277,
     UNSETENV = 278,
     PRINTENV = 279,
     QUOTE = 280,
     PIPE = 281,
     BACKGROUND = 282,
     BACKSLASH = 283,
     WORD = 284,
     SPACE = 285,
     VARIABLE = 286,
     VALUE = 287,
     STRING = 288,
     OPTION = 289
   };
#endif
/* Tokens.  */
#define LT 258
#define GT 259
#define AMP 260
#define LPAREN 261
#define VBAR 262
#define DOT 263
#define DEBUG 264
#define NEWLINE 265
#define TILDE 266
#define LS 267
#define SETENV 268
#define PATH 269
#define PROMPT 270
#define CD 271
#define BYE 272
#define ALIAS 273
#define UNALIAS 274
#define PWD 275
#define EXTEND 276
#define ALIASLOOP 277
#define UNSETENV 278
#define PRINTENV 279
#define QUOTE 280
#define PIPE 281
#define BACKGROUND 282
#define BACKSLASH 283
#define WORD 284
#define SPACE 285
#define VARIABLE 286
#define VALUE 287
#define STRING 288
#define OPTION 289




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 19 "shellProject.y"
{
    int integer;
    char *string;
    char *word;
    char *option;
}
/* Line 1529 of yacc.c.  */
#line 124 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;


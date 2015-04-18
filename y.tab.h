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
     PERIODPERIOD = 268,
     SETENV = 269,
     PATH = 270,
     PROMPT = 271,
     CD = 272,
     BYE = 273,
     ALIAS = 274,
     UNALIAS = 275,
     PWD = 276,
     EXTEND = 277,
     PERIOD = 278,
     ALIASLOOP = 279,
     UNSETENV = 280,
     PRINTENV = 281,
     QUOTE = 282,
     PIPE = 283,
     BACKGROUND = 284,
     BACKSLASH = 285,
     LEFTBRACE = 286,
     RIGHTBRACE = 287,
     DOLLARSIGN = 288,
     LTLT = 289,
     GTGT = 290,
     WORD = 291,
     SPACE = 292,
     VARIABLE = 293,
     VALUE = 294,
     STRING = 295,
     OPTION = 296,
     ENVEXP = 297
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
#define PERIODPERIOD 268
#define SETENV 269
#define PATH 270
#define PROMPT 271
#define CD 272
#define BYE 273
#define ALIAS 274
#define UNALIAS 275
#define PWD 276
#define EXTEND 277
#define PERIOD 278
#define ALIASLOOP 279
#define UNSETENV 280
#define PRINTENV 281
#define QUOTE 282
#define PIPE 283
#define BACKGROUND 284
#define BACKSLASH 285
#define LEFTBRACE 286
#define RIGHTBRACE 287
#define DOLLARSIGN 288
#define LTLT 289
#define GTGT 290
#define WORD 291
#define SPACE 292
#define VARIABLE 293
#define VALUE 294
#define STRING 295
#define OPTION 296
#define ENVEXP 297




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 20 "shellProject.y"
{
    int   integer;
    char *string;
    char *word;
    char *option;
    char *envexp;
}
/* Line 1529 of yacc.c.  */
#line 141 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;


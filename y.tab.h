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
     SETENV = 266,
     PATH = 267,
     PROMPT = 268,
     CD = 269,
     BYE = 270,
     ALIAS = 271,
     UNALIAS = 272,
     PWD = 273,
     EXTEND = 274,
     ALIASLOOP = 275,
     UNSETENV = 276,
     PRINTENV = 277,
     QUOTE = 278,
     PIPE = 279,
     BACKGROUND = 280,
     BACKSLASH = 281,
     TILDE = 282,
     WORD = 288,
     STRING = 289
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
#define SETENV 266
#define PATH 267
#define PROMPT 268
#define CD 269
#define BYE 270
#define ALIAS 271
#define UNALIAS 272
#define PWD 273
#define EXTEND 274
#define ALIASLOOP 275
#define UNSETENV 276
#define PRINTENV 277
#define QUOTE 278
#define PIPE 279
#define BACKGROUND 280
#define BACKSLASH 281
#define TILDE 282
#define WORD 288
#define STRING 289




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 17 "shellProject.y"
{
    int integer;
    char *string;
    char *word;
}
/* Line 1529 of yacc.c.  */
#line 113 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;


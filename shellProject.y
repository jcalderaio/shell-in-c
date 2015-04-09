%{
#include <stdio.h>
#include <string.h>
#include "shellProject.h"

/*-------------------------------------------------------------------------------------
 * shellProject.y - yacc specification file for the parser generator
 *------------------------------------------------------------------------------------
 */

int eventcount = 0;
 /* parse local working data section */
 COMMAND *q, *p;
 int pfd[2];
%}

%union{
    int integer;
    char *string;
    char *word;
}

%token <integer> LT GT AMP LPAREN VBAR DOT DEBUG NEWLINE
%token <integer> SETENV PATH PROMPT CD BYE ALIAS UNALIAS PWD EXTEND
%token <integer> ALIASLOOP UNSETENV PRINTENV QUOTE PIPE BACKGROUND BACKSLASH TILDE
%token <word> WORD
%token <string> STRING

%start cmd

%%

cmd:              builtin.cmd
                        { eventcount++; }
                | simple.cmd
                        { eventcount++; }
                ;


builtin.cmd:    CD WORD
                        { bicmd = CDX; }
                | CD STRING
                        { bicmd = CDX; }
                | BYE
                        { bicmd = BYE_CMD; return 0; }
                | NEWLINE
                        { bicmd = NEWLINE; return 0;}
                ;

simple.cmd:     exec.cmd
                ;


exec.cmd:         WORD{
                        input_command = $1;
                        argv[0] = $1;
                        argv[1] = NULL;
                        return 0;
                  }
                  ;
%%

int yyerror(char *s){
    fprintf(stderr, "*%s*\n", s);
    return 0;
}


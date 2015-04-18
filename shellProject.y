%{
#include <stdio.h>
#include <string.h>
#include "shellProject.h"

/*-------------------------------------------------------------------------------------
 * shellProject.y - yacc specification file for the parser generator
 *--------------------------------------------------------------------------------------*/

int eventcount = 0;

 /* parse local working data section */

 COMMAND *q, *p;

 int pfd[2];

%}

%union{
    int   integer;
    char *string;
    char *word;
    char *option;
    char *envexp;
}

%token <integer> LT GT AMP LPAREN VBAR DOT DEBUG NEWLINE TILDE LS PERIODPERIOD
%token <integer> SETENV PATH PROMPT CD BYE ALIAS UNALIAS PWD EXTEND PERIOD
%token <integer> ALIASLOOP UNSETENV PRINTENV QUOTE PIPE BACKGROUND BACKSLASH
%token <integer> LEFTBRACE RIGHTBRACE DOLLARSIGN LTLT GTGT
%token <word>    WORD SPACE VARIABLE VALUE
%token <string>  STRING
%token <option>  OPTION
%token <envexp>  ENVEXP

%start cmd

%%

cmd:              builtin.cmd

                | simple.cmd

                ;

builtin.cmd:    TILDE NEWLINE
                        {
                        bicmd = CDHome_CMD;
                        builtin = 1;
                        return 0;
                        }
                |  CD NEWLINE
                        {
                        bicmd = CDHome_CMD;
                        builtin = 1;
                        return 0;
                        }
                | CD WORD NEWLINE
                        {
                        bicmd = CDPath_CMD;
                        builtin = 1;
                        strPath = $2;
                        return 0;
                        }
                | CD TILDE NEWLINE
                        {
                        bicmd = CDHome_CMD;
                        builtin = 1;
                        return 0;
                        }
                | CD TILDE WORD NEWLINE
                        {
                        bicmd = CDPath_CMD;
                        isTilde = 1;
                        builtin = 1;
                        strPath = $3;
                        return 0;
                        }
                | CD PERIODPERIOD NEWLINE
                        {
                        bicmd = CDPath_CMD;
                        builtin = 1;
                        strPath = "..";
                        return 0;
                        }
                | CD PERIOD NEWLINE
                        {
                        bicmd = CDPath_CMD;
                        builtin = 1;
                        strPath = ".";
                        return 0;
                        }
                | CD PERIODPERIOD WORD NEWLINE
                        {
                        bicmd = CDPath_CMD;
                        builtin = 1;
                        dotdot = 1;
                        strPath = $3;
                        return 0;
                        }
                | CD PERIOD WORD NEWLINE
                        {
                        bicmd = CDPath_CMD;
                        dotdot = 0;
                        builtin = 1;
                        strPath = $3;
                        return 0;
                        }
                | BYE
                        {
                        bicmd = BYE_CMD;
                        return 0;
                        }
                | NEWLINE
                        {
                        bicmd = NEWLINE_CMD;
                        builtin = 1;
                        return 0;
                        }
                | LS NEWLINE
                        {
                        bicmd = LS_CMD;
                        builtin = 1;
                        return 0;
                        }
                | LS WORD NEWLINE
                        {
                        bicmd = LSWord_CMD;
                        builtin = 1;
                        fileName = $2;
                        return 0;
                        }
                | LS simple.cmd

                | SETENV NEWLINE
                        {
                        bicmd = SETENV_CMD;
                        builtin = 1;
                        argv[0] = NULL;
                        return 0;
                        }
                | SETENV WORD NEWLINE
                        {
                        bicmd = SETENV_CMD;
                        builtin = 1;
                        argv[0] = $2;
                        argv[1] = NULL;
                        return 0;
                        }
                | SETENV WORD PERIOD NEWLINE
                        {
                        bicmd = SETENV_CMD;
                        builtin = 1;
                        isPeriod = 1;
                        argv[0] = $2;
                        argv[1] = NULL;
                        return 0;
                        }
                | SETENV WORD WORD NEWLINE
                        {
                        bicmd = SETENV_CMD;
                        builtin = 1;
                        argv[0] = $2;
                        argv[1] = $3;
                        return 0;
                        }
                | UNSETENV NEWLINE
                        {
                        bicmd = UNSETENV_CMD;
                        builtin = 1;
                        argv[0] = NULL;
                        return 0;
                        }
                | UNSETENV WORD NEWLINE
                        {
                        bicmd = UNSETENV_CMD;
                        builtin = 1;
                        argv[0] = $2;
                        return 0;
                        }
                | PRINTENV NEWLINE
                        {
                        builtin = 1;
                        bicmd = PRINTENV_CMD;
                        return 0;
                        }
                | ALIAS NEWLINE
                        { bicmd = ALIAS_CMD;
                        builtin = 1;
                        return 0;
                        }
                | ALIAS WORD WORD NEWLINE
                        {
                        bicmd = ALIAS_CMD_CREATE;
                        builtin = 1;
                        argv[0] = $2;
                        argv[1] = $3;
                        return 0; }
                | UNALIAS WORD NEWLINE
                        {
                        bicmd = UNALIAS_CMD;
                        builtin = 1;
                        argv[0] = $2;
                        return 0;
                        }
                ;

simple.cmd:      WORD NEWLINE
                        {
                        input_command = $1;
                        argv[0] = $1;
                        argv[1] = NULL;
                        return 0;
                        }
                | WORD WORD NEWLINE
                        {
                        bistr = $1;
                        argv[argc] = $1;
                        argv[++argc] = $2;
                        argv[++argc] = NULL;
                        return 0;
                        }
                | WORD STRING NEWLINE
                        {
                        bistr = $1;
                        argv[argc] = $1;
                        argv[++argc] = $2;
                        argv[++argc] = NULL;
                        return 0;
                        }
                | WORD GT WORD NEWLINE
                        {
                        currcmd = IO_ADDTOFILE;
                        input_command = $1;
                        distf = $3;
                        return 0;
                        }
                | WORD GTGT WORD NEWLINE
                        {
                        currcmd = IO_APPENDTOFILE;
                        input_command = $1;
                        distf = $3;
                        return 0;
                        }
                ;
%%

int yyerror(char *s){
    fprintf(stderr, "*%s*\n", s);
    return 0;
}


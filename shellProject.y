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

 extern int yylex();

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

                | alias.cmd

                ;

builtin.cmd:    TILDE NEWLINE
                        {
                        bicmd = CDHome_CMD;
                        builtin = 1;
                        return 0;
                        }
                | TILDE WORD NEWLINE
                        {
                        bicmd = CDUser_CMD;
                        builtin = 1;
                        userName = $2;
                        return 0;
                        }
                | CD NEWLINE
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
                | LS GT WORD NEWLINE
                        {
                        currcmd = OUTPUT_REDIRECTION;
                        isLSWithWord = 1;
                        input_command = $1;
                        distf = $3;
                        return 0;
                        }
                | LS GTGT WORD NEWLINE
                        {
                        currcmd = OUTPUT_APP;
                        isLSWithWord = 1;
                        input_command = $1;
                        distf = $3;
                        return 0;
                        }
                | LS LT WORD NEWLINE
                        {
                        currcmd = INPUT_REDIRECTION;
                        isLSWithWord = 1;
                        input_command = $1;
                        srcf = $3;
                        return 0;
                        }
                | LS WORD WORD NEWLINE
                        {
                        bicmd = LSWordWord_CMD;
                        builtin = 1;
                        fileName1 = $2;
                        fileName2 = $3;
                        return 0;
                        }
                | ENVEXP NEWLINE
                        {
                        bicmd = ENVEXP_CMD;
                        builtin = 1;
                        envExpVariable = $1;
                        return 0;
                        }
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
                | SETENV WORD PERIOD WORD NEWLINE
                        {
                        printf("\n\nHOLLY SHIT I MADE IT HERE11111\n\n");
                        bicmd = SETENV_CMD;
                        isFrontPeriod = 1;
                        builtin = 1;
                        argv[0] = $2;
                        argv[1] = $4;
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
                  ;

alias.cmd:        ALIAS NEWLINE
                        {
                        bicmd = ALIAS_CMD;
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
                        bicmd = WORD_CMD;
                        argv[0] = $1;
                        argv[1] = NULL;
                        return 0;
                        }
                | WORD WORD NEWLINE
                        {
                        bicmd = WORD_CMD;
                        argv[0] = $1;
                        argv[1] = $2;
                        argv[2] = NULL;
                        return 0;
                        }
                | WORD GT WORD NEWLINE
                        {
                        currcmd = OUTPUT_REDIRECTION;
                        isLSWithWord = 0;
                        input_command = $1;
                        distf = $3;
                        return 0;
                        }
                | WORD GTGT WORD NEWLINE
                        {
                        currcmd = OUTPUT_APP;
                        isLSWithWord = 0;
                        input_command = $1;
                        distf = $3;
                        return 0;
                        }
                | WORD LT WORD NEWLINE
                        {
                        currcmd = INPUT_REDIRECTION;
                        isLSWithWord = 0;
                        input_command = $1;
                        srcf = $3;
                        return 0;
                        }
                | WORD PIPE WORD NEWLINE
                        {
                        currcmd = PIPELINE;
                        input_command = $1;
                        srcf = $3;
                        return 0;
                        }
                ;
%%


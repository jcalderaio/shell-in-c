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
%token <integer> useless.redir other.cmd alias.cmd dir.list cmd.file
%token <word> WORD
%token <string> STRING

%start cmd

%%

cmd:              builtin.cmd
                        { eventcount++; }
                | simple.cmd
                        { eventcount++; }
                | builtin.cmd LT WORD
                        { nuterr("illegal input redirection"); undoit(); bicmd = 0; }
                | builtin.cmd LT STRING
                        { nuterr("illegal input redirection"); undoit(); bicmd = 0; }
                | alias.cmd
                        { eventcount++; }
                | alias.cmd LT WORD
                        { nuterr("illegal input redirection"); undoit(); bicmd = 0; }
                | alias.cmd LT STRING
                        { nuterr("illegal input redirection"); undoit(); bicmd = 0; }
                | other.cmd
                        { eventcount++; builtin = 0; }
                ;


builtin.cmd:      SETENV PATH    dir.list
                        { bicmd = SETPATH; }
                | SETENV PATH
                        { pathleng =0; bicmd = SETPATH; }
                | SETENV PROMPT STRING
                        { bicmd = SETPROMPT; bistr = mkstr($3); }
                | SETENV
                        { bicmd = SETT; }
                | SETENV GT WORD
                        { bicmd = SETT; bioutf = 1; bistr = mkstr($3); }
                | SETENV GT STRING
                        { bicmd = SETT; bioutf = 1; bistr = mkstr($3); }
                | SETENV GT GT WORD
                        { bicmd = SETT; bioutf = 1; bistr = mkstr($3); append = 1; }
                | SETENV GT GT STRING
                        { bicmd = SETT; bioutf = 1; bistr = mkstr($3); append = 1; }
                | CD WORD
                        { bicmd = CDX; bistr = mkstr($2); }
                | CD STRING
                        { bicmd = CD; bistr = mkstr($2); }
                | BYE
                        { bicmd = BYE; return 0; }
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

int main(void){
    yyparse();
    return 0;
}

int yyerror(char *s){
    fprintf(stderr, "*%s*\n", s);
    return 0;
}

int yywrap(){
    return 1;
}
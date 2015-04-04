%{
#include <stdio.h>
#include <string.h>
#include "shellProject.h"

/*-------------------------------------------------------------------------------------
 * shellProject.y - yacc specification file for the parser generator
 *------------------------------------------------------------------------------------
 */
int eventcount = 0;
void yyerror(const char *str){
    fprintf(stderr, "error: %s\n", str);
}
int yywrap(){
    return 1;
}
 /* parse local working data section */
 COMMAND *q, *p;
 int pfd[2];

%}

%union{
    int i;
    char *s;
    char *w;
}

%token <i> LT GT AMP LPAREN VBAR DOT DEBUG
%token <i> SET PATH PROMPT CD BYE ALIAS UNALIAS PWD EXTEND
%token <i> ALIASLOOP
%token <w> WORD
%token <s> STRING

%type <w> cmd.file

%start cmd

%%

cmd:           builtin.cmd
                 { eventcount++; }
               | simple.cmd
                 { eventcount++; }
               | builtin.cmd LT WORD
                 { nuterr("illegal input redirection");
                   undoit(); bicmd = 0; }
               | builtin.cmd LT STRING
                 { nuterr("illegal input redirection");
                   undoit(); bicmd = 0; }
               | alias.cmd
                 { eventcount++; }
               | alias.cmd LT WORD
                 { nuterr("illegal input redirection");
                   undoit(); bicmd = 0; }
               | alias.cmd LT STRING
                 { nuterr("illegal input redirection");
                   undoit(); bicmd = 0; }
               | other.cmd { eventcount++; builtin = 0; }
               ;


builtin.cmd     SETENV PATH    dir.list    useless.redir
                        { bicmd = SETPATH; }
                | SETENV PATH
                        { pathleng =0; bicmd = SETPATH; }
                | SETENV PROMPT STRING
                        { bicmd = SETPROMPT; bistr = mkstr($3); }
                        useless.redir
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
                | CD WORD useless.redir
                        { bicmd = CDX; bistr = mkstr($2); }
                | CD STRING useless.redir
                | BYE
                        { bicmd = byeCMD; return 0; }
                | NEWLINE
                        { bicmd = newlineCMD; return 0;}
                ;

simple.cmd:     exec.cmd


exec.cmd        WORD{
                        input_command = $1;
                        argv[0] = $1;
                        argv[1] = NULL;
                        return 0;
                }
%%
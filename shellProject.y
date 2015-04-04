%{
#include <stdio.h>
#include <string.h>
#include "global.h"
#include "shellProject.h"

/*-------------------------------------------------------------------------------------
 * shellProject.y - yacc specification file for he parser generator
 *------------------------------------------------------------------------------------
 */

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

builtin.cmd     SET PATH    dir.list    useless.redir
                        { bicmd = SETPATH; }
                | SET PATH
                        { pathleng =0; bicmd = SETPATH; }
                | SET PROMPT STRING
                        { bicmd = SETPROMPT; bistr = mkstr($3); }
                        useless.redir
                | SET
                        { bicmd = SETT; }
                | SET GT WORD
                        { bicmd = SETT; bioutf = 1; bistr = mkstr($3); }
                | SET GT STRING
                        { bicmd = SETT; bioutf = 1; bistr = mkstr($3); }
                | SET GT GT WORD
                        { bicmd = SETT; bioutf = 1; bistr = mkstr($3); append = 1; }
                | SET GT GT STRING
                        { bicmd = SETT; bioutf = 1; bistr = mkstr($3); append = 1; }
                | CD WORD useless.redir
                        { bicmd = CDX; bistr = mkstr($2); }
                | CD STRING useless.redir


/*-------------------------------------------------------------------------------------
 * Need to add code in here
 *------------------------------------------------------------------------------------
 */

simple.cmd:         cmd.file
                        {
                            comtab[currcmd].comname = mkstr($1);
                            comtab[currcmd].atptr = NIL(ARGTAB);
                            comtab[currcmd].narg = 0;
                            /* first arg is reversed for command */
                        }
                    | cmd.file  arguments
                        {
                            comtab[currcmd].comname = mkstr($1);
                            comtab[currcmd].narg = currarg;
                            /* first arg is reversed for command */
                        }
                    ;


cmd.file:           WORD
                        {
                            (p = &comtab[currcmd])->atptr = Allocate(ARGTAB);
                            currarg = 1; /* 1st arg is reversed for the comm.  */
                            p->atptr->args[currarg++] = mkstr($1);
                        }
                    | STRING
                        {
                            (p = &comtab[currcmd])->atptr = Allocate(ARGTAB);
                            currarg = 1; /* 1st arg is reversed for the comm.  */
                            p->atptr->args[currarg++] = mkstr($1);
                        }
                    | arguments WORD
                        {
                            p->atptr->args[currarg++] = mkstr($2);
                        }
                    | arguments STRING
                        {
                            p->atptr->args[currarg++] = mkstr($2);
                        }
                    ;


input:              LT WORD
                        {
                            strcopy( srcf, $2 );
                            comtab[0].infd = BADFD;
                        }
                    ;


ouput:              GT WORD
                        {
                            strcopy( distf, $2 );
                            comtab[currcmd-1].outfd = BADFD;
                        }
                    | GT GT WORD
                        {
                            strcopy( distf, $3 );
                            comtab[currcmd-1].outfd = BADFD;
                            append = 1;
                        }
                    ;

words:              WORD WORD
                    | words WORD
                    ;




/*-------------------------------------------------------------------------------------
 * Need to add code in here
 *------------------------------------------------------------------------------------
 */



%%


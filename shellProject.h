#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXCMDS              50
#define MAXARGS              300
#define MAXALIAS             100
#define MAXCACHE             100
#define MAXPATH              50

#define OK                   0
#define ERRORS               1
#define SYSERR               1
#define OLD_ERR              3
#define SYSCALLER           -1

#define BADFD               -2
#define EOFILE               2

#define THE_ONLY_ONE         1
#define FIRST                2
#define LAST                 3

#define REGISTRY "REGISTRY"

#define BYE_CMD                  2
#define CDHome_CMD               3
#define CDPath_CMD               4
#define ALIAS_CMD                5
#define UNALIAS_CMD              6
#define SETENV_CMD               7
#define UNSETENV_CMD             8
#define PRINTENV_CMD             9
#define NEWLINE_CMD              10

///////*Command line arguments structure*//////
typedef struct comrgs{
    char *args[MAXARGS];
} ARGTAB;

//////*Command line structure*////////
typedef struct com{
    char *comname;
    int remote;
    int infd;
    int outfd;
    int nargs;
    ARGTAB *atptr;

} COMMAND;

/////////*Alias structure*//////////
struct alias{
    int used;
    char *alname;
    char *alstr;
};

struct env {
    int used; //number of usage times?
    char *envname; //pointer to alias name?
    char *envstr;  //pointer to alias string?
};

typedef struct cache{
    char *cmd;
    char *hostport;
} CACHE;

///////*Externals*/////////////

extern struct alias aliastab[];
extern COMMAND camtab[];
extern CACHE cachetab[];
extern char *pathtab[];
extern int currcmd;
extern int currcache;
extern int lastcurrcmd;
extern int recursive;
extern int pathleng;
extern int currarg;
extern int login;
extern int builtin = 0;
extern int bicmd = 0;
extern int bioutf = 0;
extern char *bistr = "";
extern char *bistr2;
extern int debug;
extern int IwasSet;
extern int err;
extern int error_somewhere;
extern int ap;
extern int cmd_has_tail;
extern int backgnd;
extern int concurrp;
extern int eventcount;
extern char home[] = {0};
extern char *shname;
extern char *prompt_string;
extern int user_defined_prompt;
extern char srcf[];
extern char distf[];
extern int append = 0;
extern int loop;

////////////////////////////////

extern int SETPATH = 0;
extern int SETT = 0;
extern int CDX = 0;
extern int MAXENV = 0;
extern int SETPROMPT = 0;
extern int CMD = 0;
extern int yylex();
extern int yyparse();
extern int currcmd = 0;
extern char* pathtab[MAXPATH] = {0};
extern char* command_path;
extern int argc = 0;
extern char* argv[MAXARGS] = {0};
extern char* executable_path = "";
extern int yylineno;
extern char* yytext;
extern char* input_command = "";

////////////////////////////////////

#define NIL(x) (x *)0
#define ALL NIL(char)
#define copystring (a,b) strcpy((a=(char *)malloc(strlen(b)+1)), b)
#define mkstr(a) (char *)makestring(a)
#define allocate(t) (t *)malloc(sizeof(t))


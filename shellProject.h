#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define FALSE 0
#define TRUE !FALSE

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
#define LS_CMD                   11
#define LSWord_CMD               12
#define ALIAS_CMD_CREATE         13

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

struct AliasNode {
        struct AliasNode* next;
        char* key;
        char* value;
};

struct AliasNode* aliasHead;
struct AliasNode* aliasHead1;
struct AliasNode* aliasHead2;
struct AliasNode* aliasHead3;
struct AliasNode* aliasHead4;
struct AliasNode* aliasHead5;
struct AliasNode* dec;

///////*Externals*/////////////

struct alias aliastab[];
COMMAND camtab[];
CACHE cachetab[];
char *pathtab[];
int currcmd;
int currcache;
int lastcurrcmd;
int recursive;
int pathleng;
int currarg;
int login;
int builtin;
int bicmd;
int bioutf;
char *bistr;
char *bistr2;
int debug;
int IwasSet;
int err;
int error_somewhere;
int ap;
int cmd_has_tail;
int backgnd;
int concurrp;
int eventcount;
char *home;
char *shname;
char *prompt_string;
int user_defined_prompt;
char srcf[];
char distf[];
int append;
int loop;

////////////////////////////////

int SETPATH;
int SETT;
int CDX;
int MAXENV;
int SETPROMPT;
int CMD;
int yylex();
int yyparse();
int currcmd;
char* pathtab[MAXPATH];
char* command_path;
int argc;
char* argv[MAXARGS];
char* executable_path;
int yylineno;
char* yytext;
char* input_command;
int isExe;
char* currentLocation;
char currLoc[MAXPATH];
char* strPath;
int alphasort(); //Inbuilt sorting function
char* pathname[MAXPATH];
char* currentWorkDir;
char* fileName;
char* var;
char* value;
char* word1;
char* word2;

char* word5;
char* al;
char* alWord;


////////////////////////////////////

#define NIL(x) (x *)0
#define ALL NIL(char)
#define copystring (a,b) strcpy((a=(char *)malloc(strlen(b)+1)), b)
#define mkstr(a) (char *)makestring(a)
#define allocate(t) (t *)malloc(sizeof(t))


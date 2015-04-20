

//#include "lex.yy.c"
/*Boolean Definitions*/

#define FALSE 0
#define TRUE !FALSE
/*Size Definitions*/
#define MAXCMDS              50
#define MAXARGS              300
#define MAXALIAS             100
#define MAXCACHE             100
#define MAXPATH              50
/*Error Definitions*/
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

//------Builtin Commands-----------//
/*Assigning bicmd Different Numbers*/
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
#define CDUser_CMD               14
#define LSWordWord_CMD           15
#define WORD_CMD                 16
#define ENVEXP_CMD               17

//------Simple Commands-----------//
/*Assigning Simple Commands Different Numbers*/
#define IO_ADDTOFILE             1
#define IO_APPENDTOFILE          2

#define yyconst const


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
/*Environment Structure*/
struct env {
    int used; //number of usage times?
    char *envname; //pointer to alias name?
    char *envstr;  //pointer to alias string?
};
/*Cache Table Structure*/
typedef struct cache{
    char *cmd;
    char *hostport;
} CACHE;
/*Alias Structure*/
struct AliasNode {
        int nested;
        char* key;
        char* value;
};

///////*Externals*/////////////

struct AliasNode aliasTable[MAXALIAS]; //Table of all aliases
int alias_count;                       //Number of aliases
COMMAND comtab[MAXCMDS];               //Table of all commands
CACHE cachetab[MAXCACHE];              //Table of all cache
int currcmd;                           //Number of the current command
int currcache;                         //Number of the current cache
int lastcurrcmd;                       //Number of the last command
int recursive;                         //it's just a variable
int pathleng;                          //Path length
int currarg;                           //Current argument
int login;                             //Login number
int builtin;                           //Used for builtin commands
int bicmd;                             //Used for builtin commands to get executed
int bioutf;                            //out file for builtin
char *bistr;                           //String pointer for the builtin commands
char *bistr2;                          //builtin pointer2
int debug;                             //for debugging 
int IwasSet;                           //something was set 
int err;                               //error 
int error_somewhere;                   //if error is somewhere
int ap;                                //just a variable 
int cmd_has_tail;                      //used for the commands having tail 
int backgnd;                           //used for background
int concurrp;                          //for concurrent process
int eventcount;                        //counts the number of events
char *home;                            //home 
char *shname;                          //for shell name 
char *prompt_string;                   //string prompt 
int user_defined_prompt;               //user defined prompt 
int append;                            //for appending anything 
int loop;                              //used as a loop integer 

////////////////////////////////

int SETPATH;                           //set the path
int SETT;                              //used somewhere 
int CDX;                               //used somewhere
int MAXENV;                            //maximum no of environment 
int SETPROMPT;                         //setting the prompt
int CMD;                               //for taking the command 
char* pathtab[MAXPATH];                //used in executable 
char* command_path;                    //used for command path 
int argc;                              //number of arguments 
char* argv[MAXARGS];                   //array of arguments 
char* executable_path;                 //for executable path 
char* input_command;                   //for input command 
int isExe;                             //used somewhere 
char* currentLocation;                 //for current location 
char currLoc[MAXPATH];                 //for current location path 
char* strPath;                         //for string path 
int alphasort();                       //Inbuilt sorting function
char* pathname[MAXPATH];               //for path name 
char* currentWorkDir;                  //for current working directory 
char* fileName;                        //for filename     
char* var;                             //just a variable 
char* value;                           //used in aliasing 
int isQuote;                           //used in init_scanner_and_parser
char* strPathConCat;                   //string path concatenation
int dotdot;                            //used for CD ..
char* srcf;                            //used as source file 
char* distf;                           //used as destination file 
int isPeriod;                          //used in set environment 
int isInFile;                          //input file 
int isOutFile;                         //output file 
char* wcFound;                         //wildcard found 
char* userName;                        //username     
int isLSWithWord;                      //list with word         
char* fileName1;                       //used as filename for WildCard Matching
char* fileName2;                       //used as filename for WildCard Matching
char* envExpVariable;                  //environment expansion variable     
int isWild;                            //for checking wildcard 
int isTilde;                           //for checking tilde 
int isFrontPeriod;                     //used in set environment 

////////////////////////////////////


/*For I/O Redirection and Pipelining!!!!*/
#define INPUT_STRING_SIZE   80
#define NORMAL              0
#define OUTPUT_REDIRECTION  1
#define INPUT_REDIRECTION   2
#define PIPELINE            3
#define BACKGROUND          4
#define OUTPUT_APP          5
int myPipe[2];


#define NIL(x) (x *)0
#define ALL NIL(char)
#define copystring (a,b) strcpy((a=(char *)malloc(strlen(b)+1)), b)  //copying definition is allocating the memory space of actual string
#define mkstr(a) (char *)makestring(a)         //definining mkstr as a char* to makestring
#define allocate(t) (t *)malloc(sizeof(t))     //allocate memory of size t


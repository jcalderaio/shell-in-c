#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>


#include "shellProject.h"

//////////////////////////////////////////////////////
///////Builtin Functions//////////////////////////////
//////////////////////////////////////////////////////

extern char **environ;

extern int yyparse();
//extern void reset_lexer(void);
//extern void reset_parser(void);
extern int yylex_destroy();
typedef struct yy_buffer_state * YY_BUFFER_STATE;
//extern struct YY_BUFFER_STATE;
extern void yy_switch_to_buffer ( YY_BUFFER_STATE  );
extern YY_BUFFER_STATE yy_scan_string(char * str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern YY_BUFFER_STATE yy_scan_buffer(char *);




bool is_alias(char *key) {

    struct AliasNode currAlias;
    int index = 0;
    while(alias_count > index){
        if(!strcmp(aliasTable[index].key, key)){
            currAlias = aliasTable[index];
            return true;
        }
        ++index;
    }
    return false;
}

char * get_alias(char *key) {

    struct AliasNode currAlias;
    int flag = 0;
    int index = 0;
    while(alias_count > index){
        if(!strcmp(aliasTable[index].key, key)){
            currAlias = aliasTable[index];
            ++flag;
            break;
        }
        ++index;
    }

    if(flag == 0) {
        return key;
    }

    if(currAlias.nested != -1) { //there is a nested command

        while(currAlias.nested != -1){
            currAlias = aliasTable[currAlias.nested];
        }
    }

    return currAlias.value;

    // char* argument_future = argv[1];
    // char* string = malloc(strlen(currAlias.value));
    // strcpy(string, currAlias.value);
    // char* drf;
    // char* token = strtok_r(string, " ", &drf);
    // int i = 0;
    // while (token != NULL){
    //     argv[i] = token;
    //     ++i;
    //     token = strtok_r(NULL, " ", &drf);
    // }
    // if(argument_future == NULL)
    //     argv[i] = NULL;
    // else{
    //     argv[i] = argument_future;
    //     argv[++i] = NULL;
    // }
    // memset(input_command,0,strlen(input_command));
    // input_command = argv[0];
    // return;
}

bool wCard(char* first, char* second){
    if(*first == '\0' && *second == '\0'){
        return true;
    }
    if(*first == '*' && *(first+1) != '\0' && *second == '\0'){
        return false;
    }
    if(*first == '?' || *first == *second){
        return wCard(first+1, second+1);
    }
    if(*first == '*'){
        return wCard(first+1, second) || wCard(first, second+1);
    }
    return false;
}

void wTest(char* str){
    DIR *dirp;
    char* second;
    struct dirent* dir;
    dirp = opendir(currentWorkDir);
    if(dirp){
        while((dir = readdir(dirp)) != NULL){
            second = dir->d_name;
            if(wCard(str, second)){
                wcFound = second;
                break;
            }
        }
        closedir(dirp);
    }
}

void wTestNewNew(){
    printf("\n\nWe Are Here...\n\n");
    DIR *dirp;
    char* second;
    struct dirent* dir;
    dirp = opendir(currentWorkDir);
    if(dirp){
        while((dir = readdir(dirp)) != NULL){
            second = dir->d_name;
            if(wCard(fileName2, second)){
                printf("\n\nSecond Directory name is:%s\n\n",second);
                wcFound = second;
                break;
            }
        }
        closedir(dirp);
    }
}

void wTestNew(){
    DIR *dirp;
    char* second;
    struct dirent* dir;
    dirp = opendir(currentWorkDir);
    if(dirp){
        while((dir = readdir(dirp)) != NULL){
            second = dir->d_name;
            if(wCard(fileName1, second)){
                printf("\n\nDirectory name is:%s\n\n",second);
                wcFound = second;
                break;
            }
        }
        closedir(dirp);
    }
    wTestNewNew();
}



//For I/O Redirection and Pipelining functioning
void chop(char *srcPtr)
{
    while(*srcPtr != ' ' && *srcPtr != '\t' && *srcPtr != '\n')
    {
        srcPtr++;
    }
    *srcPtr = '\0';
}


//End of I/O Redirection and Pipelining functioning
void removeSpaces (char *str) {
    // Set up two pointers.
    char *src = str;
    char *dst = src;
    // Process all characters to end of string.
    while (*src != '\0') {
        // If it's not a space, transfer and increment destination.
        if (*src != ' ')
            *dst++ = *src;
        // Increment source no matter what.
        src++;
    }
    // Terminate the new string.
    *dst = '\0';
}

char * remove_white(char * source) {
    while(isspace(*source)){ //removing preceeding 0 from the input
        ++source;
    }
    return source;
}

void getCurrentPath(){
    char * cwd;
    cwd = getcwd (0, 0);
    if (! cwd) {
        fprintf (stderr, "getcwd failed: %s\n", strerror (errno));
    }
    else {
        currentWorkDir = cwd;
        removeSpaces(currentWorkDir);
        free(cwd);
    }
}

void goHome(){
    strcpy(currLoc, home);
    printf("You are now being redirected to the home directory\n");
    chdir(home);
}

void goPath(){
    strPath = get_alias(strPath);
    if(isTilde == 1){
            getCurrentPath();
            strcpy(currLoc, home);
            if(!(strPath[0] == '/')){
                strcat(currLoc, "/");
            }
            strcat(currLoc, strPath);
            currentWorkDir = currLoc;
            removeSpaces(currentWorkDir);
            int isDir = chdir(currentWorkDir);
            if(isDir){
                printf("%s is not a valid directory name.\n", strPath);
            }
            isTilde = 0;
        }
        else{
            if(dotdot == 1){
                getCurrentPath();
                strcpy(currLoc, currentWorkDir);
                if(!(strPath[0] == '/')){
                    strcat(currLoc, "/");
                }
                strcat(currLoc, "..");
                currentWorkDir = currLoc;
                removeSpaces(currentWorkDir);
                int isDir = chdir(currentWorkDir);
                if(isDir){
                    printf("%s is not a valid directory name.\n", strPath);
                }

                getCurrentPath();
                strcpy(currLoc, currentWorkDir);
                if(!(strPath[0] == '/')){
                    strcat(currLoc, "/");
                }
                strcat(currLoc, strPath);
                currentWorkDir = currLoc;
                removeSpaces(currentWorkDir);
                isDir = chdir(currentWorkDir);
                if(isDir){
                    printf("%s is not a valid directory name.\n", strPath);
                }

                dotdot = 0;
            }
            else{
                getCurrentPath();
                strcpy(currLoc, currentWorkDir);
                if(!(strPath[0] == '/')){
                    strcat(currLoc, "/");
                }
                strcat(currLoc, strPath);
                currentWorkDir = currLoc;
                removeSpaces(currentWorkDir);
                int isDir = chdir(currentWorkDir);
                if(isDir){
                    printf("%s is not a valid directory name.\n", strPath);
                }
            }
        }

        strPath = "";
}

void printEnvironment() {
    int i;
    for(i = 0; environ[i] != NULL; ++i) {
        printf("%s\n",environ[i]);
    }
}

void setEnvironment() {
    if(!isPeriod){
        if(argv[0] == NULL) {
            printEnvironment();
        }
        else if(argv[1] == NULL) {
            char* string_1 = remove_white(argv[0]);
            string_1 = get_alias(string_1);
            setenv(string_1, "", 0);
            printf("\"%s\" added to environment variables!\n", string_1);
        }
        else {
            char* string_1 = remove_white(argv[0]);
            string_1 = get_alias(string_1);
            setenv(string_1, get_alias(remove_white(argv[1])), 0);
            printf("\"%s\" added to environment variables!\n", string_1);
        }
    }
    else{
        if(argv[0] == NULL) {
            printEnvironment();
        }
        else {
            getCurrentPath();
            char* string_1 = get_alias(remove_white(argv[0]));
            setenv(string_1, remove_white(currentWorkDir), 0);
            printf("\"%s\" added to environment variables!\n", string_1);
            isPeriod = 0;
        }
    }
}

void unsetEnvironment() {
    if(argv[0] == NULL) {
        printf("%s\n", "unsetenv: you didn't include anything to unset!");
    }
    else if(getenv(remove_white(argv[0])) == NULL) {
        printf("%s\n", "unsetenv: environment variable not found!");
    }
    else {
        char* string_1 = get_alias(remove_white(argv[0]));
        unsetenv(string_1);
        printf("\"%s\" removed from environment variables!\n", string_1);
    }
}

void printAlias() {

    if(alias_count == 0) {
        printf("No aliases!\n");
        return;
    }
    int count = 0;
    while(count < alias_count){
        printf("%s:%s\n", aliasTable[count].key, aliasTable[count].value);
        ++count;
    }
}

void createAlias(char* key, char* value){

    int count = 0;
    //If max alias count reached
    if(alias_count == MAXALIAS) {
        printf("Max number of aliases created!\n");
        return;
    }

    //If no aliases created yet
    if(alias_count == 0){
        aliasTable[0].key = key;
        aliasTable[0].value = value;
        aliasTable[0].nested = -1;
        ++alias_count;
        printf("\"%s\" added as an alias!\n", key);
        return;
    }

    while(count < alias_count){
        if(!strcmp(aliasTable[count].key, key)){
            printf("\"%s\" is already an alias!\n", key);
            return;
        }
        ++count;
    }

    aliasTable[alias_count].key = key;
    aliasTable[alias_count].value = value;
    aliasTable[alias_count].nested = -1;

    printf("\"%s\" added as an alias!\n", key);

    int count2 = 0;
    while(count2 < alias_count){
        if(!strcmp(aliasTable[count2].value, key)) {
            aliasTable[count2].nested = alias_count;
        }
        ++count2;
    }
     ++alias_count;
    return;
}

void unaliasword(char* key){

    int count = 0;
    if(alias_count != 0) {

        while(alias_count > count){
            if(!strcmp(key, aliasTable[count].key)){
                int i = 0;
                while(i < count){
                    if(strcmp(key, aliasTable[i].value) == 0)
                        aliasTable[i].nested = -1;
                    ++i;
                }
                break;
            }
            ++count;
        }

        int count2 = count + 1;
        while(alias_count -1 > count)
        {
            aliasTable[count] = aliasTable[count2];
            int i = 0;
            while(count > i){
                if (!strcmp(aliasTable[i].value, aliasTable[count].key))
                    aliasTable[i].nested = count;
                ++i;
            }
            ++count;
            ++count2;
        }
        --alias_count;
        printf("\"%s\" alias removed!\n", key);
        return;
    }

    else {
        printf("No aliases to remove\n");
        return;
    }

}

void goLS(){
    DIR *dirp;
    struct dirent* dir;
    dirp = opendir(currentWorkDir);
    if(dirp){
        while((dir = readdir(dirp)) != NULL){
            printf("%s\n", dir->d_name);
        }
        closedir(dirp);
    }
}

void goLSWord(){
    fileName = get_alias(fileName);
    if(isWild == 1){
        wTest(fileName);
        if(wcFound != ""){
            removeSpaces(wcFound);
            fileName = wcFound;
            wcFound = "";
        }
    }
    if(isTilde == 1){
        goHome();
        fileName = fileName + 1;
    }
    if(fileName[0] == '/'){
        fileName = fileName + 1;
    }
    DIR *dirp;
    struct dirent *dir;
    getCurrentPath();
    dirp = opendir(currentWorkDir);
    int flag = 0;
    if (dirp){
        while ((dir = readdir(dirp)) != NULL){
            if(strcmp(fileName, dir->d_name) == 0){
                flag = 1;
                DIR *d2;
                struct dirent *dir2;
                d2 = opendir(dir->d_name);
                if (d2){
                    while ((dir2 = readdir(d2)) != NULL){
                        printf("%s\n", dir2->d_name);
                    }
                    closedir(d2);
                }
            }
        }
        closedir(dirp);
        if(flag == 0)
            printf("Directory %s does not exist.\n", fileName);
    }
}

void goLSWordWord(){

    if(isWild == 1){
        wTest(fileName1);
        if(wcFound != ""){
            removeSpaces(wcFound);
            fileName1 = wcFound;
            wcFound = "";
        }

        wTest(fileName2);
        if(wcFound != ""){
            removeSpaces(wcFound);
            fileName2 = wcFound;
            wcFound = "";
        }
    }
    if(isTilde == 1){
        goHome();
        fileName1 = fileName1 + 1;
    }
    if(fileName1[0] == '/'){
        fileName1 = fileName1 + 1;
    }
    DIR *dirp;
    struct dirent *dir;
    getCurrentPath();
    dirp = opendir(currentWorkDir);
    int flag = 0;
    if (dirp){
        while ((dir = readdir(dirp)) != NULL){
            if(strcmp(fileName1, dir->d_name) == 0){
                flag = 1;
                DIR *d2;
                struct dirent *dir2;
                d2 = opendir(dir->d_name);
                if (d2){
                    printf("%s:\n\n", fileName1);
                    while ((dir2 = readdir(d2)) != NULL){
                        printf("%s\n", dir2->d_name);
                    }
                    closedir(d2);
                }
            }
        }
        closedir(dirp);
        if(flag == 0)
            printf("Directory %s does not exist.\n", fileName1);

        printf("\n\n");
    }

    //The second file name
    fileName2 = get_alias(fileName2);

    if(isTilde == 1){
        goHome();
        fileName2 = fileName2 + 1;
    }
    if(fileName2[0] == '/'){
        fileName2 = fileName2 + 1;
    }

    getCurrentPath();
    dirp = opendir(currentWorkDir);
    flag = 0;
    if (dirp){
        while ((dir = readdir(dirp)) != NULL){
            if(strcmp(fileName2, dir->d_name) == 0){
                flag = 1;
                DIR *d2;
                struct dirent *dir2;
                d2 = opendir(dir->d_name);
                if (d2){
                    printf("%s:\n\n", fileName2);
                    while ((dir2 = readdir(d2)) != NULL){
                        printf("%s\n", dir2->d_name);
                    }
                    closedir(d2);
                }
            }
        }
        closedir(dirp);
        if(flag == 0)
            printf("Directory %s does not exist.\n", fileName2);
    }
}

void envExpansion(){

    printf("%s\n", getenv(envExpVariable));
}

void in_redir(){

}

void out_redir(){

}

///////////////////////////////////////////////////////
///////Error Handling//////////////////////////////////
///////////////////////////////////////////////////////

void understand_errors(){
    printf("\nAn error occured while parsing the yacc file.\n");
}

void recover_from_errors(){
    // Find out if error occurs in middle of command
    // That is, the command still has a “tail”
    // In this case you have to recover by “eating”
    // the rest of the command.
    // To do this: use yylex() directly.
    printf("\nCommand Error!!!\n");
              // yyscan_t scanner;
              // yylex_init ( &scanner );
              // yylex ( scanner );
              // yylex_destroy ( scanner );
}

///////////////////////////////////////////////////////
///////Shell Functions/////////////////////////////////
///////////////////////////////////////////////////////

int check_in_file(){
    isInFile = open(srcf, O_RDONLY, 0600);
    if( isInFile == -1){
        return SYSERR;
    }
    else{
        return OK;
    }
}

int check_out_file(){
    isOutFile = open(distf, O_WRONLY, O_APPEND, O_RDWR, O_CREAT, 0644);
    if(isOutFile == -1){
        return SYSERR;
    }
    else{
        return OK;
    }
}

void init_scanner_and_parser(){
    // Need to initialize all the variables
    argc = 0;
    bicmd = 0;
    builtin = 0;
    isTilde = -1;
    isQuote = -1;
    wcFound = "";
}

void printPrompt(){
    getCurrentPath();
    printf("%s", currentWorkDir);
    printf(" || SHELL---->$");
    return;
}

void shell_init(){
    //init all variables
    currcmd = 0;
    //define (allocate storage) for some var/tables
    //struct alias aliastab[MAXALIAS];
    struct env envtab[MAXENV];

    //init all tables (e.g., alias table)
    //get PATH environment variable (use getenv())
    char *currPath = getenv("PATH");
    char *homePath = getenv("HOME");

    char* dlim = ":";
    char* tok = strtok(currPath, dlim);

    int i = 0;
    while(tok != NULL){
        pathtab[i] = tok;
        ++i;
        tok = strtok(NULL, dlim);
    }
    pathtab[i] = NULL;
    alias_count = 0;
    //printf("two: %d\n", strlen(pathtab));
    //get HOME env variable (also use getenv())

    //printf("%s", home);
    home = homePath;
    currentLocation = home;
    //disable anything that can kill your shell
    //(the shell should never die; only can be exit)
    //do anything you feel should be done as init
    signal(SIGINT, SIG_IGN);
    return;

    // init all variables.
    // define (allocate storage) for some var/tables
    // init all tables (e.g., alias table)

    //Dont require
    // get PATH environment variable (use getenv())
    // get HOME env variable (also use getenv())

    // disable anything that can kill your shell.
    // (the shell should never die; only can be exit)
    // do anything you feel should be done as init
}

void do_it(){

    switch (bicmd) {
        case CDHome_CMD:
            goHome();
            break;
        case CDPath_CMD:
            goPath();
            break;
        case LS_CMD:
            goLS();
            break;
        case LSWord_CMD:
            goLSWord();
            break;
        case LSWordWord_CMD:
            goLSWordWord();
            break;
        case ALIAS_CMD:
            printAlias();
            break;
        case ALIAS_CMD_CREATE:
            createAlias(remove_white(argv[0]),remove_white(argv[1]));
            break;
        case UNALIAS_CMD:
            unaliasword(remove_white(argv[0]));
            break;
        case ENVEXP_CMD:
            envExpansion();
            break;
        case SETENV_CMD:
            setEnvironment();
            break;
        case UNSETENV_CMD:
            unsetEnvironment();
            break;
        case PRINTENV_CMD:
            printEnvironment();
            break;
        case NEWLINE_CMD:
            break;
        default:
            break;
    }
}

int executable(){
    int i = 0;
    for(i = 0; pathtab[i] != NULL; ++i){
        int length = strlen(pathtab[i]) + strlen(input_command) + strlen("/");
        executable_path = malloc(length);
        strcpy(executable_path, pathtab[i]);
        strcat(executable_path, "/");
        strcat(executable_path, input_command);
        int retVal = access(executable_path, X_OK);
        if(retVal == 0) {
            printf("return ok\n");
            return OK;
        }
    }
    printf("return error\n");
    return ERRORS;

}

int getCommand();
void processCommand();

void reprocess() {

    int length = 0;
    while(argv[length] != NULL) {
        ++length;
    }

    char * new_command = argv[0];

    if(length == 1) {
        //strcat(new_command, "");
    }
    else {
        strcat(new_command, " ");
        int i = 1;
        while(argv[i] != NULL){
            strcat(new_command, argv[i]);
            if(i == (length-1) ) {
                //strcat(new_command, "");
            }
            else {
                strcat(new_command, " ");
            }
            ++i;
        }
    }
    
    const char * const_cmd = new_command;
    
        // yy_scan_string(new_new_command);
        // char* reserve;
        // printf("alias print bitch\n");
        // //char * whatever = strtok_r(new_command, " ", &reserve);
        // yy_scan_string("cd ");
        // yyparse();
        // yylex_destroy();
        
        printf("%s\n", const_cmd);
        YY_BUFFER_STATE bp;
        bp = yy_scan_string(new_command);
        yy_switch_to_buffer( bp );
        getCommand();
        processCommand();
        yy_delete_buffer(bp);
        yylex_destroy();




}

void execute_it(){
    // Handle  command execution, pipelining, i/o redirection, and background processing.
    // Utilize a command table whose components are plugged in during parsing by yacc.

    //Handle Aliases
    int flag = 0;
    int i = 0;
    while(argv[i] != NULL) {
        if(is_alias(argv[i])) {
            argv[i] = get_alias(argv[i]);
            ++flag;
        }
        ++i;
    }

    if(flag != 0) {
        reprocess();
        return;
    }





    // //  * Check io file existence in case of io-redirection.
    // if( check_in_file() == SYSERR ) {
    //     printf("Error reading from : %s", srcf);
    //     return;
    // }
    // if( check_out_file() == SYSERR ) {
    //     printf("Error writing to : %s", distf);
    //     return;
    // }



    pid_t pid, pid2;
    FILE *fp;
    int mode2 = NORMAL, cmdArgc, status1, status2;
    char *cmdArgv2[INPUT_STRING_SIZE], *supplement2 = NULL;
    if(currcmd == PIPELINE){
        if(pipe(myPipe)){
            fprintf(stderr, "Pipe failed!");
            exit(-1);
        }
    }
    pid = fork();
    if( pid < 0){
        printf("Error occured");
        exit(-1);
    }
    else if(pid == 0){
        switch(currcmd)
        {
            case OUTPUT_REDIRECTION:
                fp = fopen(distf, "w+");
                dup2(fileno(fp), 1);
                if(isLSWithWord == 1){
                    goLS();
                }
                else{
                    printf("%s", input_command);
                }
                break;
            case OUTPUT_APP:
                fp = fopen(distf, "a");
                dup2(fileno(fp), 1);
                if(isLSWithWord == 1){
                    goLS();
                }
                else{
                    printf("%s", input_command);
                    printf("\n\n");
                }
                break;
            case INPUT_REDIRECTION:
                printf("\n\nWe are in the INPUT_REDIRECTION\n\n");
                fp = fopen(srcf, "r");
                dup2(fileno(fp), 0);
                if(isLSWithWord == 1){
                    goLS();
                }
                else{
                    printf("%s", input_command);
                    printf("\n\n");
                }
                break;
            case PIPELINE:
                close(myPipe[0]);       //close input of pipe
                dup2(myPipe[1], fileno(stdout));
                close(myPipe[1]);
                break;
        }
        execvp(input_command, input_command);
        exit(0);
    }
    else{
        if(currcmd == BACKGROUND)
            ;
        else if(currcmd == PIPELINE){
            waitpid(pid, &status1, 0);      //wait for process 1 to finish
            pid2 = fork();
            if(pid2 < 0){
                printf("error in forking");
                exit(-1);
            }
            else if(pid2 == 0){
                close(myPipe[1]);       //close output to pipe
                dup2(myPipe[0], fileno(stdin));
                close(myPipe[0]);
                execvp(*cmdArgv2, cmdArgv2);
            }
            else{
                ;//wait(NULL);
                //waitpid(pid, &status1, 0);
                //waitpid(pid2, &status2, 0);
                close(myPipe[0]);
                close(myPipe[1]);
            }
        }
        else
            waitpid(pid, &status1, 0);
            //wait(NULL);
    }
}

void processCommand(){
    if (builtin)
        do_it();
    else
        execute_it();
}

int getCommand(){
    init_scanner_and_parser();
    if (yyparse()) {
        understand_errors();
        return ERRORS;
    }
    else {
        if (bicmd == BYE_CMD) {
            return BYE_CMD;
        }
        else {
            return OK;
        }
    }
}

int main( int argc, char *argv[], char ** environ ){
    printf("=====================================================\n");
    printf("------------<{(Welcome to the SHELL)}>---------------\n");
    printf("=====================================================\n\n");
    shell_init();
    int flag = 1;
    while (1) {
        if(flag) {
            printPrompt();
        }
        else {
            flag = 1;
        }
        switch (CMD = getCommand()) {
            case OK:
                processCommand();
                break;

            case ERRORS:
                recover_from_errors();
                flag = 1;
                break;

            case BYE_CMD:
                printf("Goodbye!\n\n");
                exit(0);
            default:
                break;
        }
    }
    return 0;
}

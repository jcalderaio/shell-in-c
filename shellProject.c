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
#include <pwd.h>
#include "shellProject.h"

//////////////////////////////////////////////////////
///////Builtin Functions//////////////////////////////
//////////////////////////////////////////////////////

extern char **environ;

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

void wTest(){
    DIR *dirp;
    char* second;
    struct dirent* dir;
    dirp = opendir(currentWorkDir);
    if(dirp){
        while((dir = readdir(dirp)) != NULL){
            second = dir->d_name;
            if(wCard(fileName, second)){
                wcFound = second;
                break;
            }
        }
        closedir(dirp);
    }
}

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

void goPath(const char* thePathStr){
    if(isTilde == 1){
            getCurrentPath();
            strcpy(currLoc, home);
            if(!(thePathStr[0] == '/')){
                strcat(currLoc, "/");
            }
            strcat(currLoc, thePathStr);
            currentWorkDir = currLoc;
            removeSpaces(currentWorkDir);
            int isDir = chdir(currentWorkDir);
            if(isDir){
                printf("%s is not a valid directory name.\n", thePathStr);
            }
            isTilde = 0;
        }
        else{
            if(dotdot == 1){
                getCurrentPath();
                strcpy(currLoc, currentWorkDir);
                if(!(thePathStr[0] == '/')){
                    strcat(currLoc, "/");
                }
                strcat(currLoc, "..");
                currentWorkDir = currLoc;
                removeSpaces(currentWorkDir);
                int isDir = chdir(currentWorkDir);
                if(isDir){
                    printf("%s is not a valid directory name.\n", thePathStr);
                }

                getCurrentPath();
                strcpy(currLoc, currentWorkDir);
                if(!(thePathStr[0] == '/')){
                    strcat(currLoc, "/");
                }
                strcat(currLoc, thePathStr);
                currentWorkDir = currLoc;
                removeSpaces(currentWorkDir);
                isDir = chdir(currentWorkDir);
                if(isDir){
                    printf("%s is not a valid directory name.\n", thePathStr);
                }

                dotdot = 0;
            }
            else{
                getCurrentPath();
                strcpy(currLoc, currentWorkDir);
                if(!(thePathStr[0] == '/')){
                    strcat(currLoc, "/");
                }
                strcat(currLoc, thePathStr);
                currentWorkDir = currLoc;
                removeSpaces(currentWorkDir);
                int isDir = chdir(currentWorkDir);
                if(isDir){
                    printf("%s is not a valid directory name.\n", thePathStr);
                }
            }
        }

        thePathStr = "";
}

void goPathUser(){
    struct passwd *getpwnam(const char *);
        if(userName[0] == '/'){
            goHome();
            goPath(userName+1);
        }
        else{
            goPath(userName);
        }
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
            setenv(string_1, "", 0);
            printf("\"%s\" added to environment variables!\n", string_1);
        }
        else {
            char* string_1 = remove_white(argv[0]);
            setenv(string_1, remove_white(argv[1]), 0);
            printf("\"%s\" added to environment variables!\n", string_1);
        }
    }
    else{
        if(argv[0] == NULL) {
            printEnvironment();
        }
        else {
            getCurrentPath();
            char* string_1 = remove_white(argv[0]);
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
        char* string_1 = remove_white(argv[0]);
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
        printf("%s: %s\n", aliasTable[count].key, aliasTable[count].value);
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

void check_alias(char * key) {

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
        return;
    }

    if(currAlias.nested != -1) { //there is a nested command

        while(currAlias.nested != -1){
            currAlias = aliasTable[currAlias.nested];
        }
    }

    char* argument_future = argv[1];
    char* string = (char*) malloc(sizeof(strlen(currAlias.value)));
    char* drf;
    char* token = strtok_r(string, " ", &drf);
    int i = 0;
    while (token != NULL){
        argv[i] = token;
        ++i;
        token = strtok_r(NULL, " ", &drf);
    }
    if(argument_future == NULL)
        argv[i] = NULL;
    else{
        argv[i] = argument_future;
        argv[++i] = NULL;
    }
    memset(input_command,0,strlen(input_command));
    input_command = argv[0];
    return;
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
    printf("\n\n%d\n\n", isWild);
    if(isWild == 1){
        wTest();
        if(wcFound != ""){
            removeSpaces(wcFound);
            fileName = wcFound;
            printf("\n\n%s\n\n", fileName);
        }
    }
    if(isTilde == 1){
        goHome();
        fileName = fileName + 1;
    }
    if(fileName[0] == '/'){
        fileName = fileName + 1;
    }
    printf("\n\n%s\n\n", fileName);
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
                printf("\n\nMADE IT HERE\n\n");
                d2 = opendir(dir->d_name);
                printf("\n\nd2 = %d\n\n", d2);
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

void in_redir(){

}

void out_redir(){

}

///////////////////////////////////////////////////////
///////Error Handling//////////////////////////////////
///////////////////////////////////////////////////////

void understand_errors(){
    printf("An error occured while parsing the yacc file.\n");
}

void recover_from_errors(){
    // Find out if error occurs in middle of command
    // That is, the command still has a “tail”
    // In this case you have to recover by “eating”
    // the rest of the command.
    // To do this: use yylex() directly.
    printf("Command Error!!!");
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
            goPath(strPath);
            break;
        case CDUser_CMD:
            goPathUser();
            break;
        case LS_CMD:
            goLS();
            break;
        case LSWord_CMD:
            goLSWord();
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

void undoit(){
    //Need to define this function
}

int executable(){
    int i = 0;
    for(i = 0; pathtab[i] != NULL; ++i){
        int len = strlen(pathtab[i]) + strlen(input_command) + strlen("/"); // add 1 for the '/'
        executable_path = malloc(len);
        strcpy(executable_path, pathtab[i]);
        strcat(executable_path, "/");
        strcat(executable_path, input_command);
        int retVal = access(executable_path, X_OK);
        if(retVal == 0)
            return OK;
    }
    return SYSERR;
}

void execute_it(){
    // Handle  command execution, pipelining, i/o redirection, and background processing.
    // Utilize a command table whose components are plugged in during parsing by yacc.
    //check_alias(input_command);

    if(!executable()) {
        pid_t pid = fork();
        int stat;
        if(pid == 0){
            switch (currcmd){
            case IO_ADDTOFILE:
                    if(check_out_file() == NULL){
                        int fd0 = fopen(distf, 0644);
                        dup2(fd0, distf);
                        fclose(distf);
                    }
                    break;
            case IO_APPENDTOFILE:
                    break;
            default:
                    break;
        }
            //child process
            execve(executable_path, argv , environ);
            free(executable_path);
        }
        else if(pid < 0){
            //error forking
            perror(executable_path);
        }
        else{
            waitpid(pid, &stat, 0);
        }
    }
    else{

        printf("%s %s\n", input_command, ": command not found");
    }
    //Build up the pipeline (create and set up pipe end points (using pipe, dup)
    //Process background
    return;

    // //  * Check io file existence in case of io-redirection.
    // if( check_in_file() == SYSERR ) {
    //     printf("Error reading from : %s", srcf);
    //     return;
    // }
    // if( check_out_file() == SYSERR ) {
    //     printf("Error writing to : %s", distf);
    //     return;
    // }

    // printf("%s :command not found\n", input_command);

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
        }
    }
    return 0;
}

#include <stdio.h>
#include "shellProject.h"

void init_scanner_and_parser(){
    // Need to initialize all the variables
    argc = 0;
    bicmd = 0;
    builtin = 0;
}

void printPrompt(){
    printf("[shell-->$] ");
    return;
}

void understand_errors(){
    printf("An error occured while parsing the yacc file.\n");
}

void shell_init(){
    //init all variables
    currcmd = 0;



    //define (allocate storage) for some var/tables
    struct alias aliastab[MAXALIAS];
    struct env envtab[MAXENV];

    //init all tables (e.g., alias table)
    //get PATH environment variable (use getenv())
    char* my_path = getenv("PATH");
    char* delim = ":";
    char* token = strtok(my_path, delim);

    int i = 0;
    while(token != NULL){
        pathtab[i] = token;
        i++;
        token = strtok(NULL, delim);
    }
    pathtab[i] = NULL;
    //printf("two: %d\n", strlen(pathtab));
    //get HOME env variable (also use getenv())
    char *home_path = getenv("HOME");
    //printf("%s", home_path);
    home = home_path;
    //disable anything that can kill your shell
    //(the shell should never die; only can be exit)
    //do anything you feel should be done as init
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

void getCommand(){
    init_scanner_and_parser();
    if (yyparse())
        understand_errors();
    else
        return (OK);
}

void recover_from_errors(){
    // Find out if error occurs in middle of command
    // That is, the command still has a “tail”
    // In this case you have to recover by “eating”
    // the rest of the command.
    // To do this: use yylex() directly.
}

void processCommand(){
    if (builtin)
        do_it();        // run built-in commands – no fork
                        // no exec; only your code + Unix
                        //system calls.
    else
        execute_it();   // execute general commands
                        //using fork and exec
}

void do_it(){
    switch (builtin) {
      case ALIAS …  // e.g., alias(); alias(name, word);
      case CDHome …     // e.g., gohome();
      case CDPath … // e.g., chdir(path);
      case UNALIAS …
      case SETENV …
      case PRINTENV …
    …
    }
}

void undoit(){
    //Need to define this function
}

void execute_it(){
    // Handle  command execution, pipelining, i/o redirection, and background processing.
    // Utilize a command table whose components are plugged in during parsing by yacc.

    /*
     * Check Command Accessability and Executability
     */
    if( ! Executable() ) {
        //use access() system call with X_OK
        nuterr("Command not Found");
        return;
    }

    /*
     * Check io file existence in case of io-redirection.
     */
    if( check_in_file()==SYSERR ) {
        nuterr("Cann't read from : %s",srcf);
        return;
    }
    if( check_out_file()==SYSERR ) {
        nuterr("Cann't write to : %s",distf);
        return;
    }

    //Build up the pipeline (create and set up pipe end points (using pipe, dup)
    //Process background
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
        if(retVal == 0){
            return OK;
        }
    }
    return ERRORS;
}

int main(void){
    shell_init();
    while (1) {
        printPrompt( );
        switch (CMD = getCommand()) {
            case: BYE
                exit();
            case: ERRORS
                recover_from_errors();
                break;
            case: OK
                processCommand();
                break;
        }
    }
}

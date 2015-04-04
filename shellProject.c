#include <stdio.h>
#include "shellProject.h"

void init_scanner_and_parser(){
    // Need to initialize all the variables
}

void shell_init(){
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
        Return (OK);
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

int main(void){
    shell_init();
    while (1) {
        printPrompt( );
        switch (CMD = getCommand()) {
            case: BYE       exit();
            case: ERRORS    recover_from_errors();
            case: OK        processCommand();
        }
    }
}

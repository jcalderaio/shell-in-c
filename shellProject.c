    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <ctype.h>
    #include <string.h>
    #include <dirent.h>
    #include <errno.h>
    #include "shellProject.h"


    //////////////////////////////////////////////////////
    ///////Builtin Functions//////////////////////////////
    //////////////////////////////////////////////////////

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

    void getCurrentPath(){
        char * cwd;
        cwd = getcwd (0, 0);
        if (! cwd) {
            fprintf (stderr, "getcwd failed: %s\n", strerror (errno));
        }
        else {
            //printf("\n\nI am here\n\n");
            //printf("%s\n", cwd);
            currentWorkDir = cwd;
           // printf("%s\n", currentWorkDir);
            free(cwd);
            //printf("\n\nI am here\n\n");
        }
    }

    void goHome(){
        strcpy(currLoc, home);
        printf("You are now being redirected to the home directory\n");
        chdir(home);
    }

    void goPath(const char* thePathStr){
        getCurrentPath();
        strcpy(currLoc, currentWorkDir);
        printf("%s\n", currLoc);
        printf("%s\n", currentWorkDir);
        strcat(currLoc, "/");
        strcat(currLoc, thePathStr);
        currentWorkDir = currLoc;
        removeSpaces(currentWorkDir);
        int isDir = chdir(currentWorkDir);
        if(isDir){
            printf("%s is not a valid directory name.\n", thePathStr);
        }
    }





    void do_print_Alias(struct AliasNode* alias) {
        char* toPrint = alias->key;
        printf("%s", toPrint);
        printf(": ");
        toPrint = alias->value;
        printf("%s", toPrint);
        printf("\n");
	
    }

    void printAlias(char* dec1) {
        if (dec1 == 0) {
            printf("No aliases have been created.");
            return;
        }
        else {
            struct AliasNode* current = dec1;
	   // printf("hgdsgbvhfdsgv",aliasHead2->key,aliasHead2->value);
            printf("Current Aliases: \n");
            while (current != NULL) {
                do_print_Alias(current);
                current = current->next;

            }
        }
	
        
   }

	void createAlias(char* word3,char* word4)
	{
		
		aliasHead=(struct AliasNode *)malloc(sizeof(struct AliasNode));
		aliasHead->key=word3;
		aliasHead->value=word4;
		aliasHead->next=NULL;
		//aliasHead3=aliasHead;
		//printf("alias3",aliasHead3->key,aliasHead3->value);
		//p2=*k;
		if(aliasHead1==NULL)
		{
		aliasHead1=aliasHead;
		aliasHead2=aliasHead;
		dec=aliasHead;
		aliasHead3=aliasHead;
		aliasHead4=aliasHead;
		aliasHead5=aliasHead;
		//printf("dedfe",aliasHead1->key,aliasHead1->value);
		}
		else
		{
		while(aliasHead1->next!=NULL)
		{
			aliasHead1=aliasHead1->next;
		}
		aliasHead1->next=aliasHead;
		}
	}

		void unaliasword(char* word6)
		{
			aliasHead3=aliasHead5;
    			char* temp = aliasHead3->key;
			if(strcmp(temp,word6) == 0)
			{
			
				aliasHead3=aliasHead4->next;
				aliasHead4->next=NULL;
				free(aliasHead4);
				aliasHead4=aliasHead3;
				printAlias(aliasHead3);
			}
			else{
    			while(strcmp((aliasHead3->next->key),word6) != 0)
    			{
    				aliasHead3=aliasHead3->next;
    			}
			//printf("vbhvbv",aliasHead3->next->key);
			aliasHead4=aliasHead3->next;
			aliasHead3->next=aliasHead4->next;
			aliasHead4->next=NULL;
			free(aliasHead4);
			printAlias(aliasHead5);
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
        DIR *dirp;
        struct dirent *dir;
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
        return 0;
    }

    int check_out_file(){
        return 0;
    }

    void init_scanner_and_parser(){
        // Need to initialize all the variables
        argc = 0;
        bicmd = 0;
        builtin = 0;
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
        //struct env envtab[MAXENV];

        //init all tables (e.g., alias table)
        //get PATH environment variable (use getenv())
        char *currPath = getenv("PATH");
        char *homePath = getenv("HOME");

        char* dlim = ":";
        char* tok = strtok(currPath, dlim);

        int i = 0;
        while(tok != NULL){
            pathtab[i] = tok;
            i++;
            tok = strtok(NULL, dlim);
        }
        pathtab[i] = NULL;
        //printf("two: %d\n", strlen(pathtab));
        //get HOME env variable (also use getenv())

        //printf("%s", home);
        home = homePath;
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

    void do_it(){
        switch (bicmd) {
          case CDHome_CMD:
                goHome();
                break;
          case CDPath_CMD:
                goPath(strPath);
                break;
          case LS_CMD:
                goLS();
                break;
          case LSWord_CMD:
                goLSWord();
                break;
          case ALIAS_CMD:
                printAlias(dec);
                break;
	  case ALIAS_CMD_CREATE:
                createAlias(word1,word2);
                break;
          case UNALIAS_CMD:
		unaliasword(word5);
                break;
          case SETENV_CMD:
                break;
          case UNSETENV_CMD:
                break;
          case PRINTENV_CMD:
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

    void execute_it(){
        // Handle  command execution, pipelining, i/o redirection, and background processing.
        // Utilize a command table whose components are plugged in during parsing by yacc.

        /*
         * Check Command Accessability and Executability
         */
        if(isExe == 0) {
            //use access() system call with X_OK
            return;
        }

        /*
         * Check io file existence in case of io-redirection.
         */
        if( check_in_file() == SYSERR ) {
            //nuterr("Cann't read from : %s",srcf);
            return;
        }
        if( check_out_file() == SYSERR ) {
            //nuterr("Cann't write to : %s",distf);
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
            if(retVal == 0)
                return OK;
        }
        return SYSERR;
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

    int main( int argc, char *argv[] ){
        printf("=====================================================\n");
        printf("---------------Welcome to the shell------------------\n");
        printf("=====================================================\n\n");
        shell_init();
        while (1) {
            printPrompt();
            switch (CMD = getCommand()) {
                case BYE_CMD:
                    printf("Goodbye!\n\n");
                    exit(0);
                case ERRORS:
                    recover_from_errors();
                    break;
                case OK:
                    processCommand();
                    break;
            }
        }
        return 0;
    }

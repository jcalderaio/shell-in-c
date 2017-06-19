# shellProject
## hkhkjh
This is a shell that was coded using lex and yacc in c.

Implemented features
===================================
    - CD
    - CD ~
    - CD WORD
    - LS
    - LS WORD
    - LS WORD WORD
    - SETENV
    - SETENV WORD
    - SETENV WORD WORD
    - UNSETENV WORD
    - PRINTENV
    - ALIAS
    - ALIAS WORD WORD
    - UNALIAS WORD
    - We also implemented reparsing char* when they are alias
    - We implemented I/O redirect WORD > WORD, WORD >> WORD, WORD < WORD
    - We also made ${variable} return a value
    - If you type ~ this will take you to the home drectory
    - We also incorporated tilde in the file path ~/bin/app
    - We have double dot and single dot implemented (i.e: cd.. cd . cd ../Desktop/stuff cd ./Desktop/stuff)
    - We have wildcard in place using * and ?

NOT Implemented features
==================================
    - Pipelining
    - Muitiplte I/O redirection
    - ~User tilde expansion
    - replacing environment expansion within
      words and strings ${ }

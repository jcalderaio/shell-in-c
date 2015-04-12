%{
#include <stdio.h>
#include <ctype.h>
#include "y.tab.h"
extern YYSTYPE yylval;
%}


%%

cd                  return CD;
alias               return ALIAS;
unalias             return UNALIAS;
setenv              return SETENV;
unsetenv            return UNSETENV;
printenv            return PRINTENV;
bye                 return BYE;
[a-zA-Z0-9\-\.*_]+  {
                        yylval.word = strdup(yytext);
                        return WORD;
                    }
[^\|\>\<\&\t\n\r][^\|\>\<\& \t\n]*  {
                                        yylval.option = strdup(yytext);
                                        return WORD;
                                    }
\"                  return QUOTE;
\<                  return LT;
\>                  return GT;
\|                  return PIPE;
\&                  return BACKGROUND;
\\                  return BACKSLASH;
~                   return TILDE;
\n                  return NEWLINE
[ \t\r]+            ;


%%

int yywrap(void){
    return 1;
}
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
[-][a-z]            {
                        yylval.option = strdup(yytext);
                        return OPTION;
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
\n                  return NEWLINE;
[ \t\r]+            ;


%%

int yywrap(void){
    return 1;
}
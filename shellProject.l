%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>
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
ls                  return LS;
[-][a-z]                            { yylval.option = strdup(yytext); return OPTION; }
[a-zA-Z][a-zA-Z0-9\/-_]*            { yylval.word   = strdup(yytext); return WORD; }
\"[^"\n]*["\n]                      {
                                       yylval.string = strdup(yytext+1);
                                       if (yylval.string[yyleng-2] != '"'){
                                          recover_from_errors();
                                          break;
                                       }
                                       else{
                                          yylval.string[yyleng-2] = 0;
                                          return STRING;
                                       }
                                    }

\"                  return QUOTE;
\{                  return LEFTBRACE;
\}                  return RIGHTBRACE;
\$                  return DOLLARSIGN;
\<                  return LT;
\>                  return GT;
\|                  return PIPE;
\&                  return BACKGROUND;
\\                  return BACKSLASH;
\~                  return TILDE;
\n                  return NEWLINE;
\.\.                return PERIODPERIOD;
\.                  return PERIOD;
[ \t\r]+            ;

%%

int yywrap(void){
    return 1;
}
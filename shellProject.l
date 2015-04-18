%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "y.tab.h"
#include "shellProject.h"
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
[-][a-z]                                    { yylval.option = strdup(yytext); return OPTION; }
[a-zA-Z\/\-\_\*\?\.][a-zA-Z0-9\/\-\_\*\?\.]*    {
                                              yylval.word   = strdup(yytext);
                                              int i = 0;
                                              isWild = 0;
                                              for(i = 0; i < yyleng; ++i){
                                                if(yylval.word[i] == '*' || yylval.word[i] == '?'){
                                                  isWild = 1;
                                                  break;
                                                }
                                              }
                                              return WORD;
                                            }
\"[^"\n]*["\n]                                {
                                               yylval.string = strdup(yytext);
                                               if (yylval.string[yyleng-1] != '"'){
                                                  return WORD;
                                               }
                                               else{
                                                  yylval.string = strdup(yytext + 1);
                                                  if(yylval.string[0] == '~'){
                                                    yylval.string = strdup(yytext + 2);
                                                    isTilde = 1;
                                                  }
                                                  else{
                                                    isTilde = 0;
                                                  }
                                                  yylval.string[yyleng - 2] = 0;
                                                  return WORD;
                                               }
                                            }
\$\{[^ \$\{\}\n]*[}\n]                      {
                                              yylval.envexp = strdup(yytext);
                                              int i = 0;
                                              if (yylval.string[yyleng-3] != '}'){
                                                  return WORD;
                                               }
                                               else{
                                                  yylval.envexp = strdup(yytext+2);
                                                  yylval.string[yyleng-3] = 0;
                                                  return ENVEXP;
                                               }
                                            }

\"                  return QUOTE;
\{                  return LEFTBRACE;
\}                  return RIGHTBRACE;
\$                  return DOLLARSIGN;
\<                  return LT;
\<\<                return LTLT;
\>                  return GT;
\>\>                return GTGT;
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
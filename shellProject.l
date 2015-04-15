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
ls                  return LS;
[-][a-z]            {
                        yylval.option = strdup(yytext);
                        return OPTION;
                    }
[^\|\>\<\&\t\n\r][^\|\>\<\& \t\n]*  {
                                        yylval.word = strdup(yytext);
                                        return WORD;
                                    }
["][^\|\>\<\&\t\n\r][^\|\>\<\&\t\n]*["] {
                                            yylval.string = strdup(yytext);
                                            return STRING;
                                        }
\"                  return QUOTE;
\<                  return LT;
\>                  return GT;
\|                  return PIPE;
\&                  return BACKGROUND;
\\                  return BACKSLASH;
"//"                return FORWARDSLASH;
"~/"                return TILDE;
"./"                return SINGLEPERIOD;
"../"               return DOUBLEPERIOD;
\n                  return NEWLINE;
[ \t\r]+            ;

%%

int yywrap(void){
    return 1;
}
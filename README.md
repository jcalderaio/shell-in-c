# shellProject
This is a shell that was coded using lex and yacc in c.

///////////////////////////////////////////////////////
///////Lex Input///////////////////////////////////////
///////////////////////////////////////////////////////

FIRST PART

%%

pattern                        //action

. . . .

%%

THIRD PART

///////////////////////////////////////////////////////
///////How to run//////////////////////////////////////
///////////////////////////////////////////////////////

$ lex ex1.l                   //Process the lex file to generate a scanner

$cc lex.yy.c -ll              //Compile the scanner and grab main() from the lex library (-ll option)

$./a.out

//The you enter in the input and you should
//recieve the output

///////////////////////////////////////////////////////
///////Lex Patterns////////////////////////////////////
///////////////////////////////////////////////////////

1. abc                       //Match the string abc

2. [a-zA-Z]                  //Match and lower or upercase letter

3. dog.*cat                  //Match any lower or uppercase letter

4. (ab)+                     //Match one or more occurence of "ab" concatenated

5. [^a-z]+                   //Match any string of one or more characters that do not include lower case a-z

6. [+-]?[0-9]+               //Match any stringof one or more digits with an optional prefix of + or -

%{
#include<stdio.h>
#include<stdlib.h>
int answer=0;
%}
%token NUMBER ID NL
%left '+' '-'
%left '*' '/'
%%
stmt : exp NL { printf("Answer: %d \n",$1); 
	exit(0);} 
|
exp1 NL { printf("Valid Expression \nBut, Calculation Can Be Performed On Variables \n"); 
	exit(0);}
; 

exp : exp '+' exp  	{$$=$1+$3;}
| exp '-' exp		{$$=$1-$3;}
| exp '*' exp		{$$=$1*$3;}
| exp '/' exp		{$$=$1/$3;}
| '(' exp ')'
| NUMBER 
;

exp1 : exp1 '+' exp1  	
| exp1 '-' exp1		
| exp1 '*' exp1	
| exp1 '/' exp1		
| '(' exp1 ')'
| ID 
;

%%
int yyerror(char *msg)
{
printf("Invalid Expression \n");
exit(0);
}
main()
{
printf("Enter the expression : \n");
yyparse();
}
int yywrap(){return 1;}
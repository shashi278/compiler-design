/*
	Topic: Compiler Design
	Program: Write a C programe to evaluate an expression of type (e1 [+,-,*,/] e2)
			where e can be an expression or number or r(stdin)
	By: Shashi Ranjan(39/CSE/17080/278)
*/

#include<lex.h>
#include<parser.h>
#include<backend.h>

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

char expr[255];

int main(int argc, char const *argv[]){

	if (argc!=2)
	{	
		printf("Wrong command format.\n");
		printf("Usage: ./<executable> <file_name.txt>\n'file_name': Name of the text file containing an expression to evaluate.\n");
		printf("\nExiting...\n");
		return 0;
	}

	FILE *fp;
	fp= fopen(argv[1], "r");

	if(fp==NULL){
		printf("Cannot find '%s'. Please specify correct file path.\n", argv[1]);
		return 0;
	}

	ASTnode_t *tpp= (ASTnode_t *)malloc(sizeof(ASTnode_t));

	if(tpp==NULL){
		printf("Memory allocation error! Nothing that you can do here :(\n");
		return 0;
	}

	printf("Parsing expression....\n");
	if(parser(&tpp, fp)==1){
		printf("Syntax tree successfully built.\n");
		printf("Traversing syntax tree...\n");
		int res= interpreter(tpp);
		printf("\n%s = %d\n", expr,res);
		
	}
	else
		printf("Error in building syntax tree.\nMake sure the expression is valid.\n\nExiting...\n");
	return 0;

}

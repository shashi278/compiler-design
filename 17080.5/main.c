/*
	Topic: Compiler Design

	Program: Write a C programme to either accept or reject a given expression using a Predictive Parser Table
	built according to the provided grammar.

	By: Shashi Ranjan(39/CSE/17080/278)
*/

#include<lex.h>
#include<parser.h>
#include<stack.h>

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

char expr[255];

int main(int argc, char const *argv[]){

	FILE *fp;

	//provide expression through stdin
	if(argc==1){
		//temporary file, will be deleted after execution
		fp= fopen("_tmp.txt","w");
		printf("Enter expression and hit Return(Enter) to end:\n\n>>> ");

		char _expr[257];
		scanf("%257[^\n]",_expr);
		fprintf(fp, "%s", _expr);
		fclose(fp);
		fp= fopen("_tmp.txt","r");
	}

	//second argv must be a file name
	else if(argc==2){
		fp= fopen(argv[1], "r");

		if(fp==NULL){
			printf("Cannot find '%s'. Please specify correct file path.\n", argv[1]);
			return 0;
		}
	}
	else{	
		printf("Wrong command format.\n");
		printf("Usage: ./<executable> [<file_name.txt>, optional]\n");
		printf("\nExiting...\n");
		return 0;
	}

	stack *stack_p= (stack *)malloc(sizeof(stack));

	if(stack_p==NULL){
		printf("Memory allocation error! Nothing that you can do here :(\n");
		return 0;
	}

	//initialize stack
	init_stack(stack_p);

	//make rules
	make_rules();

	if(accept_or_reject(stack_p, fp)==accept)
		printf("Accepted!\n");
	else
		printf("Rejected :(\n");

	//delete _tmp.txt if available
	remove("_tmp.txt");
	return 0;

}

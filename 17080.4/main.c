/*
	Topic: Compiler Design

	Program: Write a C programme to evaluate an expression of type (e1 [+,-,*,/] e2) and (id=e)
			 where e can be an expression or number or r(stdin) and id is an identifier

	By: Shashi Ranjan(39/CSE/17080/278)
*/

#include<lex.h>
#include<parser.h>
#include<backend.h>
#include<symTab.h>

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

	ASTnode_t *tpp= (ASTnode_t *)malloc(sizeof(ASTnode_t));

	if(tpp==NULL){
		printf("Memory allocation error! Nothing that you can do here :(\n");
		return 0;
	}

	//initialize symTab
	initSymTab();

	//printf("Parsing expression....\n");
	if(parser(&tpp, fp)==1){
		//printf("Syntax tree successfully built.\n");
		//printf("Traversing syntax tree...\n");
		int res= interpreter(tpp);
		printf("\n%s = %d\n", expr,res);

		//delete _tmp.txt if available
		remove("_tmp.txt");
		
	}
	else
		printf("Error in building syntax tree.\nMake sure the expression is valid.\n\nExiting...\n");
	return 0;

}

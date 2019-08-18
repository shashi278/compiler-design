#include<stdio.h>
#include<stdlib.h>
#include<backend.h>

int interpreter(ASTnode_t *tpp){
	//traverse the tree pointed by tpp

	if(tpp==NULL){
		return 0;
	}

	if((tpp)->type=='D'){
		return (tpp)->val;
	}
	if((tpp)->type=='R'){
		int x;
		printf("Enter r: ");
		scanf("%d",&x);
		return x;
	}

	//evaluate left
	int left_num= interpreter((tpp)->left);
	//evaluate right
	int rt_num= interpreter((tpp)->right);
	
	char op= (tpp)->op;

	if(op=='+')
		return left_num+rt_num;
	if(op=='-')
		return left_num-rt_num;
	if(op=='*')
		return left_num*rt_num;

	if(op=='/' ){
		if(rt_num==0){
			printf("Error: ZeroDivisionError\n");
			exit(1);
		}
		return left_num/rt_num;
	}

	return 0;

}
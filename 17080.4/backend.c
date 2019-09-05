#include<stdio.h>
#include<stdlib.h>
#include<backend.h>
#include<symTab.h>

//returns the user input
int enter_r();

//get the value of id from symTab
void get_nums(int*, int*, ASTnode_t*, ASTnode_t*);

//raise specific error and exit
void raiseError(int err_no, char identifier){
	if(err_no==ZeroDivisionError)
		printf(ZDE_msg);
	if(err_no==NameError)
		printf(NE_msg,identifier);
	exit(1);
}

int interpreter(ASTnode_t *tpp){
	//traverse the tree pointed by tpp

	if(tpp==NULL){
		return 0;
	}

	if((tpp)->type=='D' || (tpp)->type=='N'){
		return (tpp)->val;
	}
	if((tpp)->type=='R'){
		return enter_r();
	}
	
	//evaluate left
	int left_= interpreter((tpp)->left);

	//evaluate right
	int rt_= interpreter((tpp)->right);

	int *left_num=&left_, *rt_num=&rt_;
	
	char op= (tpp)->op;

	//get the value of an identifier from symTab if its being used in the expression
	if(op!='=')
		get_nums(left_num,rt_num,(tpp)->left,(tpp)->right);

	if(op=='+')
		return *left_num+(*rt_num);
	if(op=='-')
		return *left_num-(*rt_num);
	if(op=='*')
		return (*left_num)*(*rt_num);
	if(op=='/' ){
		if(*rt_num==0){
			raiseError(ZeroDivisionError,' ');
		}
		return *left_num/(*rt_num);
	}
	if(op=='%' ){
		if(*rt_num==0){
			raiseError(ZeroDivisionError,' ');
		}
		return *left_num%(*rt_num);
	}
	if(op==','){
		return *rt_num;
	}
	if(op=='='){
		updateSymTab(*left_num,*rt_num);
		return *rt_num;
	}

	return 0;
}

int enter_r(){
	int x;
	printf("Enter r: ");
	scanf("%d",&x);
	return x;
}

void get_nums(int *left_num, int *rt_num, ASTnode_t *left_, ASTnode_t *rt_){
	
	int x;
	if(left_->type=='N'){
		int *vp=&x;
		getVal(left_->val, vp)!=1? raiseError(NameError, left_->val+(int)'A') : (*left_num= *vp);
		
	}
	if(rt_->type=='N'){
		int *vp= &x;
		getVal(rt_->val,vp)!=1? raiseError(NameError, rt_->val+(int)'A') : (*rt_num= *vp);
	}

}
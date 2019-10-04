//stack.c

#include <stack.h>

stack stack_p;

void init_stack(stack *stack_p){
	stack_p->tos= -1;
}

int push(stack *stack_p, int data){
	if(stack_p->tos>=SIZE)
		return ERROR;

	stack_p->tos++;
	stack_p->data[stack_p->tos]=data;
	return OK;
}

int pop(stack *stack_p){
	int data= stack_p->data[stack_p->tos];
	stack_p->tos--;
	return data;
}

int isEmpty(stack *stack_p){
	return (stack_p->tos<=-1)? OK : ERROR;
}

int isFull(stack *stack_p){
	return (stack_p->tos>=SIZE)? OK : ERROR;	
}
// stack.h
#include <stdio.h>
#ifndef _STACK_H
#define _STACK_H

#define SIZE 1000
#define ERROR 0
#define OK 1

typedef struct {
	int data[SIZE];
	int tos;
} stack;

void init_stack(stack *) ;
int push(stack * , int);
int pop(stack *);
int top(stack *, int *);
int isEmpty(stack *);
int isFull(stack *);
#endif
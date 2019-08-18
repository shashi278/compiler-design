//parser.h
#ifndef PARSER_H
#define PARSER_H

#include<stdio.h>

typedef struct node{
	char type;
	unsigned int val;
	struct node *left,*right;
	char op;
} ASTnode_t;

extern int parser(ASTnode_t **, FILE *);

#endif
//parser.h
#ifndef PARSER_H
#define PARSER_H

#include<stdio.h>

#define is_valid_op(tmp)(\
		   tmp=='+' || tmp=='-'\
		|| tmp=='*' || tmp=='/' \
		|| tmp=='%' || tmp==',' \
		|| tmp=='=' || tmp==')')

typedef struct node{
	char type;			// D: Data, N: ID, I: Internal node, R: Stdin
	unsigned int val;
	struct node *left,*right;
	char op;
} ASTnode_t;

extern int parser(ASTnode_t **, FILE *);

#endif
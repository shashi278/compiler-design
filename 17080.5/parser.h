//parser.h
#ifndef _PARSER_H
#define _PARSER_H

#include <stack.h>
#include <stdio.h>

#define LEN 10
#define accept 1
#define reject 0
#define ERR -1
#define ERR_MSG "\n\x1B[31mError:\x1B[0m Unexpected token '%c'\n"

typedef struct{
	int len;		//length of right hand side of the rule
	int rule[LEN];	//code sequences
} rule_t;

extern void make_rules();
extern void push_rules(stack *, rule_t);
extern int accept_or_reject(stack *, FILE *);
extern int check_next(int, stack *, FILE *);
extern int consume(int, FILE *);
extern int get_index(char);
extern void raiseError();

#endif
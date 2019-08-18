//lex.h
#ifndef LEX_H
#define LEX_H

#include <stdio.h>

#define END 256
#define NUM 257

typedef struct{
	int tokenClass;
	int val;
} token_t;

//to store the expression
extern char expr[255];

extern token_t token;
extern int getNextToken(FILE *);

#endif
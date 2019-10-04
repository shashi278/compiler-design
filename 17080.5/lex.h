//lex.h
#ifndef _LEX_H
#define _LEX_H

#include <stdio.h>

#define END '$'
#define NUM 'N'
#define ID 'I'
#define SIN 'R'
#define BUFFSIZE 257

#define is_potential_op(tmp)(\
		   tmp=='(' || tmp==')'\
		|| tmp=='+' || tmp=='-'\
		|| tmp=='*' || tmp=='/' \
		|| tmp=='r' || tmp=='=' \
		|| tmp==',' || tmp=='%')

#define is_skip_token(tmp)(\
			tmp==' ' || tmp=='\n'\
		|| tmp=='\t' || tmp=='\r'\
		|| tmp=='#')

#define is_potential_num(tmp)(\
		(int)tmp>=48 && (int)tmp<=57\
		)

#define is_potential_identifier(tmp)(\
		(tmp>='A' && tmp<='Z')\
		|| (tmp>='a' && tmp<='z')\
		)

typedef struct{
	char tokenClass;
	int val;
} token_t;

//to store the expression
extern char expr[255];

extern token_t token;
extern int getNextToken(FILE *);

#endif
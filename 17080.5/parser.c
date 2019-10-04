//parser.c
#include <parser.h>
#include <stack.h>
#include <lex.h>

#define NUM_RULES 17

stack stack_p;
rule_t rules[NUM_RULES];
token_t token;

void print_stack(stack *stack_p){
	printf("\n=======Stack=============================\n");
	for(int i=stack_p->tos; i>=0; i--){
		printf("%d\n", stack_p->data[i]);
	}
	printf("=======Stack=============================\n");
}

void raiseError(){
	char c;
	if(token.tokenClass==NUM || token.tokenClass==ID)
		c= token.val;
	else
		c= token.tokenClass;
	printf(ERR_MSG,c);
}

//hard-coded predictive parser table
int rule_table[][10]={
//			 id(I)	,	num(N)	,	stdin(R),	EOF($)	,	(	,	)	,	*	,	+	,	,	,	=
/*0(S)*/	{1		,	1		,	1		,	ERR 	,	1	,	ERR	,	ERR	,	ERR	,	ERR	,	ERR},
/*1(CE)*/	{1		,	1		,	1		,	ERR		,	1	,	ERR	,	ERR	,	ERR	,	ERR	,	ERR},
/*2(CE')*/	{ERR	,	ERR		,	ERR		,	3		,	ERR	,	3	,	ERR	,	ERR	,	2	,	ERR},
/*3(AE)*/	{4		,	5 		,	5		,	ERR		,	5 	,	ERR	,	ERR	,	ERR	,	ERR	,	ERR},
/*4(AE')*/	{ERR	,	ERR		,	ERR		,	ERR		,	ERR	,	ERR	,	ERR	,	ERR	,	ERR	,	6  },
/*5(PE)*/	{7		,	7		,	7		,	ERR		,	7	,	ERR	,	ERR	,	ERR	,	ERR	,	ERR},
/*6(PE')*/	{ERR	,	ERR		,	ERR		,	9		,	ERR	,	9	,	ERR	,	8	,	9	,	ERR},
/*7(ME)*/	{10		,	10		,	10		,	ERR		,	10	,	ERR	,	ERR	,	ERR	,	ERR	,	ERR},
/*8(ME')*/	{ERR	,	ERR		,	ERR		,	12		,	ERR	,	12	,	11	,	12	,	12	,	ERR},
/*9(BE)*/	{14		,	15		,	16		,	ERR		,	13	,	ERR	,	ERR	,	ERR	,	ERR	,	ERR}
		};

int _rules[][4]={
//		len, rules*	
/*0*/	{2, 1, '$'},
/*1*/	{2,	3,	2},
/*2*/	{3,	',', 3, 2},
/*3*/	{1, '~'},	//Epsilon
/*4*/	{2, 'I', 4},
/*5*/	{1,  5},
/*6*/	{2, '=', 3},
/*7*/	{2, 7,  6},
/*8*/	{3, '+', 7, 6},
/*9*/	{1, '~'},
/*10*/	{2, 9, 8},
/*11*/	{3, '*', 9, 8},
/*12*/	{1, '~'},
/*13*/	{3, '(', 1, ')'},
/*14*/	{1, 'I'},
/*15*/	{1, 'N'},
/*16*/	{1, 'R'}
};


void make_rules(){
	/*
	Takes each rule from `_rules` and add it to `rule_t` struct prior to parsing
	*/
	for(int i=0; i<17; i++){
		rules[i].len= _rules[i][0];
		for(int j=1; j<=rules[i].len; j++){
			rules[i].rule[j-1]= _rules[i][j];
		}
	}
}


void push_rules(stack *stack_p, rule_t rule_ele){
	/*
	Push required rules onto the stack in reverse order

	args:
	=====
		- Pointer to stack
		- A rule of type `rule_t` to be pushed onto the stack
	*/
	for(int i=rule_ele.len-1; i>=0; i--)
		push(stack_p, rule_ele.rule[i]);
}


int accept_or_reject(stack *stack_p, FILE *fp){
	/*
	Minimal driving function.

	args:
	=======
		- Pointer to stack
		- Pointer of file containing the expression
	return:
	=======
		`reject`- if the exp. is rejected
		`accept`- if the exp. is accepted
	*/

	push_rules(stack_p,rules[0]); //push start symbol
	//print_stack(stack_p); //for debugging purpose
	getNextToken(fp);

	if(check_next(pop(stack_p), stack_p, fp)==1)
		return accept;
	return reject;
}


int check_next(int top_stack, stack *stack_p, FILE *fp){
	/*
	Backend for `accept_or_reject` function ;)

	Chars used here have integer value greater than 30 meaning, if
	`top_stack` is less than 30, it must not something to be consumed.
	Thus a recursive call to same function can be made for `top_stack`
	less than 30. Otherwise it'll be sent to get consumed.

	args:
	=======
		- Top element of the stack
		- The stack pointer
		- File pointer
	return:
	=======
		0- Incase of error at any point of parsing
		1- else

	*/

	if(top_stack>=30 && (char)top_stack!='$'){
		if(consume(top_stack, fp)==1){
			top_stack= pop(stack_p);
		}
		else{
			raiseError();
			return ERROR;
		}
	}

	int idx= get_index(token.tokenClass);
	if(idx!=-1){
		/*
		Get the required rule to expand using, based on `top_stack` &
		current token(token index from the rule_table, `idx`) and push
		it onto the stack.
		*/
		int entry= rule_table[top_stack][idx];
		if(entry!=ERR){
			push_rules(stack_p, rules[entry]);
			//print_stack(stack_p);

			top_stack= pop(stack_p);
			if(top_stack<=30 && isEmpty(stack_p)==ERROR){
				return check_next(top_stack, stack_p, fp);
			}

			if(isEmpty(stack_p)==ERROR && consume(top_stack, fp)==1){
				top_stack= pop(stack_p);
				//print_stack(stack_p);
				if((char)top_stack=='$' && (char)top_stack==token.tokenClass)
					return 1;
				if((char)top_stack!='$')
					return check_next(top_stack, stack_p, fp);
			}
		}
	}
	raiseError();
	return 0;
}


int consume(int top_stack, FILE *fp){
	/*
	Function to consume the token if `top_stack` and token are same or
	just pop it out incase its epsilon in `top_stack`.
	*/
	if(token.tokenClass==(char)top_stack){
		getNextToken(fp);
		return 1;
	}
	if((char)top_stack=='~'){
		return 1;
	}
	return 0;
}


int get_index(char tc){
	/*
	Take a character and return the corresponding column number from `rule_table`
	*/
	switch(tc){
		case 'I': return 0;
		case 'N': return 1;
		case 'R': return 2;
		case '$': return 3;
		case '(': return 4;
		case ')': return 5;
		case '*': return 6;
		case '+': return 7;
		case ',': return 8;
		case '=': return 9;
		default: return -1;
	}

	return -1;

}
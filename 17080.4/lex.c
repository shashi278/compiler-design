//lex.c
#include<stdlib.h>
#include<string.h>
#include<lex.h>

int getNextToken(FILE *fp){
	char str[2]={'\0','\0'};
	char comment[NUM];

	char tmp= getc(fp);
	while(is_skip_token(tmp)){
		if(tmp=='#'){
			ungetc(tmp, fp);
			fscanf(fp,"%257[^\n]",comment);
		}
		tmp= getc(fp);
	}

	if(is_potential_op(tmp)){
		token.tokenClass= tmp;
		token.val=0;

		str[0]=token.tokenClass;
		strcat(expr,str);
	}
	else if(is_potential_num(tmp)){
		token.tokenClass= NUM;
		ungetc(tmp, fp);
		fscanf(fp, "%d", &token.val);

		char buff[6];
		snprintf(buff,6,"%d",token.val);
		strcat(expr,buff);
	}
	else if(is_potential_identifier(tmp)){
		token.tokenClass= ID;
		token.val= (int)tmp-(int)'A';

		str[0]=tmp;
		strcat(expr,str);

	}

	else if(tmp==EOF){
		token.tokenClass= END;
		token.val=0;
	}
	return 1;

}
//lex.c
#include<stdlib.h>
#include<string.h>
#include<lex.h>

int getNextToken(FILE *fp){
	char str[2]={'\0','\0'};

	char tmp= getc(fp);
	while(tmp==' ' || tmp=='\n' || tmp=='\t' || tmp=='\r'){
		tmp= getc(fp);
	}

	if(tmp=='(' || tmp==')' || tmp=='+' || tmp=='-' || tmp=='*' || tmp=='/' || tmp=='r'){
		token.tokenClass= tmp;
		token.val=0;

		str[0]=token.tokenClass;
		strcat(expr,str);
	}
	else if((int)tmp>=48 && (int)tmp<=57){
		token.tokenClass= NUM;
		ungetc(tmp, fp);
		fscanf(fp, "%d", &token.val);

		char buff[6];
		snprintf(buff,6,"%d",token.val);
		strcat(expr,buff);
	}
	else if(tmp==EOF){
		token.tokenClass= END;
		token.val=0;
	}
	return 1;

}
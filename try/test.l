%{
#include<stdio.h>

#define INT 256
#define FLOAT 257
#define ID 258
#define OK 1
#define ERR 0
#define ERRTOK 1
#define UNDEF -1
#define EEOF 0

int S();
int DL();
int DLx();
int VL();
int VLx();
int D();
int T();

int token=UNDEF;
%}

%option noyywrap

ID ([abc][0123]*)
NAT (0|[1-9]+[0-9]*)
FLT ([0-9]*\.[0-9]+)

%%
{ID}    {return ID;}
"int"   {return INT;}
"float"   {return FLOAT;}
";"     {return (int)';';}
","     {return (int)',';}
[\t]+    {;}

%%

int S(){
    if(token==UNDEF) token=yylex();
    if(token==INT || token==FLOAT){
        if(DL()==OK){
            if(token==UNDEF) token=yylex();
            if(token==EEOF) return OK;
        }
    }
    return ERR;
}

int DL(){
    if(token==UNDEF) token=yylex();
    if(token==INT || token==FLOAT){
        if(D()==OK) return DLx();
    }
    return ERR;
}

int DLx(){
    if(token==UNDEF) token=yylex();
    if(token==EEOF) return OK;
    if(token==';'){
        token=UNDEF;
        if(D()==OK) return DLx();
    }
    return ERR;
}

int VL(){
    if(token==UNDEF) token=yylex();
    if(token==ID){
        token=UNDEF;
        return VLx();
    }
    return ERR;
}

int VLx(){
    if(token==UNDEF) token=yylex();
    if(token==EEOF||token==';'){
        return OK;
    }
    if(token==','){
        token=yylex();
        if(token==ID){
            token=UNDEF;
            return VLx();
        }
    }
    return ERR;
}

int D(){
    if(token==UNDEF) token=yylex();
    if((token==INT || token==FLOAT) && T()==OK)
        return VL();
    return ERR;
}

int T(){
    if(token==UNDEF) token=yylex();
    if(token==INT || token==FLOAT){
        token=UNDEF;
        return OK;
    }
    return ERR;
}

int main(){
    if(S()==OK){
        printf("\nAccept\n");
    }
    else{
        printf("\nReject\n");
    }
    return 0;
}
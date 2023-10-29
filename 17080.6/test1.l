%{
#include <stdio.h>
#include <string.h>
#include <test.tab.h++>

%}

%option noyywrap
%option yylineno

NUM (0|[0-9]+[0-9]*)
FLT ([0-9]*\.[0-9]+)
ID  ([a-zA-Z]+[0-9]*)

%%
[\t]+   {;}
\/\/.   {;}
{NUM}   {
            yylval.integer= atoi(yytext);
            return IC;
        }
{FLT}   {
            yylval.real= atof(yytext);
            return FC;
        }
{ID}    {
            yylval.str= strdup(yytext);
            return ID;
        }
\".\"   {
            yylval.str= (char*)malloc((yyleng+1)*sizeof(char));
            strncpy(yylval.str, yytext+1, yyleng-2);
            yylval.str[yyleng-2]='\0';
            return STRING;
        }
"if"    {return IF;}
"else"  {return ELSE;}
"then"  {return THEN;}
"int"   {return INT;}
"real"  {return REAL;}
"do"    {return DO;}
"nop"   {return NOP;}
"print" {return PRINT;}
"read"  {return READ;}
"then"  {return THEN;}
"while" {return WHILE;}

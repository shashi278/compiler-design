%{
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include "17080.tab.h++"
using namespace std;
%}

%option noyywrap
%option yylineno

%x CMNT

number    (0|([1-9]+[0-9]*))
decimal   ({number}?\.{number})
id        ([a-zA-Z][a-zA-z0-9]*)


%%
\/\/. ;
[ \t\n] ;
{decimal} {
  yylval.real = atof(yytext);
  return FC;
}

{number} {
  yylval.integer = atoi(yytext);
  return IC;
}

\".\" {
  yylval.str=(char *)malloc((yyleng+1)*(sizeof(char)));
  strncpy(yylval.str, yytext+1, yyleng-2);
  yylval.str[yyleng-2]='\0';
  return STRING;
}

"if"                    {return IF;}
"then"                  {return THEN;}
"else"                  {return ELSE;}
"int"                   {return INT;}
"real"                  {return REAL;}
"do"                    {return DO;}
"print"                 {return PRINT;}
"read"                  {return READ;}
"while"                 {return WHILE;}

{id} {
  yylval.str = strdup(yytext); 
  return ID;
}

"+"   {return (int)'+';}
"*"   {return (int)'*';}
"/"   {return (int)'/';}
"=="  {
  return COMP;
}

"<" {return (int)'<';}
">" {return (int)'>';}
"=" {return (int)'=';}
";" {return (int)';';}
":" {return (int)':';}
"&" {return (int)'&';}
"|" {return (int)'|';}
"~" {return (int)'~';}

"-"   {return (int)'-';}

"(" {return (int)'(';}
")" {return (int)')';}
"{" {return (int)'{';}
"}" {return (int)'}';}

%%

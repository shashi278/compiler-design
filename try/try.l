%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<bits/stdc++.h>
#include "try.tab.h++"
using namespace std;
%}

%option noyywrap
%option yylineno

DELIM ([\t])
WHITESPACES ({DELIM}+)
NATNUM ([0-9]+)
FLOAT (([0-9]*\.[0-9]+)|([0-9]+\.[0-9]*))

%%
{WHITESPACES}   {;}
{NATNUM}        {
                    yylval.integer=atoi(yytext);
                    return INT;
                }
{FLOAT}         {
                    yylval.real= (float)atof(yytext);
                    return FLOAT;
                }
"+"             {return (int)'+';}
"-"             {return (int)'-';}
"*"             {return (int)'*';}
"/"             {return (int)'/';}
"\n"            {return (int)'\n';}
")"             {return (int)'(';}
")"             {return (int)')';}
%%
%{
#include <string>

%}

ESPACO [ \t]
DIGITO [0-9]
LETRA [A-Za-z_]
BOOL [true|false]

DELIM {ESPACO}+
NUM {DIGITO}+
REAL {NUM}+("."{NUM}+)?
CHAR \'({LETRA}|{NUM})\'
STRING (["]["])|(["][^\n]+["])
ID {LETRA}({LETRA}|{NUM})*


%%

"\n"		{linha++;}

{DELIM} 	{}

"(float)"|"(int)"|"(String)"   {yylval.label = yytext; return TK_CAST;}

"main"		{return TK_MAIN;}

"int"		{yylval.label = yytext; return TK_TIPO;}
"float"     {yylval.label = yytext; return TK_TIPO;}
"bool"      {yylval.label = yytext; return TK_TIPO;}
"char"		{yylval.label = yytext; return TK_TIPO;}
"String"	{yylval.label = yytext; return TK_TIPO;}

"true"      {yylval.label = "1"; yylval.tipo = "bool"; return TK_BOOL;}
"false"		{yylval.label = "0"; yylval.tipo = "bool"; return TK_BOOL;}


"while"		{yylval.label = yytext; return WHILE;}
"for"		{yylval.label = yytext; return FOR;}

"if"		{yylval.label = yytext; return IF;}
"else"		{yylval.label = yytext; return ELSE;}

"print"		{yylval.label = yytext; return PRINT;}
"imput"		{yylval.label = yytext; return IMPUT;}

"++"		{yylval.label = "1"; return MAISUNARIO;}
"--"		{yylval.label = "1"; return MENOSUNARIO;}
"+="		{yylval.label =  yytext; return SUGARADD;}
"-="		{yylval.label =  yytext; return SUGARSUB;}
"*="		{yylval.label =  yytext; return SUGARMUL;}
"/="		{yylval.label =  yytext; return SUGARDIV;}

[(){}[\];,]	{ return *yytext; }

[+\-*/]		{ return *yytext; }

[&|%]	{return *yytext; }

[<>!=]	{return *yytext; }

{NUM}		{ yylval.label = yytext; yylval.tipo = "int"; return TK_NUM; }
{ID}		{ yylval.nome_var = yytext; return TK_ID; }
{REAL}		{ yylval.label = yytext; yylval.tipo = "float"; return TK_FLOAT; }
{CHAR}      { yylval.label = yytext; yylval.tipo = "char"; return TK_CHAR; }
{STRING}	{ yylval.label = yytext; yylval.tipo = "String"; return TK_STRING; }
.			{ *yytext; }

%%

int yywrap(void){
    return 1;
}

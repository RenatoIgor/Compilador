%{
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <map>
#include <list>

#define YYSTYPE atributos

using namespace std;

struct atributos
{
	string label;
	string traducao;
	string tipo;
	string nome_var;
	string bloco_pertence;
};
typedef struct atributos Atributos;

typedef map<string, Atributos> MAPA;

struct contexto
{
	list<string> labels;
	string nome_bloco;
};

typedef struct contexto Contexto;

typedef map<string, Contexto> ESCOPO;

list<ESCOPO> pilhaDeMapas; //PILHA de MAPAS .... modificar MAPA* para MAPA
string variaveis; 
list<string> nome_var;//o correto seria nome_bloco ... preguiça de mudar

MAPA mapa_temp; //MAPA DE TEMPORARIAS
MAPA mapa_temp2;// Só usar para na funcao declaracoes;
ESCOPO mapa_escopo;// MAPA DE ESCOPOS DAS TEMPORARIAS

int linha = 1;
int bloco = 0;
int yylex(void);
void yyerror(string);

string gerarNome(){
	static int numeroVariaveis = 0;
	numeroVariaveis++;
	ostringstream stringNumeroVariaveis;
	stringNumeroVariaveis << numeroVariaveis;
	return "temp_" + stringNumeroVariaveis.str();
}

string num_linha(){

	ostringstream NumLinhas;
	NumLinhas << linha;
	return "Linha: "+ NumLinhas.str();
}

string num_bloco(){

	ostringstream NumBloco;
	NumBloco << bloco;
	return "Bloco_"+NumBloco.str();
}

string gerarRotulo(){
	static int numeroRotulos = 0;
	numeroRotulos++;
	ostringstream stringNumeroVariaveis;
	stringNumeroVariaveis << numeroRotulos;
	return "rotulo_" + stringNumeroVariaveis.str();
}


string buscaMapaTemp(string label){// BUSCA NO MAPA DE TEMPORARIAS

	MAPA::iterator i;

	string aux = label;
	for(i = mapa_temp.begin(); i != mapa_temp.end(); i++){
		if(i->second.nome_var == label)
			aux = i->first;

	}

	return aux;	
}

string conversaoImplicita(atributos E1, atributos E2, string operador, atributos *$$){
	
	
	if((E1.tipo == "bool" || E2.tipo == "bool") && operador != "&&" && operador != "||")
		{	
			yyerror("Error: Operação invalida! " + num_linha());
		}
	else if((E1.tipo == "bool")^(E2.tipo == "bool"))
	{		
			yyerror("Error: Operação invalida! " + num_linha());
	}
	
	if(operador == "+" || operador == "-" || operador == "*" || operador == "/")
	{	
		
		if(E1.tipo == E2.tipo)
		{
				string tempLabelResultado = gerarNome();
				$$->label = tempLabelResultado;
				mapa_temp[$$->label].label = $$->label;
				mapa_temp[$$->label].tipo = $$->tipo;
				return "\t" + tempLabelResultado + " = " + E1.label + " " + operador + " " + E2.label + ";\n";
		}else
		{
			if(E1.tipo == "int")
			{	if(E2.tipo == "float"){
					string tempCastVarLabel = gerarNome();
					string builder = "\t" + tempCastVarLabel + " = " + "(" + E2.tipo + ")" + E1.label + ";\n";
					E1.label = tempCastVarLabel;
					mapa_temp[tempCastVarLabel].label = E1.label;
					mapa_temp[tempCastVarLabel].tipo = E2.tipo;
					string tempLabelResultado = gerarNome();
					$$->label = tempLabelResultado;
					$$->tipo = "float";
					mapa_temp[$$->label].label = $$->label;
					mapa_temp[$$->label].tipo = $$->tipo;
					return builder + "\t" + tempLabelResultado + " = " + E1.label + " " + operador + " " + E2.label + ";\n";
				}

				if(E2.tipo == "char"){
					string tempCastVarLabel = gerarNome();
					string builder = "\t" + tempCastVarLabel + " = " + "(" + E1.tipo + ")" + E2.label + ";\n";
					E1.label = tempCastVarLabel;
					mapa_temp[tempCastVarLabel].label = E2.label;
					mapa_temp[tempCastVarLabel].tipo = E1.tipo;
					string tempLabelResultado = gerarNome();
					$$->label = tempLabelResultado;
					$$->tipo = "int";
					mapa_temp[$$->label].label = $$->label;
					mapa_temp[$$->label].tipo = $$->tipo;
					return builder + "\t" + tempLabelResultado + " = " + E1.label + " " + operador + " " + E2.label + ";\n";
				}

				if(E2.tipo == "bool"){
					string tempCastVarLabel = gerarNome();
					string builder = "\t" + tempCastVarLabel + " = " + "(" + E1.tipo + ")" + E2.label + ";\n";
					E1.label = tempCastVarLabel;
					mapa_temp[tempCastVarLabel].label = E2.label;
					mapa_temp[tempCastVarLabel].tipo = E1.tipo;
					string tempLabelResultado = gerarNome();
					$$->label = tempLabelResultado;
					$$->tipo = "int";
					mapa_temp[$$->label].label = $$->label;
					mapa_temp[$$->label].tipo = $$->tipo;
					return builder + "\t" + tempLabelResultado + " = " + E1.label + " " + operador + " " + E2.label + ";\n";
				}

				if(E2.tipo ==  "String"){
				
					yyerror("Error: Conversao invalida! " + num_linha());
				
				}
			}
			if(E1.tipo == "float")
			{
				if(E2.tipo == "int"){
					string tempCastVarLabel = gerarNome();
					string builder = "\t" + tempCastVarLabel + " = " + "(" + E2.tipo + ")" + E1.label + ";\n";
					E1.label = tempCastVarLabel;
					mapa_temp[tempCastVarLabel].label = E1.label;
					mapa_temp[tempCastVarLabel].tipo = E2.tipo;
					string tempLabelResultado = gerarNome();
					$$->label = tempLabelResultado;
					$$->tipo = "float";
					mapa_temp[$$->label].label = $$->label;
					mapa_temp[$$->label].tipo = $$->tipo;
					return builder + "\t" + tempLabelResultado + " = " + E1.label + " " + operador + " " + E2.label + ";\n";
				}

				if(E2.tipo == "String"){
					yyerror("Error: Conversao invalida! " + num_linha());
				}
			}

			if(E1.tipo == "char")
			{
				if(E2.tipo == "int"){
					string tempCastVarLabel = gerarNome();
					string builder = "\t" + tempCastVarLabel + " = " + "(" + E2.tipo + ")" + E1.label + ";\n";
					E1.label = tempCastVarLabel;
					mapa_temp[tempCastVarLabel].label = E1.label;
					mapa_temp[tempCastVarLabel].tipo = E2.tipo;
					string tempLabelResultado = gerarNome();
					$$->label = tempLabelResultado;
					$$->tipo = "int";
					mapa_temp[$$->label].label = $$->label;
					mapa_temp[$$->label].tipo = $$->tipo;
					return builder + "\t" + tempLabelResultado + " = " + E1.label + " " + operador + " " + E2.label + ";\n";
				}
			}
			
			if(E1.tipo == "String")
			{
				yyerror("Error: Operação invalida! " + num_linha());
			}
		}
	}else if(operador == "<" || operador == ">" || operador == ">=" || operador == "<=" || operador == "==" || operador == "!=" || operador == "&&" || operador == "||")
	{
		$$->tipo = "bool";
		if(E1.tipo == E2.tipo)
		{
				string tempLabelResultado = gerarNome();
				$$->label = tempLabelResultado;
				mapa_temp[$$->label].label = $$->label;
				mapa_temp[$$->label].tipo = "int";
				return "\t" + tempLabelResultado + " = " + E1.label + " " + operador + " " + E2.label + ";\n";
		}else if(E1.tipo != E2.tipo){
			if(E1.tipo == "int" && E2.tipo != "bool")
			{
				string tempCastVarLabel = gerarNome();
				string builder = "\t" + tempCastVarLabel + " = " + "(" + E2.tipo + ")" + E1.label + ";\n";
				E1.label = tempCastVarLabel;
				mapa_temp[tempCastVarLabel].label = E1.label;
				mapa_temp[tempCastVarLabel].tipo = E2.tipo;
				string tempLabelResultado = gerarNome();
				$$->label = tempLabelResultado;
				mapa_temp[$$->label].label = $$->label;
				mapa_temp[$$->label].tipo = "int";
				return builder + "\t" + tempLabelResultado + " = " + E1.label + " " + operador + " " + E2.label + ";\n";
			}else if(E1.tipo == "float" && E2.tipo != "bool")
			{
				string tempCastVarLabel = gerarNome();
				string builder = "\t" + tempCastVarLabel + " = " + "(" + E1.tipo + ")" + E2.label + ";\n";
				E2.label = tempCastVarLabel;
				mapa_temp[tempCastVarLabel].label = E2.label;
				mapa_temp[tempCastVarLabel].tipo = E1.tipo;
				string tempLabelResultado = gerarNome();
				$$->label = tempLabelResultado;
				mapa_temp[$$->label].label = $$->label;
				mapa_temp[$$->label].tipo = "int";
				return builder + "\t" + tempLabelResultado + " = " + E1.label + " " + operador + " " + E2.label + ";\n";
			}
		}
	}
	return " ";
}

string declaracoes(){


	MAPA::iterator i;
	stringstream s;


	for(i = mapa_temp2.begin(); i != mapa_temp2.end(); i++){
		if(i->second.tipo == "bool"){
			i->second.tipo = "int";
		}
			
		s << i->second.tipo << " " << i->second.label << ";\n\t";
	}
	
	variaveis += "\t" + s.str()  + "\n";
	return variaveis;
}
%}

%token WHILE FOR IF ELSE
%token TK_NUM TK_FLOAT TK_CHAR TK_STRING TK_BOOL
%token TK_MAIN TK_ID TK_TIPO
%token TK_FIM TK_ERROR PRINT IMPUT
%token TK_CAST

%start START
%left '='
%left "||" "&&"
%left "==" "!="
%left '<' '>' ">=" "<="
%left '+' '-'
%left '*' '/'
%left MAISUNARIO MENOSUNARIO SUGARADD SUGARSUB SUGARMUL SUGARDIV
%%


START			: ESCOPO_GLOBAL MAIN
				{ 
					cout << "\n*Compilador DOIT* \n#include<string.h>\n#include<iostream>\n#include<stdio.h>\n" << endl;
					
					cout <<  $2.traducao  << endl;
				}


				;
MAIN			: TK_TIPO TK_MAIN  '(' ')' BLOCO 
				{
					$$.traducao = "int main(void)\n{\n" + declaracoes() + $5.traducao + "\treturn 0;\n}\n\n"; 
				}
				;
ESCOPO_GLOBAL	:
				{
					
					//pilhaDeMapas.push_front(mapa_escopo);
				} 
				;
INICIO_ESCOPO	: '{'
				{	bloco = bloco + 1;
					string s = num_bloco();
	
				//	mapa_escopo[s].nome_bloco = s;
					nome_var.push_front(s);
				//	ESCOPO mapadeEscopo;
				//	mapadeEscopo[s].nome_bloco = s;
					//pilhaDeMapas.push_front(mapadeEscopo);
					$$.traducao = "";

				
				}
				;
FIM_ESCOPO		: '}'
				{	

					ESCOPO::iterator it;
					
					it = mapa_escopo.find(nome_var.front());
					
					MAPA::iterator i;

					list<string>::iterator aux  = it->second.labels.begin();
					
					for(aux = it->second.labels.begin(); aux != it->second.labels.end() ; aux++)
					{
						i = mapa_temp.find(*aux);
						mapa_temp.erase(i);
					}


					mapa_escopo.erase(it);
					
					nome_var.pop_front();
					pilhaDeMapas.pop_front();
					$$.traducao = "";

				}
				;
BLOCO			: INICIO_ESCOPO COMANDOS FIM_ESCOPO
				{
					$$.traducao = $2.traducao;
		

				}
		
				;
COMANDOS		:COMANDO COMANDOS
				{ 
					$$.label = $1.label + $2.label;
					$$.traducao = $1.traducao + $2.traducao;
				}
				|

				;
COMANDO 	 	: E ';'
				| DECLARACAO ';'
				| ATRIBUICAO ';' 
				| LOOPS
				| CONDICAO
				| ENTRADA ';'
				| SAIDA ';'
				|//opcional. se retirar, os blocos deverao ser preenchidos
				;


LOOPS:			WHILE '(' COMPARACAO ')' '{' COMANDOS '}'//mudar expressao para comparar
				{

					string rotulo_inicio = gerarRotulo();
					string rotulo_fim = gerarRotulo();
	
					$$.traducao = "\t" + rotulo_inicio + ":\n"+ $3.traducao +"\tif(!" +$3.label + ") goto " +rotulo_fim+"\n"
					+ $6.traducao + "\tgoto " + rotulo_inicio + "\n\t"+ rotulo_fim +":\n";

				} 	

				|FOR '(' ATRIBUICAO ';' COMPARACAO ';' ATRIBUICAO')' '{' COMANDOS '}'{

					string rotulo_inicio = gerarRotulo();
					string rotulo_fim = gerarRotulo();

					$$.traducao = $3.traducao + "\t" + rotulo_inicio + ":\n"+ $5.traducao +"\tif(!" +$5.label + ") goto " +rotulo_fim+"\n"
				 	+ $10.traducao + $7.traducao + "\tgoto " + rotulo_inicio + "\n\t"+ rotulo_fim +":\n";

				}
				|FOR '('  ';' COMPARACAO ';' ATRIBUICAO')' '{' COMANDOS '}'{

					string rotulo_inicio = gerarRotulo();
					string rotulo_fim = gerarRotulo();

					$$.traducao = "\t" + rotulo_inicio + ":\n"+ $4.traducao +"\tif(!" +$4.label + ") goto " +rotulo_fim+"\n"
				 	+ $9.traducao + $6.traducao + "\tgoto " + rotulo_inicio + "\n\t"+ rotulo_fim +":\n";
				}

				|FOR '('  ';' COMPARACAO ';' ')' '{' COMANDOS '}'{

					string rotulo_inicio = gerarRotulo();
					string rotulo_fim = gerarRotulo();

					$$.traducao = "\t" + rotulo_inicio + ":\n"+ $4.traducao +"\tif(!" +$4.label + ") goto " +rotulo_fim+"\n"
				 	+ $8.traducao  + "\tgoto " + rotulo_inicio + "\n\t"+ rotulo_fim +":\n";
				}

				;

CONDICAO:	    IF '(' COMPARACAO ')' BLOCO 
				{
					
					string rotulo_inicio = gerarRotulo();
					string rotulo_fim = gerarRotulo();
					$$.traducao = $3.traducao + "\tif(!" + $3.label + ") goto " + rotulo_inicio + ";\n"
					+ $5.traducao + "\t" + rotulo_inicio + ":\n";
				}

				| IF '(' COMPARACAO ')' BLOCO ELSE BLOCO
				{
					string rotulo_inicio = gerarRotulo();
					string rotulo_fim = gerarRotulo();
					$$.traducao = $3.traducao   + "\tif(!"  + $3.label  + ") goto " + rotulo_fim  + "\n"  +  $5.traducao  + 
					"\tgoto "  + rotulo_inicio  +  ":\n\telse  " + rotulo_fim  + ":\n"  + $7.traducao  + "\t" + rotulo_inicio +":\n" ;	
				}

				;				

DECLARACAO 		: TK_TIPO TK_ID
				{
					

					$$.label = gerarNome();
					$$.tipo = $1.label;
					string b = num_bloco();
					MAPA::iterator it;

					for(it = mapa_temp.begin(); it != mapa_temp.end(); it++){

						if(it->second.nome_var == $2.nome_var && it->second.bloco_pertence == b)
						{
							yyerror("Atribuicao ja existentente! " );
						}
					}

					mapa_temp[$$.label].label = $$.label;
					mapa_temp[$$.label].tipo = $$.tipo;
					mapa_temp[$$.label].nome_var = $2.nome_var;
					mapa_temp[$$.label].bloco_pertence = b;

					mapa_temp2[$$.label].label = $$.label;
					mapa_temp2[$$.label].tipo = $$.tipo;
					mapa_temp2[$$.label].nome_var = $2.nome_var;
					mapa_temp2[$$.label].bloco_pertence = b;

					mapa_escopo[b].labels.push_front($$.label);
					mapa_escopo[b].nome_bloco = b;

					
					pilhaDeMapas.push_front(mapa_escopo);


				} 

				| DECLARACAO ',' TK_ID{
					$$.label = gerarNome();
					$$.tipo = $1.tipo;
					string b = num_bloco();
					MAPA::iterator it;

					for(it = mapa_temp.begin(); it != mapa_temp.end(); it++){

						if(it->second.nome_var == $3.nome_var && it->second.bloco_pertence == b)
						{
							yyerror("Atribuicao ja existentente! " );
						}
					}

					mapa_temp[$$.label].label = $$.label;
					mapa_temp[$$.label].tipo = $$.tipo;
					mapa_temp[$$.label].nome_var = $3.nome_var;
					mapa_temp[$$.label].bloco_pertence = num_bloco();

					mapa_temp2[$$.label].label = $$.label;
					mapa_temp2[$$.label].tipo = $$.tipo;
					mapa_temp2[$$.label].nome_var = $2.nome_var;
					mapa_temp2[$$.label].bloco_pertence = b;

					mapa_escopo[b].labels.push_front($$.label);
					mapa_escopo[b].nome_bloco = b;


					pilhaDeMapas.push_front(mapa_escopo);
				} 	

				;
ATRIBUICAO      :TK_ID '=' E 
				{
					string aux = $1.nome_var;
					string msn = buscaMapaTemp($1.nome_var);
					$1 = mapa_temp[msn];
					
					int existe = 0;

					list<string>::iterator i;

					for(i = nome_var.begin(); i != nome_var.end(); i++){

						if($1.bloco_pertence == *i)
						{
							existe = 1;
							break;
						}
					}


					if($1.tipo == "" || existe == 0)
					{
						msn = mapa_temp[msn].nome_var;	
						yyerror("Variavel " + aux + " não declarada! " );
			
					}

					if($1.tipo != $3.tipo)
					{


						string temp_cast = gerarNome();

						string temp_builder = "\t" + temp_cast + " = " + "(" + $1.tipo + ")" + $3.label + ";\n";

						mapa_temp[temp_cast].label = temp_cast;
						mapa_temp[temp_cast].tipo = $1.tipo;
						mapa_temp2[temp_cast].label = temp_cast;
						mapa_temp2[temp_cast].tipo = $1.tipo;

						$$.traducao = $1.traducao + $3.traducao + temp_builder +"\t" + $1.label + " = " + temp_cast + ";\n" ;


					}

					
					else
					{	

						
						$$.traducao = $1.traducao  + $3.traducao + "\t" + $1.label +  " = " + $3.label + ";\n";


					}				

					
				}

				| TK_ID '=' COMPARACAO{

					string msn = buscaMapaTemp($1.nome_var);
					$1 = mapa_temp[msn];
				

						
						if( $1.tipo != "bool")
						{
							
							yyerror("Atribuicao invalida! Linha: " );
				
						}

					if($1.tipo != $3.tipo)
					{


						string temp_cast = gerarNome();

						string temp_builder = "\t" + temp_cast + " = " + "(" + $1.tipo + ")" + $3.label + ";\n";

						mapa_temp[temp_cast].label = temp_cast;
						mapa_temp[temp_cast].tipo = $1.tipo;

						mapa_temp2[temp_cast].label = temp_cast;
						mapa_temp2[temp_cast].tipo = $1.tipo;

						$$.traducao = $1.traducao + $3.traducao + temp_builder +"\t" + $1.label + " = " + temp_cast + ";\n" ;


					}

					
					else
					{	

						
						$$.traducao = $1.traducao  + $3.traducao + "\t" + $1.label +  " = " + $3.label + ";\n";


					}				

					
				}
				| ATRIBUICAO ',' ATRIBUICAO{
					$$.traducao = $1.traducao + $3.traducao;
				}


				| TK_ID MAISUNARIO{ // EX: a++ 
				
					atributos valor1,valorVariavel;	

					string msn = buscaMapaTemp($1.nome_var);
					$1 = mapa_temp[msn];
				
					if($1.tipo == "")
					{
							
						yyerror("Variavel " + msn + " não declarada! " );
			
					}
						

									valor1.tipo = $1.tipo;
					if($1.tipo == "float"){
						valor1.label = "1.0";
					}	

					if($1.tipo == "int"){
						valor1.label = "1";
					}

					valorVariavel.label = gerarNome();
					mapa_temp[valorVariavel.label].label = valorVariavel.label;
					mapa_temp[valorVariavel.label].tipo = $1.tipo;

					mapa_temp2[valorVariavel.label].label = valorVariavel.label;
					mapa_temp2[valorVariavel.label].tipo = $1.tipo;

					valor1.label = gerarNome();
					mapa_temp[valor1.label].label = valor1.label;
					mapa_temp[valor1.label].tipo = $1.tipo;

					mapa_temp2[valor1.label].label = valor1.label;
					mapa_temp2[valor1.label].tipo = $1.tipo;


					string tempLabelResultado = gerarNome();
		
					mapa_temp[tempLabelResultado].label = tempLabelResultado;
					mapa_temp[tempLabelResultado].tipo = $1.tipo;

					mapa_temp2[tempLabelResultado].label = tempLabelResultado;
					mapa_temp2[tempLabelResultado].tipo = $1.tipo;
					$$.traducao =  "\t" + valorVariavel.label + " = " + $1.label + ";\n\t"+
					valor1.label + " = " + "1" + ";\n\t" + tempLabelResultado + " = " + valorVariavel.label + " + "  + valor1.label + ";\n\t"+
					$1.label + " = " + tempLabelResultado + ";\n";

				}

				| TK_ID MENOSUNARIO{ // EX: a--
				
					atributos valor1,valorVariavel;	

					string msn = buscaMapaTemp($1.nome_var);
					$1 = mapa_temp[msn];
				
					if($1.tipo == "")
					{
							
						yyerror("Variavel " + msn + " não declarada! " );
			
					}
						

					valor1.tipo = $1.tipo;
					if($1.tipo == "float"){
						valor1.label = "1.0";
					}	

					if($1.tipo == "int"){
						valor1.label = "1";
					}

					valorVariavel.label = gerarNome();
					mapa_temp[valorVariavel.label].label = valorVariavel.label;
					mapa_temp[valorVariavel.label].tipo = $1.tipo;

					mapa_temp2[valorVariavel.label].label = valorVariavel.label;
					mapa_temp2[valorVariavel.label].tipo = $1.tipo;

					valor1.label = gerarNome();
					mapa_temp[valor1.label].label = valor1.label;
					mapa_temp[valor1.label].tipo = $1.tipo;

					mapa_temp2[valor1.label].label = valor1.label;
					mapa_temp2[valor1.label].tipo = $1.tipo;


					string tempLabelResultado = gerarNome();
		
					mapa_temp[tempLabelResultado].label = tempLabelResultado;
					mapa_temp[tempLabelResultado].tipo = $1.tipo;

					mapa_temp2[tempLabelResultado].label = tempLabelResultado;
					mapa_temp2[tempLabelResultado].tipo = $1.tipo;
					$$.traducao =  "\t" + valorVariavel.label + " = " + $1.label + ";\n\t"+
					valor1.label + " = " + "1" + ";\n\t" + tempLabelResultado + " = " + valorVariavel.label + " - "  + valor1.label + ";\n\t"+
					$1.label + " = " + tempLabelResultado + ";\n";

				}

				| TK_ID SUGARADD E	// a += expressao	
				{
					string aux = $1.nome_var;
					string msn = buscaMapaTemp($1.nome_var);
					$1 = mapa_temp[msn];
					
					int existe = 0;

					list<string>::iterator i;

					for(i = nome_var.begin(); i != nome_var.end(); i++){

						if($1.bloco_pertence == *i)
						{
							existe = 1;
							break;
						}
					}


					if($1.tipo == "" || existe == 0)
					{
						msn = mapa_temp[msn].nome_var;	
						yyerror("Variavel " + aux + " não declarada! " );
			
					}

					if($1.tipo != $3.tipo)
					{


						string temp_cast = gerarNome();

						string temp_builder = "\t" + temp_cast + " = " + "(" + $1.tipo + ")" + $3.label + ";\n";

						mapa_temp[temp_cast].label = temp_cast;
						mapa_temp[temp_cast].tipo = $1.tipo;
						mapa_temp2[temp_cast].label = temp_cast;
						mapa_temp2[temp_cast].tipo = $1.tipo;

						$$.traducao = $1.traducao + $3.traducao + temp_builder +"\t" + $1.label + " = " + temp_cast + ";\n" ;


					}

					
					else
					{	

						Atributos x;
						x = $1;
						x.label = gerarNome();
						$$.traducao = $1.traducao + $3.traducao + "\t"+x.label + " = " + $1.label + "\n"+ 
						conversaoImplicita(x, $3, "+", &$$) + "\t" + $1.label + " = " + $$.label +";\n" ;


					}				

					
				}		
				

				| TK_ID SUGARSUB E	// a -= expressao	
				{
					string aux = $1.nome_var;
					string msn = buscaMapaTemp($1.nome_var);
					$1 = mapa_temp[msn];
					
					int existe = 0;

					list<string>::iterator i;

					for(i = nome_var.begin(); i != nome_var.end(); i++){

						if($1.bloco_pertence == *i)
						{
							existe = 1;
							break;
						}
					}


					if($1.tipo == "" || existe == 0)
					{
						msn = mapa_temp[msn].nome_var;	
						yyerror("Variavel " + aux + " não declarada! " );
			
					}

					if($1.tipo != $3.tipo)
					{


						string temp_cast = gerarNome();

						string temp_builder = "\t" + temp_cast + " = " + "(" + $1.tipo + ")" + $3.label + ";\n";

						mapa_temp[temp_cast].label = temp_cast;
						mapa_temp[temp_cast].tipo = $1.tipo;
						mapa_temp2[temp_cast].label = temp_cast;
						mapa_temp2[temp_cast].tipo = $1.tipo;

						$$.traducao = $1.traducao + $3.traducao + temp_builder +"\t" + $1.label + " = " + temp_cast + ";\n" ;


					}

					
					else
					{	

						Atributos x;
						x = $1;
						x.label = gerarNome();
						$$.traducao = $1.traducao + $3.traducao + "\t"+x.label + " = " + $1.label + "\n"+ 
						conversaoImplicita(x, $3, "-", &$$) + "\t" + $1.label + " = " + $$.label +";\n" ;


					}				

					
				}

				| TK_ID SUGARMUL E	// a *= expressao	
				{
					string aux = $1.nome_var;
					string msn = buscaMapaTemp($1.nome_var);
					$1 = mapa_temp[msn];
					
					int existe = 0;

					list<string>::iterator i;

					for(i = nome_var.begin(); i != nome_var.end(); i++){

						if($1.bloco_pertence == *i)
						{
							existe = 1;
							break;
						}
					}


					if($1.tipo == "" || existe == 0)
					{
						msn = mapa_temp[msn].nome_var;	
						yyerror("Variavel " + aux + " não declarada! " );
			
					}

					if($1.tipo != $3.tipo)
					{


						string temp_cast = gerarNome();

						string temp_builder = "\t" + temp_cast + " = " + "(" + $1.tipo + ")" + $3.label + ";\n";

						mapa_temp[temp_cast].label = temp_cast;
						mapa_temp[temp_cast].tipo = $1.tipo;
						mapa_temp2[temp_cast].label = temp_cast;
						mapa_temp2[temp_cast].tipo = $1.tipo;

						$$.traducao = $1.traducao + $3.traducao + temp_builder +"\t" + $1.label + " = " + temp_cast + ";\n" ;


					}

					
					else
					{	

						Atributos x;
						x = $1;
						x.label = gerarNome();
						$$.traducao = $1.traducao + $3.traducao + "\t"+x.label + " = " + $1.label + "\n"+ 
						conversaoImplicita(x, $3, "*", &$$) + "\t" + $1.label + " = " + $$.label +";\n" ;


					}				

					
				}	

				| TK_ID SUGARDIV E	// a /= expressao	
				{
					string aux = $1.nome_var;
					string msn = buscaMapaTemp($1.nome_var);
					$1 = mapa_temp[msn];
					
					int existe = 0;

					list<string>::iterator i;

					for(i = nome_var.begin(); i != nome_var.end(); i++){

						if($1.bloco_pertence == *i)
						{
							existe = 1;
							break;
						}
					}


					if($1.tipo == "" || existe == 0)
					{
						msn = mapa_temp[msn].nome_var;	
						yyerror("Variavel " + aux + " não declarada! " );
			
					}

					if($1.tipo != $3.tipo)
					{


						string temp_cast = gerarNome();

						string temp_builder = "\t" + temp_cast + " = " + "(" + $1.tipo + ")" + $3.label + ";\n";

						mapa_temp[temp_cast].label = temp_cast;
						mapa_temp[temp_cast].tipo = $1.tipo;
						mapa_temp2[temp_cast].label = temp_cast;
						mapa_temp2[temp_cast].tipo = $1.tipo;

						$$.traducao = $1.traducao + $3.traducao + temp_builder +"\t" + $1.label + " = " + temp_cast + ";\n" ;


					}

					
					else
					{	

						Atributos x;
						x = $1;
						x.label = gerarNome();
						$$.traducao = $1.traducao + $3.traducao + "\t"+x.label + " = " + $1.label + "\n"+ 
						conversaoImplicita(x, $3, "/", &$$) + "\t" + $1.label + " = " + $$.label +";\n" ;


					}				

					
				}		

				;
E 				: '(' E ')'
				{
					$$ = $2;
				} 
				| E '+' E
				{
					$$.traducao = $1.traducao + $3.traducao + conversaoImplicita($1, $3, "+", &$$);
				}
				| E '-' E
				{
					$$.traducao = $1.traducao + $3.traducao + conversaoImplicita($1, $3, "-", &$$);
				}
				| E '*' E
				{
					$$.traducao = $1.traducao + $3.traducao + conversaoImplicita($1, $3, "*", &$$);
				}
				| E '/' E
				{	
					cout << "CUIDADO: Divisao po Zero! Linha " + num_linha();
					$$.traducao = $1.traducao + $3.traducao + conversaoImplicita($1, $3, "/", &$$);
				}

				| T
				{
					$$ = $1;
				};

ENTRADA			:TK_ID '=' IMPUT'(' F ')'	
				{
					string aux = $1.nome_var;
					string msn = buscaMapaTemp($1.nome_var);
					$1 = mapa_temp[msn];


					int existe = 0;

					list<string>::iterator i;

					for(i = nome_var.begin(); i != nome_var.end(); i++){

						if($1.bloco_pertence == *i)
						{
							existe = 1;
							break;
						}
					}


					if($1.tipo == "" || existe == 0)
					{
						msn = mapa_temp[msn].nome_var;	
						yyerror("Variavel " + aux + " não declarada! " );
			
					}

					if($1.tipo != $5.tipo)
					{


						string temp_cast = gerarNome();

						string temp_builder = "\t" + temp_cast + " = " + "(" + $1.tipo + ")" + $5.label + ";\n";

						mapa_temp[temp_cast].label = temp_cast;
						mapa_temp[temp_cast].tipo = $1.tipo;
						mapa_temp2[temp_cast].label = temp_cast;
						mapa_temp2[temp_cast].tipo = $1.tipo;

						$$.traducao = $1.traducao + $5.traducao + temp_builder +"\t" + $1.label + " = " + temp_cast + ";\n" ;


					}

					else
					{

						$$.traducao = $1.traducao + $5.traducao + "\n\tcout << " + $5.label + ";\n\t"
						+ "cin >> " + $1.label + ";\n\t";
					}
				}
				|TK_ID '=' IMPUT'(' ')'
				{
					string aux = $1.nome_var;
					string msn = buscaMapaTemp($1.nome_var);
					$1 = mapa_temp[msn];


					int existe = 0;

					list<string>::iterator i;

					for(i = nome_var.begin(); i != nome_var.end(); i++){

						if($1.bloco_pertence == *i)
						{
							existe = 1;
							break;
						}
					}


					if($1.tipo == "" || existe == 0)
					{
						msn = mapa_temp[msn].nome_var;	
						yyerror("Variavel " + aux + " não declarada! " );
			
					}



						$$.traducao = $1.traducao + $5.traducao + "\n\t"
						+ "cin >> " + $1.label + ";\n\t";
			
				}


				;

SAIDA			:PRINT'(' F ')'
				{
					$$.traducao = $3.traducao + "\n\tcout << " +$3.label + ";\n\t" ;
				};			
			
COMPARACAO:		E '>' E
				{
					$$.traducao = $1.traducao + $3.traducao + conversaoImplicita($1, $3, ">", &$$);
				}
				| E '<' E
				{
					$$.traducao = $1.traducao + $3.traducao + conversaoImplicita($1, $3, "<", &$$);
				}
				| E '>' '=' E
				{
					$$.traducao = $1.traducao + $4.traducao + conversaoImplicita($1, $4, ">=", &$$);
				}
				| E '<' '=' E
				{
					$$.traducao = $1.traducao + $4.traducao + conversaoImplicita($1, $4, "<=", &$$);
				}
				| E '=' '=' E
				{
					$$.traducao = $1.traducao + $4.traducao + conversaoImplicita($1, $4, "==", &$$);
				}
				| E '!' '=' E
				{
					$$.traducao = $1.traducao + $4.traducao + conversaoImplicita($1, $4, "!=", &$$);
				}
				| E '&' '&' E
				{
					$$.traducao = $1.traducao + $4.traducao + conversaoImplicita($1, $4, "&&", &$$);
				}
				| E '|' '|' E
				{
					$$.traducao = $1.traducao + $4.traducao + conversaoImplicita($1, $4, "||", &$$);
				}
				| E '%' '%' E
				{
					string tempNome = gerarNome();
					string tempNome2 = gerarNome();
					$$.traducao = $1.traducao + $4.traducao + "\t" + tempNome + " = " + $1.label + " * " + $4.label + ";\n" + "\t" + tempNome2 + " = " + tempNome + " / 100;\n";
					$$.label = tempNome2;
				}
				;
	
T 				: C F
				{
					$$ = $2;
					$$.label = gerarNome();
				
					mapa_temp[$$.label].label = $$.label;
					mapa_temp[$$.label].tipo = $$.tipo;

					mapa_temp2[$$.label].label = $$.label;
					mapa_temp2[$$.label].tipo = $$.tipo;
					if($1.label == "(float)"){
						$$.traducao = "\tfloat " + $$.label + " = " + $2.label + ";\n";
						$$.tipo = "float";
					}else if($1.label == "(int)"){
						$$.traducao = "\t" + $$.label + " = " + $2.label + ";\n";
						$$.tipo = "int";
					}else{
						$$.traducao = "\t" + $$.label + " = " + $2.label + ";\n";
					}
				}
				| '-' F
				{
					$$ = $2;
					$$.label = gerarNome();
					mapa_temp[$$.label].label = $$.label;
					mapa_temp[$$.label].tipo = $$.tipo;

					mapa_temp2[$$.label].label = $$.label;
					mapa_temp2[$$.label].tipo = $$.tipo;
					$$.traducao = $2.traducao + "\t"  + $$.label + " = -" + $2.label + ";\n";
					
				}
				| '+' F
				{
					$$ = $2;
					$$.label = gerarNome();
					mapa_temp[$$.label].label = $$.label;
					mapa_temp[$$.label].tipo = $$.tipo;

					mapa_temp2[$$.label].label = $$.label;
					mapa_temp2[$$.label].tipo = $$.tipo;
					$$.traducao = $2.traducao + "\t" + $$.label + " = " + $2.label + ";\n";
				}
				;

F 		  		: TK_NUM
				{
					$$ = $1;
				}
				| TK_FLOAT
				{
					$$ = $1;
				}
				| TK_ID
				{
					
					string msn = buscaMapaTemp($1.nome_var);
					$1 = mapa_temp[msn];
				
						
						if($1.tipo == "")
						{
							
							yyerror("Variavel " + msn + " não declarada!  " );
				
						}

					$$ = $1;	


				}
				| TK_CHAR
				{
					$$ = $1;
				}
				| TK_BOOL
				{
					$$ = $1;
					$$.traducao = $$.label;
				}
				| TK_STRING
				{
					$$ = $1;
				}
				;
C 				: TK_CAST
				{
					$$ = $1;
				}
				|
				;
%%

#include "lex.yy.c"
int yyparse();
int main( int argc, char* argv[] )
{
	yyparse();
	return 0;
}
void yyerror( string MSG )
{
	extern char * yytext;
	cout << "ERRO: " << MSG << num_linha() <<endl;
	exit (0);
}

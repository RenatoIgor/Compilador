/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "sintatica.y" /* yacc.c:339  */

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

#line 336 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    WHILE = 258,
    FOR = 259,
    IF = 260,
    ELSE = 261,
    TK_NUM = 262,
    TK_FLOAT = 263,
    TK_CHAR = 264,
    TK_STRING = 265,
    TK_BOOL = 266,
    TK_MAIN = 267,
    TK_ID = 268,
    TK_TIPO = 269,
    TK_FIM = 270,
    TK_ERROR = 271,
    PRINT = 272,
    IMPUT = 273,
    TK_CAST = 274,
    MAISUNARIO = 281,
    MENOSUNARIO = 282,
    SUGARADD = 283,
    SUGARSUB = 284,
    SUGARMUL = 285,
    SUGARDIV = 286
  };
#endif
/* Tokens.  */
#define WHILE 258
#define FOR 259
#define IF 260
#define ELSE 261
#define TK_NUM 262
#define TK_FLOAT 263
#define TK_CHAR 264
#define TK_STRING 265
#define TK_BOOL 266
#define TK_MAIN 267
#define TK_ID 268
#define TK_TIPO 269
#define TK_FIM 270
#define TK_ERROR 271
#define PRINT 272
#define IMPUT 273
#define TK_CAST 274
#define MAISUNARIO 281
#define MENOSUNARIO 282
#define SUGARADD 283
#define SUGARSUB 284
#define SUGARMUL 285
#define SUGARDIV 286

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 437 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   181

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  146

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,     2,     2,    48,    46,     2,
      39,    40,    31,    29,    44,    30,     2,    32,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    43,
      25,    20,    26,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,    47,    42,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    21,    22,    23,    24,    27,
      28,    33,    34,    35,    36,    37,    38
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   288,   288,   297,   303,   308,   322,   348,   356,   361,
     364,   365,   366,   367,   368,   369,   370,   371,   375,   386,
     395,   404,   415,   424,   434,   470,   502,   560,   605,   610,
     662,   714,   776,   837,   898,   960,   964,   968,   972,   976,
     982,   987,  1040,  1078,  1083,  1087,  1091,  1095,  1099,  1103,
    1107,  1111,  1115,  1124,  1144,  1156,  1169,  1173,  1177,  1195,
    1199,  1204,  1209,  1213
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WHILE", "FOR", "IF", "ELSE", "TK_NUM",
  "TK_FLOAT", "TK_CHAR", "TK_STRING", "TK_BOOL", "TK_MAIN", "TK_ID",
  "TK_TIPO", "TK_FIM", "TK_ERROR", "PRINT", "IMPUT", "TK_CAST", "'='",
  "\"||\"", "\"&&\"", "\"==\"", "\"!=\"", "'<'", "'>'", "\">=\"", "\"<=\"",
  "'+'", "'-'", "'*'", "'/'", "MAISUNARIO", "MENOSUNARIO", "SUGARADD",
  "SUGARSUB", "SUGARMUL", "SUGARDIV", "'('", "')'", "'{'", "'}'", "';'",
  "','", "'!'", "'&'", "'|'", "'%'", "$accept", "START", "MAIN",
  "ESCOPO_GLOBAL", "INICIO_ESCOPO", "FIM_ESCOPO", "BLOCO", "COMANDOS",
  "COMANDO", "LOOPS", "CONDICAO", "DECLARACAO", "ATRIBUICAO", "E",
  "ENTRADA", "SAIDA", "COMPARACAO", "T", "F", "C", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
      61,   275,   276,   277,   278,    60,    62,   279,   280,    43,
      45,    42,    47,   281,   282,   283,   284,   285,   286,    40,
      41,   123,   125,    59,    44,    33,    38,   124,    37
};
# endif

#define YYPACT_NINF -83

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-83)))

#define YYTABLE_NINF -10

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -83,    14,     6,   -83,    16,   -83,   -13,     7,    17,   -83,
      46,   -83,    22,    25,    45,    -4,    42,    72,   -83,   144,
     144,    23,    36,    46,   -83,   -83,    -8,    28,    69,    75,
      86,   -83,   144,    23,    -3,    23,    38,   -83,   -83,    23,
      23,    23,    23,   -83,   144,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,   -83,   118,   -83,   -83,   -83,   -83,   124,   -83,
     125,    23,    23,    23,    23,   -83,   -83,   -83,   -83,    77,
      99,   108,    23,    61,   116,   120,    77,   -83,   103,   103,
     103,   103,   121,   -83,   -83,   119,    82,    82,   -83,   -83,
     140,    97,   101,   142,   122,   117,   123,   126,    23,   127,
      23,    17,    -2,   -83,    23,    23,   103,    23,   103,    23,
      23,    23,    23,    46,    -1,   129,   159,   -83,   133,   103,
     103,   103,   103,   103,   103,   103,   132,   128,    26,   125,
      17,   -83,   -83,    46,   134,    39,   -83,   135,    46,   137,
     -83,   138,    46,   -83,   139,   -83
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     1,     0,     2,     0,     0,     0,     5,
      17,     3,     0,     0,     0,     0,     0,     0,    62,     0,
       0,    63,     0,    17,    13,    14,     0,     0,     0,     0,
       0,    40,     0,    63,     0,    63,    63,    29,    30,    63,
      63,    63,    63,    24,     0,    56,    57,    59,    61,    60,
      58,    55,    54,     0,     6,     7,     8,    11,     0,    12,
       0,    63,    63,    63,    63,    10,    15,    16,    53,     0,
       0,     0,    63,     0,     0,     0,    26,    27,    31,    32,
      33,    34,     0,    35,    25,    28,    36,    37,    38,    39,
       0,    63,    63,     0,     0,     0,     0,     0,    63,     0,
      63,     0,     0,    43,    63,    63,    45,    63,    44,    63,
      63,    63,    63,    17,     0,     0,    22,    42,     0,    48,
      47,    46,    49,    50,    51,    52,     0,     0,     0,     0,
       0,    41,    18,    17,     0,     0,    23,     0,    17,     0,
      21,     0,    17,    20,     0,    19
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -83,   -83,   -83,   -83,   -83,   -83,   -82,   -23,   -83,   -83,
     -83,   -83,   -33,   -18,   -83,   -83,   -31,   -83,    -7,   -83
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     5,     2,    10,    55,    11,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    77,    31,    51,    32
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      56,    73,    70,    53,    74,    45,    46,    47,    48,    49,
      71,    50,    71,    52,     3,    69,    36,    69,    76,   116,
       4,    78,    79,    80,    81,    68,     7,    85,     6,    37,
      38,    39,    40,    41,    42,    57,    58,    82,   117,   127,
      72,    99,    18,    86,    87,    88,    89,     8,   136,    12,
      13,    14,    19,    20,    69,    43,    75,    18,     9,    15,
      16,    33,    21,    17,    34,    18,   134,    19,    20,   115,
      60,    59,    60,   106,   108,    19,    20,    21,    54,   139,
      76,   128,    69,    60,    35,    21,   119,   120,    -9,   121,
     126,   122,   123,   124,   125,   118,   135,    90,    61,    62,
      63,    64,    91,    92,   100,    60,    61,    62,    63,    64,
     137,    44,    65,    63,    64,   141,    18,   105,    66,   144,
      18,   107,    93,    94,    95,    96,    19,    20,    98,    67,
      19,    20,    61,    62,    63,    64,    21,    84,    71,    97,
      21,    37,    38,    39,    40,    41,    42,    61,    62,    63,
      64,    45,    46,    47,    48,    49,   101,    50,    83,   102,
     104,   103,   109,    60,   111,   130,     0,   113,   110,   133,
     114,   112,   129,   131,   132,   138,     0,   140,   142,     0,
     143,   145
};

static const yytype_int16 yycheck[] =
{
      23,    34,    33,    21,    35,     7,     8,     9,    10,    11,
      13,    13,    13,    20,     0,    33,    20,    35,    36,   101,
      14,    39,    40,    41,    42,    32,    39,    60,    12,    33,
      34,    35,    36,    37,    38,    43,    44,    44,    40,    40,
      43,    72,    19,    61,    62,    63,    64,    40,   130,     3,
       4,     5,    29,    30,    72,    13,    18,    19,    41,    13,
      14,    39,    39,    17,    39,    19,    40,    29,    30,   100,
      44,    43,    44,    91,    92,    29,    30,    39,    42,    40,
      98,   114,   100,    44,    39,    39,   104,   105,    42,   107,
     113,   109,   110,   111,   112,   102,   129,    20,    29,    30,
      31,    32,    25,    26,    43,    44,    29,    30,    31,    32,
     133,    39,    43,    31,    32,   138,    19,    20,    43,   142,
      19,    20,    45,    46,    47,    48,    29,    30,    20,    43,
      29,    30,    29,    30,    31,    32,    39,    13,    13,    40,
      39,    33,    34,    35,    36,    37,    38,    29,    30,    31,
      32,     7,     8,     9,    10,    11,    40,    13,    40,    39,
      20,    40,    20,    44,    47,     6,    -1,    41,    46,    41,
      43,    48,    43,    40,    42,    41,    -1,    42,    41,    -1,
      42,    42
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    50,    52,     0,    14,    51,    12,    39,    40,    41,
      53,    55,     3,     4,     5,    13,    14,    17,    19,    29,
      30,    39,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    66,    68,    39,    39,    39,    20,    33,    34,    35,
      36,    37,    38,    13,    39,     7,     8,     9,    10,    11,
      13,    67,    67,    62,    42,    54,    56,    43,    44,    43,
      44,    29,    30,    31,    32,    43,    43,    43,    67,    62,
      65,    13,    43,    61,    65,    18,    62,    65,    62,    62,
      62,    62,    67,    40,    13,    61,    62,    62,    62,    62,
      20,    25,    26,    45,    46,    47,    48,    40,    20,    65,
      43,    40,    39,    40,    20,    20,    62,    20,    62,    20,
      46,    47,    48,    41,    43,    65,    55,    40,    67,    62,
      62,    62,    62,    62,    62,    62,    56,    40,    61,    43,
       6,    40,    42,    41,    40,    61,    55,    56,    41,    40,
      42,    56,    41,    42,    56,    42
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    51,    52,    53,    54,    55,    56,    56,
      57,    57,    57,    57,    57,    57,    57,    57,    58,    58,
      58,    58,    59,    59,    60,    60,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    62,    62,    62,    62,    62,
      62,    63,    63,    64,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    66,    66,    66,    67,    67,    67,    67,
      67,    67,    68,    68
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     5,     0,     1,     1,     3,     2,     0,
       2,     2,     2,     1,     1,     2,     2,     0,     7,    11,
      10,     9,     5,     7,     2,     3,     3,     3,     3,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     6,     5,     4,     3,     3,     4,     4,     4,     4,
       4,     4,     4,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 289 "sintatica.y" /* yacc.c:1646  */
    { 
					cout << "\n*Compilador DOIT* \n#include<string.h>\n#include<iostream>\n#include<stdio.h>\n" << endl;
					
					cout <<  (yyvsp[0]).traducao  << endl;
				}
#line 1619 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 298 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).traducao = "int main(void)\n{\n" + declaracoes() + (yyvsp[0]).traducao + "\treturn 0;\n}\n\n"; 
				}
#line 1627 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 303 "sintatica.y" /* yacc.c:1646  */
    {
					
					//pilhaDeMapas.push_front(mapa_escopo);
				}
#line 1636 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 309 "sintatica.y" /* yacc.c:1646  */
    {	bloco = bloco + 1;
					string s = num_bloco();
	
				//	mapa_escopo[s].nome_bloco = s;
					nome_var.push_front(s);
				//	ESCOPO mapadeEscopo;
				//	mapadeEscopo[s].nome_bloco = s;
					//pilhaDeMapas.push_front(mapadeEscopo);
					(yyval).traducao = "";

				
				}
#line 1653 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 323 "sintatica.y" /* yacc.c:1646  */
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
					(yyval).traducao = "";

				}
#line 1682 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 349 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).traducao = (yyvsp[-1]).traducao;
		

				}
#line 1692 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 357 "sintatica.y" /* yacc.c:1646  */
    { 
					(yyval).label = (yyvsp[-1]).label + (yyvsp[0]).label;
					(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[0]).traducao;
				}
#line 1701 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 376 "sintatica.y" /* yacc.c:1646  */
    {

					string rotulo_inicio = gerarRotulo();
					string rotulo_fim = gerarRotulo();
	
					(yyval).traducao = "\t" + rotulo_inicio + ":\n"+ (yyvsp[-4]).traducao +"\tif(!" +(yyvsp[-4]).label + ") goto " +rotulo_fim+"\n"
					+ (yyvsp[-1]).traducao + "\tgoto " + rotulo_inicio + "\n\t"+ rotulo_fim +":\n";

				}
#line 1715 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 386 "sintatica.y" /* yacc.c:1646  */
    {

					string rotulo_inicio = gerarRotulo();
					string rotulo_fim = gerarRotulo();

					(yyval).traducao = (yyvsp[-8]).traducao + "\t" + rotulo_inicio + ":\n"+ (yyvsp[-6]).traducao +"\tif(!" +(yyvsp[-6]).label + ") goto " +rotulo_fim+"\n"
				 	+ (yyvsp[-1]).traducao + (yyvsp[-4]).traducao + "\tgoto " + rotulo_inicio + "\n\t"+ rotulo_fim +":\n";

				}
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 395 "sintatica.y" /* yacc.c:1646  */
    {

					string rotulo_inicio = gerarRotulo();
					string rotulo_fim = gerarRotulo();

					(yyval).traducao = "\t" + rotulo_inicio + ":\n"+ (yyvsp[-6]).traducao +"\tif(!" +(yyvsp[-6]).label + ") goto " +rotulo_fim+"\n"
				 	+ (yyvsp[-1]).traducao + (yyvsp[-4]).traducao + "\tgoto " + rotulo_inicio + "\n\t"+ rotulo_fim +":\n";
				}
#line 1742 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 404 "sintatica.y" /* yacc.c:1646  */
    {

					string rotulo_inicio = gerarRotulo();
					string rotulo_fim = gerarRotulo();

					(yyval).traducao = "\t" + rotulo_inicio + ":\n"+ (yyvsp[-5]).traducao +"\tif(!" +(yyvsp[-5]).label + ") goto " +rotulo_fim+"\n"
				 	+ (yyvsp[-1]).traducao  + "\tgoto " + rotulo_inicio + "\n\t"+ rotulo_fim +":\n";
				}
#line 1755 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 416 "sintatica.y" /* yacc.c:1646  */
    {
					
					string rotulo_inicio = gerarRotulo();
					string rotulo_fim = gerarRotulo();
					(yyval).traducao = (yyvsp[-2]).traducao + "\tif(!" + (yyvsp[-2]).label + ") goto " + rotulo_inicio + ";\n"
					+ (yyvsp[0]).traducao + "\t" + rotulo_inicio + ":\n";
				}
#line 1767 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 425 "sintatica.y" /* yacc.c:1646  */
    {
					string rotulo_inicio = gerarRotulo();
					string rotulo_fim = gerarRotulo();
					(yyval).traducao = (yyvsp[-4]).traducao   + "\tif(!"  + (yyvsp[-4]).label  + ") goto " + rotulo_fim  + "\n"  +  (yyvsp[-2]).traducao  + 
					"\tgoto "  + rotulo_inicio  +  ":\n\telse  " + rotulo_fim  + ":\n"  + (yyvsp[0]).traducao  + "\t" + rotulo_inicio +":\n" ;	
				}
#line 1778 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 435 "sintatica.y" /* yacc.c:1646  */
    {
					

					(yyval).label = gerarNome();
					(yyval).tipo = (yyvsp[-1]).label;
					string b = num_bloco();
					MAPA::iterator it;

					for(it = mapa_temp.begin(); it != mapa_temp.end(); it++){

						if(it->second.nome_var == (yyvsp[0]).nome_var && it->second.bloco_pertence == b)
						{
							yyerror("Atribuicao ja existentente! " );
						}
					}

					mapa_temp[(yyval).label].label = (yyval).label;
					mapa_temp[(yyval).label].tipo = (yyval).tipo;
					mapa_temp[(yyval).label].nome_var = (yyvsp[0]).nome_var;
					mapa_temp[(yyval).label].bloco_pertence = b;

					mapa_temp2[(yyval).label].label = (yyval).label;
					mapa_temp2[(yyval).label].tipo = (yyval).tipo;
					mapa_temp2[(yyval).label].nome_var = (yyvsp[0]).nome_var;
					mapa_temp2[(yyval).label].bloco_pertence = b;

					mapa_escopo[b].labels.push_front((yyval).label);
					mapa_escopo[b].nome_bloco = b;

					
					pilhaDeMapas.push_front(mapa_escopo);


				}
#line 1817 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 470 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).label = gerarNome();
					(yyval).tipo = (yyvsp[-2]).tipo;
					string b = num_bloco();
					MAPA::iterator it;

					for(it = mapa_temp.begin(); it != mapa_temp.end(); it++){

						if(it->second.nome_var == (yyvsp[0]).nome_var && it->second.bloco_pertence == b)
						{
							yyerror("Atribuicao ja existentente! " );
						}
					}

					mapa_temp[(yyval).label].label = (yyval).label;
					mapa_temp[(yyval).label].tipo = (yyval).tipo;
					mapa_temp[(yyval).label].nome_var = (yyvsp[0]).nome_var;
					mapa_temp[(yyval).label].bloco_pertence = num_bloco();

					mapa_temp2[(yyval).label].label = (yyval).label;
					mapa_temp2[(yyval).label].tipo = (yyval).tipo;
					mapa_temp2[(yyval).label].nome_var = (yyvsp[-1]).nome_var;
					mapa_temp2[(yyval).label].bloco_pertence = b;

					mapa_escopo[b].labels.push_front((yyval).label);
					mapa_escopo[b].nome_bloco = b;


					pilhaDeMapas.push_front(mapa_escopo);
				}
#line 1852 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 503 "sintatica.y" /* yacc.c:1646  */
    {
					string aux = (yyvsp[-2]).nome_var;
					string msn = buscaMapaTemp((yyvsp[-2]).nome_var);
					(yyvsp[-2]) = mapa_temp[msn];
					
					int existe = 0;

					list<string>::iterator i;

					for(i = nome_var.begin(); i != nome_var.end(); i++){

						if((yyvsp[-2]).bloco_pertence == *i)
						{
							existe = 1;
							break;
						}
					}


					if((yyvsp[-2]).tipo == "" || existe == 0)
					{
						msn = mapa_temp[msn].nome_var;	
						yyerror("Variavel " + aux + " não declarada! " );
			
					}

					if((yyvsp[-2]).tipo != (yyvsp[0]).tipo)
					{


						string temp_cast = gerarNome();

						string temp_builder = "\t" + temp_cast + " = " + "(" + (yyvsp[-2]).tipo + ")" + (yyvsp[0]).label + ";\n";

						mapa_temp[temp_cast].label = temp_cast;
						mapa_temp[temp_cast].tipo = (yyvsp[-2]).tipo;
						mapa_temp2[temp_cast].label = temp_cast;
						mapa_temp2[temp_cast].tipo = (yyvsp[-2]).tipo;

						(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + temp_builder +"\t" + (yyvsp[-2]).label + " = " + temp_cast + ";\n" ;


					}

					
					else
					{	

						
						(yyval).traducao = (yyvsp[-2]).traducao  + (yyvsp[0]).traducao + "\t" + (yyvsp[-2]).label +  " = " + (yyvsp[0]).label + ";\n";


					}				

					
				}
#line 1913 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 560 "sintatica.y" /* yacc.c:1646  */
    {

					string msn = buscaMapaTemp((yyvsp[-2]).nome_var);
					(yyvsp[-2]) = mapa_temp[msn];
				

						
						if( (yyvsp[-2]).tipo != "bool")
						{
							
							yyerror("Atribuicao invalida! Linha: " );
				
						}

					if((yyvsp[-2]).tipo != (yyvsp[0]).tipo)
					{


						string temp_cast = gerarNome();

						string temp_builder = "\t" + temp_cast + " = " + "(" + (yyvsp[-2]).tipo + ")" + (yyvsp[0]).label + ";\n";

						mapa_temp[temp_cast].label = temp_cast;
						mapa_temp[temp_cast].tipo = (yyvsp[-2]).tipo;

						mapa_temp2[temp_cast].label = temp_cast;
						mapa_temp2[temp_cast].tipo = (yyvsp[-2]).tipo;

						(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + temp_builder +"\t" + (yyvsp[-2]).label + " = " + temp_cast + ";\n" ;


					}

					
					else
					{	

						
						(yyval).traducao = (yyvsp[-2]).traducao  + (yyvsp[0]).traducao + "\t" + (yyvsp[-2]).label +  " = " + (yyvsp[0]).label + ";\n";


					}				

					
				}
#line 1963 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 605 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao;
				}
#line 1971 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 610 "sintatica.y" /* yacc.c:1646  */
    { // EX: a++ 
				
					atributos valor1,valorVariavel;	

					string msn = buscaMapaTemp((yyvsp[-1]).nome_var);
					(yyvsp[-1]) = mapa_temp[msn];
				
					if((yyvsp[-1]).tipo == "")
					{
							
						yyerror("Variavel " + msn + " não declarada! " );
			
					}
						

									valor1.tipo = (yyvsp[-1]).tipo;
					if((yyvsp[-1]).tipo == "float"){
						valor1.label = "1.0";
					}	

					if((yyvsp[-1]).tipo == "int"){
						valor1.label = "1";
					}

					valorVariavel.label = gerarNome();
					mapa_temp[valorVariavel.label].label = valorVariavel.label;
					mapa_temp[valorVariavel.label].tipo = (yyvsp[-1]).tipo;

					mapa_temp2[valorVariavel.label].label = valorVariavel.label;
					mapa_temp2[valorVariavel.label].tipo = (yyvsp[-1]).tipo;

					valor1.label = gerarNome();
					mapa_temp[valor1.label].label = valor1.label;
					mapa_temp[valor1.label].tipo = (yyvsp[-1]).tipo;

					mapa_temp2[valor1.label].label = valor1.label;
					mapa_temp2[valor1.label].tipo = (yyvsp[-1]).tipo;


					string tempLabelResultado = gerarNome();
		
					mapa_temp[tempLabelResultado].label = tempLabelResultado;
					mapa_temp[tempLabelResultado].tipo = (yyvsp[-1]).tipo;

					mapa_temp2[tempLabelResultado].label = tempLabelResultado;
					mapa_temp2[tempLabelResultado].tipo = (yyvsp[-1]).tipo;
					(yyval).traducao =  "\t" + valorVariavel.label + " = " + (yyvsp[-1]).label + ";\n\t"+
					valor1.label + " = " + "1" + ";\n\t" + tempLabelResultado + " = " + valorVariavel.label + " + "  + valor1.label + ";\n\t"+
					(yyvsp[-1]).label + " = " + tempLabelResultado + ";\n";

				}
#line 2027 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 662 "sintatica.y" /* yacc.c:1646  */
    { // EX: a--
				
					atributos valor1,valorVariavel;	

					string msn = buscaMapaTemp((yyvsp[-1]).nome_var);
					(yyvsp[-1]) = mapa_temp[msn];
				
					if((yyvsp[-1]).tipo == "")
					{
							
						yyerror("Variavel " + msn + " não declarada! " );
			
					}
						

					valor1.tipo = (yyvsp[-1]).tipo;
					if((yyvsp[-1]).tipo == "float"){
						valor1.label = "1.0";
					}	

					if((yyvsp[-1]).tipo == "int"){
						valor1.label = "1";
					}

					valorVariavel.label = gerarNome();
					mapa_temp[valorVariavel.label].label = valorVariavel.label;
					mapa_temp[valorVariavel.label].tipo = (yyvsp[-1]).tipo;

					mapa_temp2[valorVariavel.label].label = valorVariavel.label;
					mapa_temp2[valorVariavel.label].tipo = (yyvsp[-1]).tipo;

					valor1.label = gerarNome();
					mapa_temp[valor1.label].label = valor1.label;
					mapa_temp[valor1.label].tipo = (yyvsp[-1]).tipo;

					mapa_temp2[valor1.label].label = valor1.label;
					mapa_temp2[valor1.label].tipo = (yyvsp[-1]).tipo;


					string tempLabelResultado = gerarNome();
		
					mapa_temp[tempLabelResultado].label = tempLabelResultado;
					mapa_temp[tempLabelResultado].tipo = (yyvsp[-1]).tipo;

					mapa_temp2[tempLabelResultado].label = tempLabelResultado;
					mapa_temp2[tempLabelResultado].tipo = (yyvsp[-1]).tipo;
					(yyval).traducao =  "\t" + valorVariavel.label + " = " + (yyvsp[-1]).label + ";\n\t"+
					valor1.label + " = " + "1" + ";\n\t" + tempLabelResultado + " = " + valorVariavel.label + " - "  + valor1.label + ";\n\t"+
					(yyvsp[-1]).label + " = " + tempLabelResultado + ";\n";

				}
#line 2083 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 715 "sintatica.y" /* yacc.c:1646  */
    {
					string aux = (yyvsp[-2]).nome_var;
					string msn = buscaMapaTemp((yyvsp[-2]).nome_var);
					(yyvsp[-2]) = mapa_temp[msn];
					
					int existe = 0;

					list<string>::iterator i;

					for(i = nome_var.begin(); i != nome_var.end(); i++){

						if((yyvsp[-2]).bloco_pertence == *i)
						{
							existe = 1;
							break;
						}
					}


					if((yyvsp[-2]).tipo == "" || existe == 0)
					{
						msn = mapa_temp[msn].nome_var;	
						yyerror("Variavel " + aux + " não declarada! " );
			
					}

					if((yyvsp[-2]).tipo != (yyvsp[0]).tipo)
					{


						string temp_cast = gerarNome();

						string temp_builder = "\t" + temp_cast + " = " + "(" + (yyvsp[-2]).tipo + ")" + (yyvsp[0]).label + ";\n";

						mapa_temp[temp_cast].label = temp_cast;
						mapa_temp[temp_cast].tipo = (yyvsp[-2]).tipo;
						mapa_temp2[temp_cast].label = temp_cast;
						mapa_temp2[temp_cast].tipo = (yyvsp[-2]).tipo;

						(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + temp_builder +"\t" + (yyvsp[-2]).label + " = " + temp_cast + ";\n" ;


					}

					
					else
					{	

						Atributos x;
						x = (yyvsp[-2]);
						x.label = gerarNome();
						(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t"+x.label + " = " + (yyvsp[-2]).label + "\n"+ 
						conversaoImplicita(x, (yyvsp[0]), "+", &(yyval)) + "\t" + (yyvsp[-2]).label + " = " + (yyval).label +";\n" ;


					}				

					
				}
#line 2147 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 777 "sintatica.y" /* yacc.c:1646  */
    {
					string aux = (yyvsp[-2]).nome_var;
					string msn = buscaMapaTemp((yyvsp[-2]).nome_var);
					(yyvsp[-2]) = mapa_temp[msn];
					
					int existe = 0;

					list<string>::iterator i;

					for(i = nome_var.begin(); i != nome_var.end(); i++){

						if((yyvsp[-2]).bloco_pertence == *i)
						{
							existe = 1;
							break;
						}
					}


					if((yyvsp[-2]).tipo == "" || existe == 0)
					{
						msn = mapa_temp[msn].nome_var;	
						yyerror("Variavel " + aux + " não declarada! " );
			
					}

					if((yyvsp[-2]).tipo != (yyvsp[0]).tipo)
					{


						string temp_cast = gerarNome();

						string temp_builder = "\t" + temp_cast + " = " + "(" + (yyvsp[-2]).tipo + ")" + (yyvsp[0]).label + ";\n";

						mapa_temp[temp_cast].label = temp_cast;
						mapa_temp[temp_cast].tipo = (yyvsp[-2]).tipo;
						mapa_temp2[temp_cast].label = temp_cast;
						mapa_temp2[temp_cast].tipo = (yyvsp[-2]).tipo;

						(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + temp_builder +"\t" + (yyvsp[-2]).label + " = " + temp_cast + ";\n" ;


					}

					
					else
					{	

						Atributos x;
						x = (yyvsp[-2]);
						x.label = gerarNome();
						(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t"+x.label + " = " + (yyvsp[-2]).label + "\n"+ 
						conversaoImplicita(x, (yyvsp[0]), "-", &(yyval)) + "\t" + (yyvsp[-2]).label + " = " + (yyval).label +";\n" ;


					}				

					
				}
#line 2211 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 838 "sintatica.y" /* yacc.c:1646  */
    {
					string aux = (yyvsp[-2]).nome_var;
					string msn = buscaMapaTemp((yyvsp[-2]).nome_var);
					(yyvsp[-2]) = mapa_temp[msn];
					
					int existe = 0;

					list<string>::iterator i;

					for(i = nome_var.begin(); i != nome_var.end(); i++){

						if((yyvsp[-2]).bloco_pertence == *i)
						{
							existe = 1;
							break;
						}
					}


					if((yyvsp[-2]).tipo == "" || existe == 0)
					{
						msn = mapa_temp[msn].nome_var;	
						yyerror("Variavel " + aux + " não declarada! " );
			
					}

					if((yyvsp[-2]).tipo != (yyvsp[0]).tipo)
					{


						string temp_cast = gerarNome();

						string temp_builder = "\t" + temp_cast + " = " + "(" + (yyvsp[-2]).tipo + ")" + (yyvsp[0]).label + ";\n";

						mapa_temp[temp_cast].label = temp_cast;
						mapa_temp[temp_cast].tipo = (yyvsp[-2]).tipo;
						mapa_temp2[temp_cast].label = temp_cast;
						mapa_temp2[temp_cast].tipo = (yyvsp[-2]).tipo;

						(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + temp_builder +"\t" + (yyvsp[-2]).label + " = " + temp_cast + ";\n" ;


					}

					
					else
					{	

						Atributos x;
						x = (yyvsp[-2]);
						x.label = gerarNome();
						(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t"+x.label + " = " + (yyvsp[-2]).label + "\n"+ 
						conversaoImplicita(x, (yyvsp[0]), "*", &(yyval)) + "\t" + (yyvsp[-2]).label + " = " + (yyval).label +";\n" ;


					}				

					
				}
#line 2275 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 899 "sintatica.y" /* yacc.c:1646  */
    {
					string aux = (yyvsp[-2]).nome_var;
					string msn = buscaMapaTemp((yyvsp[-2]).nome_var);
					(yyvsp[-2]) = mapa_temp[msn];
					
					int existe = 0;

					list<string>::iterator i;

					for(i = nome_var.begin(); i != nome_var.end(); i++){

						if((yyvsp[-2]).bloco_pertence == *i)
						{
							existe = 1;
							break;
						}
					}


					if((yyvsp[-2]).tipo == "" || existe == 0)
					{
						msn = mapa_temp[msn].nome_var;	
						yyerror("Variavel " + aux + " não declarada! " );
			
					}

					if((yyvsp[-2]).tipo != (yyvsp[0]).tipo)
					{


						string temp_cast = gerarNome();

						string temp_builder = "\t" + temp_cast + " = " + "(" + (yyvsp[-2]).tipo + ")" + (yyvsp[0]).label + ";\n";

						mapa_temp[temp_cast].label = temp_cast;
						mapa_temp[temp_cast].tipo = (yyvsp[-2]).tipo;
						mapa_temp2[temp_cast].label = temp_cast;
						mapa_temp2[temp_cast].tipo = (yyvsp[-2]).tipo;

						(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + temp_builder +"\t" + (yyvsp[-2]).label + " = " + temp_cast + ";\n" ;


					}

					
					else
					{	

						Atributos x;
						x = (yyvsp[-2]);
						x.label = gerarNome();
						(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t"+x.label + " = " + (yyvsp[-2]).label + "\n"+ 
						conversaoImplicita(x, (yyvsp[0]), "/", &(yyval)) + "\t" + (yyvsp[-2]).label + " = " + (yyval).label +";\n" ;


					}				

					
				}
#line 2339 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 961 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval) = (yyvsp[-1]);
				}
#line 2347 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 965 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + conversaoImplicita((yyvsp[-2]), (yyvsp[0]), "+", &(yyval));
				}
#line 2355 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 969 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + conversaoImplicita((yyvsp[-2]), (yyvsp[0]), "-", &(yyval));
				}
#line 2363 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 973 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + conversaoImplicita((yyvsp[-2]), (yyvsp[0]), "*", &(yyval));
				}
#line 2371 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 977 "sintatica.y" /* yacc.c:1646  */
    {	
					cout << "CUIDADO: Divisao po Zero! Linha " + num_linha();
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + conversaoImplicita((yyvsp[-2]), (yyvsp[0]), "/", &(yyval));
				}
#line 2380 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 983 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval) = (yyvsp[0]);
				}
#line 2388 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 988 "sintatica.y" /* yacc.c:1646  */
    {
					string aux = (yyvsp[-5]).nome_var;
					string msn = buscaMapaTemp((yyvsp[-5]).nome_var);
					(yyvsp[-5]) = mapa_temp[msn];


					int existe = 0;

					list<string>::iterator i;

					for(i = nome_var.begin(); i != nome_var.end(); i++){

						if((yyvsp[-5]).bloco_pertence == *i)
						{
							existe = 1;
							break;
						}
					}


					if((yyvsp[-5]).tipo == "" || existe == 0)
					{
						msn = mapa_temp[msn].nome_var;	
						yyerror("Variavel " + aux + " não declarada! " );
			
					}

					if((yyvsp[-5]).tipo != (yyvsp[-1]).tipo)
					{


						string temp_cast = gerarNome();

						string temp_builder = "\t" + temp_cast + " = " + "(" + (yyvsp[-5]).tipo + ")" + (yyvsp[-1]).label + ";\n";

						mapa_temp[temp_cast].label = temp_cast;
						mapa_temp[temp_cast].tipo = (yyvsp[-5]).tipo;
						mapa_temp2[temp_cast].label = temp_cast;
						mapa_temp2[temp_cast].tipo = (yyvsp[-5]).tipo;

						(yyval).traducao = (yyvsp[-5]).traducao + (yyvsp[-1]).traducao + temp_builder +"\t" + (yyvsp[-5]).label + " = " + temp_cast + ";\n" ;


					}

					else
					{

						(yyval).traducao = (yyvsp[-5]).traducao + (yyvsp[-1]).traducao + "\n\tcout << " + (yyvsp[-1]).label + ";\n\t"
						+ "cin >> " + (yyvsp[-5]).label + ";\n\t";
					}
				}
#line 2445 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 1041 "sintatica.y" /* yacc.c:1646  */
    {
					string aux = (yyvsp[-4]).nome_var;
					string msn = buscaMapaTemp((yyvsp[-4]).nome_var);
					(yyvsp[-4]) = mapa_temp[msn];


					int existe = 0;

					list<string>::iterator i;

					for(i = nome_var.begin(); i != nome_var.end(); i++){

						if((yyvsp[-4]).bloco_pertence == *i)
						{
							existe = 1;
							break;
						}
					}


					if((yyvsp[-4]).tipo == "" || existe == 0)
					{
						msn = mapa_temp[msn].nome_var;	
						yyerror("Variavel " + aux + " não declarada! " );
			
					}



						(yyval).traducao = (yyvsp[-4]).traducao + (yyvsp[0]).traducao + "\n\t"
						+ "cin >> " + (yyvsp[-4]).label + ";\n\t";
			
				}
#line 2483 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 1079 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).traducao = (yyvsp[-1]).traducao + "\n\tcout << " +(yyvsp[-1]).label + ";\n\t" ;
				}
#line 2491 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 1084 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + conversaoImplicita((yyvsp[-2]), (yyvsp[0]), ">", &(yyval));
				}
#line 2499 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 1088 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + conversaoImplicita((yyvsp[-2]), (yyvsp[0]), "<", &(yyval));
				}
#line 2507 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 1092 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).traducao = (yyvsp[-3]).traducao + (yyvsp[0]).traducao + conversaoImplicita((yyvsp[-3]), (yyvsp[0]), ">=", &(yyval));
				}
#line 2515 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 1096 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).traducao = (yyvsp[-3]).traducao + (yyvsp[0]).traducao + conversaoImplicita((yyvsp[-3]), (yyvsp[0]), "<=", &(yyval));
				}
#line 2523 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 1100 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).traducao = (yyvsp[-3]).traducao + (yyvsp[0]).traducao + conversaoImplicita((yyvsp[-3]), (yyvsp[0]), "==", &(yyval));
				}
#line 2531 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 1104 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).traducao = (yyvsp[-3]).traducao + (yyvsp[0]).traducao + conversaoImplicita((yyvsp[-3]), (yyvsp[0]), "!=", &(yyval));
				}
#line 2539 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 1108 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).traducao = (yyvsp[-3]).traducao + (yyvsp[0]).traducao + conversaoImplicita((yyvsp[-3]), (yyvsp[0]), "&&", &(yyval));
				}
#line 2547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 1112 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).traducao = (yyvsp[-3]).traducao + (yyvsp[0]).traducao + conversaoImplicita((yyvsp[-3]), (yyvsp[0]), "||", &(yyval));
				}
#line 2555 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 1116 "sintatica.y" /* yacc.c:1646  */
    {
					string tempNome = gerarNome();
					string tempNome2 = gerarNome();
					(yyval).traducao = (yyvsp[-3]).traducao + (yyvsp[0]).traducao + "\t" + tempNome + " = " + (yyvsp[-3]).label + " * " + (yyvsp[0]).label + ";\n" + "\t" + tempNome2 + " = " + tempNome + " / 100;\n";
					(yyval).label = tempNome2;
				}
#line 2566 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 1125 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval) = (yyvsp[0]);
					(yyval).label = gerarNome();
				
					mapa_temp[(yyval).label].label = (yyval).label;
					mapa_temp[(yyval).label].tipo = (yyval).tipo;

					mapa_temp2[(yyval).label].label = (yyval).label;
					mapa_temp2[(yyval).label].tipo = (yyval).tipo;
					if((yyvsp[-1]).label == "(float)"){
						(yyval).traducao = "\tfloat " + (yyval).label + " = " + (yyvsp[0]).label + ";\n";
						(yyval).tipo = "float";
					}else if((yyvsp[-1]).label == "(int)"){
						(yyval).traducao = "\t" + (yyval).label + " = " + (yyvsp[0]).label + ";\n";
						(yyval).tipo = "int";
					}else{
						(yyval).traducao = "\t" + (yyval).label + " = " + (yyvsp[0]).label + ";\n";
					}
				}
#line 2590 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1145 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval) = (yyvsp[0]);
					(yyval).label = gerarNome();
					mapa_temp[(yyval).label].label = (yyval).label;
					mapa_temp[(yyval).label].tipo = (yyval).tipo;

					mapa_temp2[(yyval).label].label = (yyval).label;
					mapa_temp2[(yyval).label].tipo = (yyval).tipo;
					(yyval).traducao = (yyvsp[0]).traducao + "\t"  + (yyval).label + " = -" + (yyvsp[0]).label + ";\n";
					
				}
#line 2606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1157 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval) = (yyvsp[0]);
					(yyval).label = gerarNome();
					mapa_temp[(yyval).label].label = (yyval).label;
					mapa_temp[(yyval).label].tipo = (yyval).tipo;

					mapa_temp2[(yyval).label].label = (yyval).label;
					mapa_temp2[(yyval).label].tipo = (yyval).tipo;
					(yyval).traducao = (yyvsp[0]).traducao + "\t" + (yyval).label + " = " + (yyvsp[0]).label + ";\n";
				}
#line 2621 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1170 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval) = (yyvsp[0]);
				}
#line 2629 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1174 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval) = (yyvsp[0]);
				}
#line 2637 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1178 "sintatica.y" /* yacc.c:1646  */
    {
					
					string msn = buscaMapaTemp((yyvsp[0]).nome_var);
					(yyvsp[0]) = mapa_temp[msn];
				
						
						if((yyvsp[0]).tipo == "")
						{
							
							yyerror("Variavel " + msn + " não declarada!  " );
				
						}

					(yyval) = (yyvsp[0]);	


				}
#line 2659 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1196 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval) = (yyvsp[0]);
				}
#line 2667 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1200 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval) = (yyvsp[0]);
					(yyval).traducao = (yyval).label;
				}
#line 2676 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1205 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval) = (yyvsp[0]);
				}
#line 2684 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1210 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval) = (yyvsp[0]);
				}
#line 2692 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2696 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1215 "sintatica.y" /* yacc.c:1906  */


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
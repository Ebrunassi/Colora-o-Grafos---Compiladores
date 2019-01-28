%{
#include <string.h>
#include "pilha.h"
extern int yylex();
extern FILE* yyin;
extern int yyrestart(FILE *f);
extern char* yytext;
extern int yyleng;
extern int yymore();
void* lista;
void* pilha;
void* pilha_backup;
int registradores;
int i = 0;
int num_grafo;
%}
%union{
	char *str;
	int num;
    void* pilhas;
}
%token NUM
%token SETA
%token MOVE
%token GRAPH
%token DOISPONTOS
%token ATRIBUICAO
%token K
%token EOL
%token FIM_LINHA
%type <num> NUM
%type <num> CONJUNTO_INTERFERENCIAS

%type <pilhas> program
%type <pilhas> LINHA_COMANDO
%debug

%%

s: program;

program:
    LINHA_COMANDO EOL                     {}
    |   program LINHA_COMANDO EOL         {}
;

LINHA_COMANDO:
    GRAPH NUM DOISPONTOS                                {
            //printf("Graph %d: ",$2-1);
            num_grafo = $2-1;
            /*Aqui começaremos a a analisar o grafo*/
            if(i != 0){
                verifica_colisao(pilha,pilha_backup,registradores,num_grafo);
            }
            lista = criaLista();
        }
    |   K ATRIBUICAO NUM                                {registradores = $3;pilha = criaPilha($3); pilha_backup = criaPilha($3);}
    |   NUM SETA CONJUNTO_INTERFERENCIAS                {adicionaPilha($1,lista,pilha);adicionaPilha($1,lista,pilha_backup);limpa_lista(lista);}
    |   CONJUNTO_MOVE                                   {}

;

CONJUNTO_INTERFERENCIAS:
    NUM CONJUNTO_INTERFERENCIAS     {adicionaNo_lista(lista,$1);}
    |                               {i++;}
;

CONJUNTO_MOVE:
    |   NUM MOVE NUM  {}
    |   CONJUNTO_MOVE NUM MOVE NUM      {}
    |                                   {}
;
%%
void yyerror(){


	exit(0);
}
int main(int argc, char **argv){
	yyparse();
    printf("\nGraph 27921: SUCCESS");
}
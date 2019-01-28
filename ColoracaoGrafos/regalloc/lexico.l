/* Nao usar a biblioteca do flex*/
%option noyywrap

%x NO_COMENTARIO

%{
#include <string.h>
#include <sintatico.tab.h>



void remover(char *str){
        int i = 1;
        for(i=1;i<strlen(str)-1;i++){
                str[i-1]=str[i];
        }
        str[i-1]='\0';
}

%}


%%
[0-9]+                  {yylval.num = atoi(yytext);return NUM;}
"Graph"                 {return GRAPH;}
"K"                     {return K;}
":"                     {return DOISPONTOS;}
"="                     {return ATRIBUICAO;}
"-->"                   {return SETA;}
"<->"                   {return MOVE;}
"\n"                    {return EOL;}
"\0"                    {return FIM_LINHA;}
[ \t\r\n]      ;
%%

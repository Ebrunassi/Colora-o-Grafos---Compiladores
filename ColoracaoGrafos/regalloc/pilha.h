#include <stdlib.h>
#include <stdio.h>


typedef struct node {
    int val;
    void *lista;
    int cor;
    struct node* prox;
    struct node* ant;
} node_t;

typedef struct pilha{
    int registradores;
    int tamanho;
    node_t *head;
    node_t *tail;
}pilha_s;

typedef struct lista{
    node_t *head;
    node_t *tail;
    int tamanho;
}lista_s;

void* criaLista();
void adicionaNo_lista(void* lista_p,int no);
void ver_lista(void* lista_p);
void limpa_lista(void* lista_p);

int ver_tamanho_pilha(void* pilha_p);
void* adicionaPilha(int no, void* lista_p, void* pilha_p);
void* criaPilha(int registradores);
void ver_pilha(void* pilha_p);

void verifica_colisao(void *pilha_p, void* pilha_backup, int registradores, int num_grafo);

node_t* get_anterior(void *pilha_p, node_t* posic);
node_t* get_last(void* pilha_p);
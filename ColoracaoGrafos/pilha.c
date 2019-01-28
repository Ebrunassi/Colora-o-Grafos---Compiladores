#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

/* Operacoes Lista */
void* criaLista(){
    lista_s *lista;
    lista = malloc(sizeof(lista_s) + 2*sizeof(node_t));

    lista->head = NULL;
    lista->tail = NULL;
    lista->tamanho = 0;

    return lista;
}
void adicionaNo_lista(void* lista_p,int no){
    
    node_t *node = malloc(sizeof(node_t) + 10);
    lista_s *lista = (lista_s *) lista_p;

    if(lista->head == NULL){
        node->val = no;
        node->prox = NULL;
        lista->head = node;
        lista->tail = node;
    }else{
        node_t *no_atual = lista->head;
        node->val = no;
        while(no_atual->prox != NULL){         // Procura o último elemento da lista
            no_atual = no_atual->prox;
        }
        no_atual->prox = node;              // Insere ele
        node->prox = NULL;                  // Faz ele apontar para nulo
        lista->tail = node;                 // Faz 'tail' apontar para ele
    }

    lista->tamanho++;
    return;
}
void limpa_lista(void* lista_p){
    lista_s *lista = (lista_s *) lista_p;
    node_t *no_atual = lista->head;
    node_t *no_prox = no_atual->prox;

    if(no_prox == NULL){
        // free(no_atual);
        lista->head = NULL;
        lista->tail = NULL;
    }else{
        while(no_atual->prox != NULL){
            // free(no_atual);
            no_atual = no_prox;
            no_prox = no_prox->prox;
        }
        lista->head = NULL;
        lista->tail = NULL;
    }
}
int get_tamanho_lista(void *lista_p){
    lista_s *lista = (lista_s *) lista_p;
    return lista->tamanho;
}
void ver_lista(void* lista_p){

    lista_s *lista = (lista_s *) lista_p;

    node_t *no = lista->head;

    if(no == NULL)
        return;

    printf("\n");
    while(no != NULL){
        printf(" %d -",no->val);
        no = no->prox;
    }
    printf("\n");
    
}
void* copia_lista( void* lista_p){

    lista_s *lista_nova = criaLista();
    lista_s *lista = (lista_s *) lista_p;
    if(lista->head != NULL){
        int tam = 0;
        node_t *node = malloc(sizeof(node_t) + 10);
        node_t *node_atual = lista->head;
        node->val = node_atual->val;
        lista_nova->head = node;

        while(node_atual->prox != NULL){                 // Vamos percorrer toda a lista
            node_t *no = malloc(sizeof(node_t) + 10);
            node->prox = no;
            node = no;                      // Verificar!
            node_atual = node_atual->prox;
            node->val = node_atual->val;
        }
        node->prox = NULL;
        lista_nova->tail = node;
        tam = lista->tamanho;
        lista_nova->tamanho = tam;
        lista->tamanho = 0; // --- error!
        return lista_nova;
    }else{
        lista_nova->head = NULL;
        lista_nova->tail = NULL;
        return lista_nova;
    }
}
int remove_elemento_lista(void* lista_p, int val){
    lista_s *lista = (lista_s *) lista_p;
    node_t *no = lista->head;
    node_t *no_ant = lista->head;
    node_t *noS;
    while(no != NULL){
        if(no->val == val){
            if(lista->head == no && lista->tail == no){         // Se só houver um nó na lista
                lista->head = NULL;
                lista->tail = NULL;
                free(no);
                lista->tamanho--;
                break;
            }else if(lista->head == no && lista->tail != no){   // Se ele for o primeiro
                lista->head = no->prox;
                free(no);
                lista->tamanho--;
                break;
                // free(no);
            }else if(lista->tail == no && lista->head != no){   // Se ele for o último
                lista->tail = no_ant;
                no_ant->prox = NULL;
                free(no);
                lista->tamanho--;
                break;
                // free(no);
            }else{                                              // Se ele for um nó que ta no meio
                no_ant->prox = no->prox;
                free(no);
                lista->tamanho--;
                break;
                // free(no);
            }
            // lista->tamanho--;
            // if(lista->tamanho < 0)
            //     lista->tamanho = 0;
        }
        no_ant = no;
        no = no->prox;
    }
    return 0;

}
void retira_no_lista(void* pilha_p,int val){
    // Essa função é usada quando estamos empilhando os nós,
    // toda vez que faremos isso, precisamos percorrer TODAS as listas de TODOS os elementos da pilha
    // para retirar os nós da lista que possuem um valor igual ao passado por parâmetro   
    pilha_s *pilha = (pilha_s *) pilha_p;

    node_t *posic;
    posic = get_last(pilha);
    while(posic != NULL){
        remove_elemento_lista(posic->lista,val);
        posic = get_anterior(pilha,posic);
    }
    // printf("\ntamanho da lista q irei remover > %d\n",get_tamanho_lista(posic->lista));
}

/* Operações Pilha */
void* criaPilha(int registradores){
    pilha_s *pilha;
    pilha = malloc(sizeof(pilha_s));
    pilha->registradores = registradores;
    pilha->tamanho = 0;
    pilha->head = NULL;
    pilha->tail = NULL;

    // printf("o tamanho é de %d",pilha->registradores);
    return pilha;
}

void* adicionaPilha2(int no, void* pilha_p, void* pilha_b){

    lista_s *lista = criaLista();
    pilha_s *pilha = (pilha_s *) pilha_p;
    pilha_s *pilha_back = (pilha_s *) pilha_b;
    node_t *node = malloc(sizeof(node_t) + 10);
    node_t *posic = malloc(sizeof(node_t) + 10);

    posic = pilha_back->head;
    while(posic != NULL){
        if(posic->val == no){
            if(pilha->tail == NULL && pilha->head == NULL){
                node->val = no;
                node->prox = NULL;
                node->ant = NULL;
                pilha->head = node;
                pilha->tail = node; 
                node->lista = copia_lista(posic->lista);
                pilha->tamanho++;
                break;
            }else{
                node_t *no_atual = pilha->tail;
                node->ant = no_atual;
                no_atual->prox = node;
                node->prox = NULL;
                pilha->tail = node;
                node->val = no;
                node->lista = copia_lista(posic->lista);     
                pilha->tamanho++;
                break;
            }
        }
        posic = posic->prox;
    }
}
void* adicionaPilha(int no, void* lista_p, void* pilha_p){

    int tam;
    node_t *node = malloc(sizeof(node_t) + 10);
    
    lista_s *lista = (lista_s *) lista_p;
    pilha_s *pilha = (pilha_s *) pilha_p;
    if(pilha->tail == NULL && pilha->head == NULL){
        node->val = no;
        node->prox = NULL;
        node->ant = NULL;
        pilha->head = node;
        pilha->tail = node; 
        node->lista = copia_lista(lista);

    }else{
        node_t *no_atual = pilha->head;
        while(no_atual->prox != NULL){
            no_atual = no_atual->prox;
        }
        node->ant = no_atual;
        no_atual->prox = node;
        node->prox = NULL;
        pilha->tail = node;
        node->val = no;
        node->lista = copia_lista(lista);     
    }
    pilha->tamanho++;
    // printf("\nvalor da calda : %d\n",pilha->tail->val);
}
int ver_tamanho_pilha(void* pilha_p){
    if(pilha_p == NULL){
        return -1;
    }
    pilha_s *pilha = (pilha_s *) pilha_p;
    return pilha->tamanho;
}
void ver_pilha(void* pilha_p){
    pilha_s *pilha = (pilha_s *) pilha_p;

    node_t *no_pilha = pilha->tail;
    printf("K = %d\n",pilha->registradores);
    while(no_pilha != NULL){    // Percorre a pilha inteira

        if(no_pilha->val != -9999){
            printf("\n%d -->",no_pilha->val);
            printf(" - tamanho lista : %d \n",get_tamanho_lista(no_pilha->lista));

            lista_s *lista = (lista_s *) no_pilha->lista; 
            node_t *no_lista = lista->head;
            while(no_lista != NULL){
                printf(" %d",no_lista->val);
                no_lista = no_lista ->prox;
            }
            printf("\n");
        }
        no_pilha = no_pilha->ant;
    }
        printf("\n\n");
}


/* -- Pilha -- */
node_t* get_last(void* pilha_p){
    pilha_s *pilha = (pilha_s *) pilha_p;
    if(pilha->tail != NULL){
        return pilha->tail;
    }else{
        return NULL;
    }
}
node_t* get_anterior(void *pilha_p, node_t* posic){
    pilha_s *pilha = (pilha_s *) pilha_p;
    if(posic->ant != NULL){
        return posic->ant;
    }else{
        return NULL;
    }
}
node_t* get_prox(void *pilha_p, node_t* posic){
    pilha_s *pilha = (pilha_s *) pilha_p;
    if(posic->prox != NULL){
        return posic->prox;
    }else{
        return NULL;
    }
}
node_t* get_first(void* pilha_p){
    pilha_s *pilha = (pilha_s *) pilha_p;
    if(pilha->head != NULL){
        return pilha->head;
    }else{
        return NULL;
    }
}
void retira_no_pilha(void* pilha_p,node_t *posic){
    pilha_s *pilha = (pilha_s *) pilha_p;
    node_t *posic_ant;

    if(posic->val == -9999)             // Ajuste de tamanho (estava diminuindo o tamanho quando o valor era -9999)
        pilha->tamanho++;

    if(posic == get_last(pilha) && posic == get_first(pilha)){       // Se só tiver um elemento na pilha
        // free(posic);
        pilha->head = NULL;
        pilha->tail = NULL;
        // free(posic);
    }else if(posic == get_last(pilha) && posic != get_first(pilha)){ // Se for o primeiro da pilha
        posic_ant = posic->ant;
        // free(posic);
        posic = posic_ant;
        pilha->tail = posic;
    }else if(posic != get_last(pilha) && posic == get_first(pilha)){ // Se for o último da pilha
        posic_ant = posic->prox;
        // free(posic);
        posic = posic_ant;
        pilha->head = posic;
    }
    pilha->tamanho--;
}

void transferencia_de_listas(void* pilha_graf_p, void *pilha_b_p){

    pilha_s *pilha_graf = (pilha_s *) pilha_graf_p;
    pilha_s *pilha_b = (pilha_s *) pilha_b_p;
    node_t *posic_graf, *posic_b;

    posic_graf = pilha_graf->tail;
    while(posic_graf != NULL){                          // Percorre a pilha

        posic_b = pilha_b->tail;
        while(posic_b != NULL){                         // Percorre a pilha backup

            if(posic_graf->val == posic_b->val){        // Achou!     
                // printf("%d == %d\n",posic_graf->val, posic_b->val);
                posic_graf->lista = copia_lista(posic_b->lista);
                break;
            }
            posic_b = posic_b->ant;
        }
        posic_graf = posic_graf->ant;
    }    


}
node_t* retira_no_pilha_2(void* pilha_p, node_t *posic){
    pilha_s *pilha = (pilha_s *) pilha_p;
    node_t *posic_ant, *posic_return;

    if(posic->val == -9999)             // Ajuste de tamanho (estava diminuindo o tamanho quando o valor era -9999)
        pilha->tamanho++;

    if(posic == get_last(pilha) && posic == get_first(pilha)){       // Se só tiver um elemento na pilha
        // free(posic);
        pilha->head = NULL;
        pilha->tail = NULL;
        posic_return = pilha->head;
        free(posic);
    }else if(posic == get_last(pilha) && posic != get_first(pilha)){ // Se for o último da pilha
        posic_ant = posic->ant;
        posic_ant->prox = NULL;
        pilha->tail = posic_ant;
        free(posic);
        posic_return = posic_ant->ant;
    }else if(posic != get_last(pilha) && posic == get_first(pilha)){ // Se for o primeiro da pilha
        pilha->head = posic->prox;
        posic->ant = NULL;
        free(posic);
        posic_return = posic_ant;
    }
    pilha->tamanho--;
    return posic_return;
}
int pega_cor_possivel(node_t *posic,int registradores){
    lista_s *lista = (lista_s *) posic->lista;
    int i, cor = 0;
    node_t *posic_at;

    for(i = 0 ; i < registradores+200 ; i++){

        posic_at = lista->head;
        while(posic_at != NULL){
            if(posic_at->val != i){
                cor = i;
            }else{
                break;
            }
            if(posic_at->prox == NULL)
                return cor;
            posic_at = posic_at->prox;
        }
        
    }
    return cor;
}

int verifica_existencia_elemento(void* lista_p, int val){
    lista_s *lista = (lista_s *) lista_p;
    node_t *posic;
    posic = lista->head;
    while(posic != NULL){
        if(posic->val == val){
            return 1;
        }
        posic = posic->prox;
    }
    return 0;
}
void empilha_possivel_spill(void* pilha_p, void* pilha_p_graf, void* pilha_b){
    pilha_s *pilha = (pilha_s *) pilha_p;
    pilha_s *pilha_graf = (pilha_s *) pilha_p_graf;
    int max = 0;
    node_t * posic;

    posic = pilha->tail;
    node_t *maior_no;

    if(ver_tamanho_pilha(pilha) == 1){      // Se só tiver um nó na pilha e o grau dele for maior que K

        maior_no = get_last(pilha);
        while(maior_no != NULL){

            if(maior_no->val != -9999)
                break;

            maior_no = maior_no->ant;
        }
        adicionaPilha(maior_no->val,maior_no->lista,pilha_graf);
        // adicionaPilha2(maior_no->val,pilha_graf,pilha_b);
        retira_no_lista(pilha,maior_no->val);   
        maior_no->val = -9999;
        pilha->tamanho--;
        return;
    }
    int soma = 0;
    while(posic != NULL){                               // Pega o nó com o maior grau
        if(posic->val != -9999)
            soma = soma + get_tamanho_lista(posic->lista);

        /* -------------- Teste! Qualquer coisa apaga isso aqui ------------------------ */
        if((get_tamanho_lista(posic->lista) == max && posic->val != -9999)){
            if(posic->val < maior_no->val)
                maior_no = posic;
        }
        /* ----------------------------------------------------------------------------- */

        if((get_tamanho_lista(posic->lista) > max && posic->val != -9999)){
            maior_no = posic;
            max = get_tamanho_lista(posic->lista);
        }
        posic = posic->ant;
    }
    if(soma <= 0){
        return;
    }
    // printf("\no valor tentado colocar é : %d\n",maior_no->val);
    // printf("\nACHOU : %d\n",maior_no->val);
    // printf("\n o tamanho da lista do vencedor é de : %d\n",get_tamanho_lista(maior_no->lista));
    adicionaPilha(maior_no->val,maior_no->lista,pilha_graf);
    // adicionaPilha2(maior_no->val,pilha_graf,pilha_b);
    retira_no_lista(pilha,maior_no->val);    
    // printf("\nVamos tirar o nó ----> %d",maior_no->val);
    retira_no_pilha(pilha,maior_no);
    maior_no->val = -9999;
    // pilha->tamanho--;


}
void adiciona_cor_vizinhos(node_t *posic, int cor, void* pilha_p){
    pilha_s *pilha = (pilha_s *) pilha_p;
    lista_s *lista;
    node_t *pos;            // Irá pegar todos os elementos da pilha
    int bol = 0;

    pos = get_last(pilha);
    while(pos != NULL){
        if(pos != posic){
            lista = pos->lista;
            bol = verifica_existencia_elemento(lista,posic->val);
            if(bol == 1){   // BOL == 1   -->   Existe esse elemento na lista
                adicionaNo_lista(pos->lista,cor);
            }
        }
        pos = get_anterior(pilha,pos);
    }


}
void libera_pilha(void *pilha_p){
    pilha_s *pilha = (pilha_s *) pilha_p;
    node_t *posic;
    node_t *posic_prox;
    posic = get_first(pilha);

    while(posic != NULL){
        posic_prox = posic->prox;
        free(posic);
        posic = posic_prox;
    }
}
/*  A 'pilha' recebida aqui será usada para fazer a verdadeira pilha verificando se 
    o grafo poderá ser colorido ou nao*/
void verifica_colisao(void *pilha_p, void* pilha_backup, int registradores, int num_grafo){
    pilha_s *pilha = (pilha_s *) pilha_p;       // Pilha recebida por parâmetro
    pilha_s *pilha_b = (pilha_s *) pilha_backup;

    pilha_s *pilha_graf = criaPilha(registradores);          // Pilha que será usada para a verificação
    node_t *posic, *posic_ant, *posic_aux, *posic_novo;
    if(num_grafo == 1){
        printf("Graph %d: ",num_grafo);
    }else{
        printf("\nGraph %d: ",num_grafo);
    }
    // printf("\n ------------------------\n");
    int i = 0;
    int change = 1;
    int cont = 0;
    // printf("\nO TAMANHO DA PILHA INICIAL : %d",ver_tamanho_pilha(pilha));
    // ver_pilha(pilha);
    // ----------- EMPILHANDO ---------------------------------------------------
    do{
        // change = 0;
        while(change == 1){
            change = 0;
            // for(i = 0 ; i < 3 ; i++){        // ATENÇÃO! A pilha será percorrida até que TODOS os nós possíveis sejam retirados
            posic = get_first(pilha);   // Qualquer coisa troca por 'last'
            while(posic != NULL){                       // Percorre a pilha inteira, verificando e empilhando na outra pilha
                // printf("\nANALISANDO : %d  tamanho : %d \n",posic->val,get_tamanho_lista(posic->lista));
                if(get_tamanho_lista(posic->lista) < registradores && posic->val != -9999){    // Verifica se pode ser empilhado!
                    if(posic->val != -9999)
                        adicionaPilha(posic->val,posic->lista,pilha_graf);  // Adiciona nó na pilha
                        // adicionaPilha2(posic->val,pilha_graf,pilha_b);

                    retira_no_lista(pilha,posic->val);                  // Retira este nó da lista dos outros elementos

                    retira_no_pilha(pilha,posic);                       // Retira o nó da pilha original
                    posic->val = -9999;                                 // Como este nó já foi inserido, vamos torná-lo 'nulo' na pilha original
                    change = 1;
                }

                posic = get_prox(pilha,posic);
            }
            
            if(change == 0)
                break;
            cont++;
        }
        // printf("\nsaiu");
        // printf("\no tamanho da pilha é de : %d\n",ver_tamanho_pilha(pilha));
        
        // }
        if(ver_tamanho_pilha(pilha) > 0){
            // printf("\npossivel spilll\n");
            // ver_pilha(pilha);
            // ver_pilha(pilha);
            empilha_possivel_spill(pilha,pilha_graf,pilha_b);
            cont = 0;
            change = 1;
        }

    }while(ver_tamanho_pilha(pilha) > 0);
    // ---------- FIM: EMPILHANDO -----------------------------------------------

    // printf("\nO TAMANHO DA PILHA FINAL : %d",ver_tamanho_pilha(pilha_graf));
        // ver_pilha(pilha_graf);


    //   FUNÇÃO TRANSFERENCIAS DE LISTAS 
    transferencia_de_listas(pilha_graf,pilha_b);
    // printf("\nANTES : \n");
    // ver_pilha(pilha_graf);
    // printf("\n-------------------------------------------------------------------\n");




    // ----------- COLOCANDO NO GRAFO COM SUA DEVIDA COR ------------------------
    // pilha_graf  -->  pilha certinha com todos os elementos na lista
    
    
    posic = get_last(pilha_graf);
    int cor;
    int resposta = 1;
    // printf("\ntamanho da lista spill : %d\n",get_tamanho_lista(lista_spill));
    while(posic != NULL){
        cor = pega_cor_possivel(posic,registradores);     // Pega a primeira cor possível
        // printf("\n (%d) - %d",cor,posic->val);
        if(cor >= registradores){                           // SPILL!!
            resposta = 0;
        }
        
        adiciona_cor_vizinhos(posic,cor,pilha_graf);
        posic = get_anterior(pilha_graf,posic);
    }
    // printf("\nDEPOIS : \n");
    // ver_pilha(pilha_graf);
    // printf("\n-------------------------------------------------------------------\n");

    if(resposta == 1){
        printf("SUCCESS");
    }else{
        printf("SPILL");
    }
    libera_pilha(pilha_b);
    libera_pilha(pilha_graf);

    // printf("\nPilha depois da iserção das cores -------------------------");
    // ver_pilha(pilha_graf);
    

}


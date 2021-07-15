#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


struct numero{
    int num;
    Num* prox;
    int marca;
};
struct lista{
    Num* inicio;
    Num* fim;
};

Lista* InicializaLista(){
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->fim = NULL;
    return lista;
}

Num* InicilizaNum(int i, int vBooleano){
    Num* numero = (Num*)malloc(sizeof(Num));
    numero->num = i;
    numero->marca = vBooleano;
    return numero;
}

//insere os nuúmeros na lista
void InsereNum(Lista* lista, Num* novo){
        if (lista->fim == NULL && lista->inicio == NULL){//lista vazia
            lista->inicio = novo;
        } else {
             lista->fim->prox = novo;
        }
    lista->fim = novo;
    novo->prox = NULL;
}

void MarcaMultiplos(Lista* lista, int N){
    Num* p = lista->inicio;
    for (int i = 2; (i*i) <= N; i++){
        while (p->prox != NULL){
            if (p->prox->num % i == 0 && p->prox->num != i){
                Num* atual = p->prox->prox;
                p->prox->marca++;
                p->prox = atual;
            }
            if (p->prox == NULL){
                break;
            }
            p = p->prox;
        }
        p = lista->inicio;
        if (p->num % i == 0 && p->num != i){
           p->marca++;
        }
    }
}

//imprime os números não marcados
void ImprimeNaoMarcados(Lista* lista){
    Num* p = lista->inicio;
    for(p = lista->inicio; p != NULL; p = p->prox){
        if (p->marca == 0){
            printf("%d ",p->num);
        }
    }
    printf("\n");
}

//acertar os frees
void LiberaLista(Lista* lista){
    Num* p = lista->inicio;
    while (p != NULL) {
        Num* atual = p->prox;
        LiberaNum(p);
        p = atual;
    }
    LiberaNum(p);
    free(lista);
}

void LiberaNum(Num *numero){
    if (numero != NULL){
        free(numero);
    }
}

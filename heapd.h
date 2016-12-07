/*
#-------------------ESTRUTURA HEAP--------------------#
#  heap maximo ---> maior valor sempre esta na raiz!  #
#  heap minimo ---> menor valor sempre esta na raiz!  #
#  consiste em uma arvore binaria completa!           #
#-----------------------------------------------------#
*/
#ifndef HEAPD_H
#define HEAPD_H

#include "item.h"

typedef struct NO {
   ITEM *item;
   struct NO *pai;
   struct NO *filho_esq;
   struct NO *filho_dir;
   struct NO *filho_esq_huff;
   struct NO *filho_dir_huff;
} NO;

NO *criarNO(ITEM *item);
int apagarNO(NO *no);

typedef struct heapd HEAPD;

HEAPD *criarHeap();
int apagarHeap(HEAPD *heap);

int vazia(HEAPD *heapd);
int tamanho(HEAPD *heapd);
int altura(HEAPD *heapd);

void imprimir(HEAPD *heapd);

int inserir(HEAPD *heapd, NO *no);
NO *remover(HEAPD *heapd);

#endif

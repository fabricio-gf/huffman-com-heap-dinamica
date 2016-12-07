#include "huffman.h"
#include <stdlib.h>
#include <stdio.h>

#define NR_SIMBOLOS 256

struct huffman {
   ARVORE_BINARIA *arvore;
   char codigo[NR_SIMBOLOS][NR_SIMBOLOS];
};

void imprimirCodigo (TABELA_HUFFMAN* huffman) {
   if (huffman != NULL)
      for (int i = 0; i < NR_SIMBOLOS; i++) {
         if (huffman->codigo[i][0] != '\0')
            printf("%c: %s\n", i, huffman->codigo[i]);
      }
}

TABELA_HUFFMAN *criarTabelaHuffman () {
   TABELA_HUFFMAN *huffman = (TABELA_HUFFMAN *)malloc(sizeof(TABELA_HUFFMAN));
   if (huffman != NULL) {
      for (int i = 0; i < NR_SIMBOLOS; i++)
         huffman->codigo[i][0] = '\0';
      huffman->arvore = NULL;
   }
   return huffman;
}

void liberarTabelaHuffman (TABELA_HUFFMAN **huffman) {
   if (huffman != NULL && *huffman != NULL) {
      apagar_arvore(&((*huffman)->arvore));
      free(*huffman);
      *huffman = NULL;
   }
}

void contagem_frequencia (int *freq, char *msg) {
   for (int i = 0; i < NR_SIMBOLOS; i++) 
      freq[i] = 0;
   for (int i = 0; msg[i] != '\0'; i++)
      freq[(int)msg[i]]++;
}

int criar_arv (TABELA_HUFFMAN *huffman, char *msg) {
   if (huffman != NULL && msg != NULL) {
      int freq[NR_SIMBOLOS];
      contagem_frequencia(freq, msg);
   
      HEAPD *heap = criarHeap();

      if (heap != NULL) {
         for (int i = 0; i < NR_SIMBOLOS; i++) {
            if (freq[i] > 0)
               inserir(heap, criarNO(criar_item(freq[i], i)));
         }
         while (tamanho(heap) > 1) {
            NO *esq = remover(heap);
            NO *dir = remover(heap);
            int freq = esq->item->frequencia + dir->item->frequencia;
            NO *novo = criarNO(criar_item(freq, '#'));
            novo->filho_esq_huff = esq;
            novo->filho_dir_huff = dir;
            inserir(heap, novo);
         }
         huffman->arvore = criar_arvore();
         huffman->arvore->raiz = remover(heap);
         apagarHeap(heap);
         return 1;
      }
   }
   return 0;
}

void criar_codigo_aux(TABELA_HUFFMAN *huffman, NO *no, char *cod, int fim) {
   if (no != NULL) {
      if (no->filho_esq_huff == NULL && no->filho_dir_huff == NULL) {
         int i;
         for (i = 0; i <= fim; i++) {
            huffman->codigo[(int) no->item->simbolo][i] = cod[i];
         }
         huffman->codigo[(int) no->item->simbolo][fim + 1] = '\0';
      } else {
         if (no->filho_esq_huff != NULL) {
            fim++;
            cod[fim] = '0';
            criar_codigo_aux(huffman, no->filho_esq_huff, cod, fim);
            fim--;
         }
         if (no->filho_dir_huff != NULL) {
            fim++;
            cod[fim] = '1';
            criar_codigo_aux(huffman, no->filho_dir_huff, cod, fim);
            fim--;
         }
      }
   }
}

void criar_codigo (TABELA_HUFFMAN *huffman) {
   char codigo[NR_SIMBOLOS];
   criar_codigo_aux(huffman, huffman->arvore->raiz, codigo, -1);
}

int compactarHuffman (char *msg, char **cod, TABELA_HUFFMAN **huffman) {
   return 0;
}

char *descompactarHuffman (char *msg, char **cod, TABELA_HUFFMAN **huffman) {
   return NULL;
}

#ifndef DICIONARIO_H
#define DICIONARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define TAM 3000

typedef struct dic {
  struct dic *esq,*dir;
  char palavra[TAM],significado[TAM];
}Dicionario;

extern Dicionario *raiz;

int verifica(char a[],char b[]);
void chama_busca(void);
void busca(void);
void inserir(Dicionario *temp);
void exportar_dicionario(Dicionario *ptr1, FILE *f);
void ler_dicionario(Dicionario *ptr1);
void ler_palavras(Dicionario *ptr1);
void preenche_dic(Dicionario *temp);
void regras_infos(void);
void base_dic2(FILE* arq);


#endif

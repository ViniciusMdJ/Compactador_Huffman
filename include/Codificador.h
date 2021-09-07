#ifndef CODIFICADOR_H
#define CODIFICADOR_H

#include "../include/Lista.h"
#include "../include/Arvore.h"

void Compacta(char *nomeArq);

static int *DefinePesos(char *nomeArq);

static tList *ListaArvores(int *pesos);

Arv *AlgoritimoHuffman(tList *listaArv);

char IndiceParada(int *pesos);

char **DefineCaminhos(Arv *arv, int *pesos);

#endif
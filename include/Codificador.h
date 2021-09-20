#ifndef CODIFICADOR_H
#define CODIFICADOR_H

#include "../include/Lista.h"
#include "../include/Arvore.h"

typedef struct codificador Cod;

void Compacta(char *nomeArq);

static void DefinePesos(char *nomeArq, Cod *dados);

static tList *ListaArvores(int *pesos);

static Arv *AlgoritimoHuffman(tList *listaArv);

static void DefineCaminhos(Cod *dados);

static void destroyCod(Cod *dados);

static int tamBitsArquivo(Cod *dados);

static void setCaminhoMapa(Cod *dados, int byte);

static void EscreveBitmapCompactado(Cod *dados, char *nomeArq);

static void EscreveCompactado(Cod *dados, char *nomeArq);

#endif
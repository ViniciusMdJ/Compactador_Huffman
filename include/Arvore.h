#ifndef ARVORE_H
#define ARVORE_H

#include "../include/Lista.h"
#include "../include/bitmap.h"
#include "../include/DecodificadorUtils.h"

typedef struct arvore Arv;

char arvGetChar(Arv *arv, BitComp *bc);

//A altura sempre que for chamada a função tem q ser 0(ZERO)
char *arvCaminho(Arv *arv, const char c, int altura);

Arv *arvCria(char c, int peso, Arv *esq, Arv *dir);

void arvLibera(void *arv);

int arvAltura(Arv *a);

int arvVazia(Arv *arv);

tList *arvInitList();

int arvCompara(void *x, void *y);

void arvImprime(void *arv);

int arvSomaPesos(Arv *arv1, Arv *arv2);

int arvQtdBits(Arv *arv);

void arvSerializa(bitmap *bm, Arv *arv);

Arv *arvDesserializa(BitComp *bc);

#endif
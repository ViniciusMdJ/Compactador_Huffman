#include "../include/Arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct arvore
{
    char c;
    int peso;
    Arv *esq;
    Arv *dir;
};

//A altura sempre que for chamada a função tem q ser 0(ZERO)
char *arvCaminho(Arv *arv, const char c, int altura)
{
    if (arvVazia(arv))
        return NULL;

    if (arvVazia(arv->esq) && arvVazia(arv->dir))
    {
        if (arv->c == c)
        {
            char *string = (char *)malloc(sizeof(char) * (altura + 1));
            string[0] = '\0';
            return string;
        }
        return NULL;
    }

    char *aux = NULL;
    aux = arvCaminho(arv->esq, c, altura + 1);
    if (aux)
    {
        aux[altura] = '0';
        return aux;
    }

    aux = arvCaminho(arv->dir, c, altura + 1);
    if (aux)
    {
        aux[altura] = '1';
        return aux;
    }

    return NULL;
}

Arv *arvCria(char c, int peso, Arv *esq, Arv *dir)
{
    Arv *arv = (Arv *)malloc(sizeof(Arv));

    arv->c = c;
    arv->peso = peso;
    arv->esq = esq;
    arv->dir = dir;

    return arv;
}

void arvLibera(void *x)
{
    Arv* arv = (Arv*) x;
    if (!arvVazia(arv))
    {
        arvLibera(arv->esq);
        arvLibera(arv->dir);
        free(arv);
    }
}

int arvVazia(Arv *arv)
{
    return arv ? 0 : 1;
}

int arvAltura(Arv* a)
{
    if(!arvVazia(a)){
        int qtdD, qtdE;
        qtdD = arvAltura(a->dir);
        qtdE = arvAltura(a->esq);
        return (qtdD > qtdE) ? (qtdD + 1) : (qtdE + 1);
    }
    return 0;
}

tList* arvInitList(){
    return NewList(sizeof(Arv), arvLibera);
}
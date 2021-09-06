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

//O caminho sairá na ordem inversa na string
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

    aux = arvCaminho(arv->esq, c, altura);
    if (!aux)
    {
        strcat(aux, "0");
        return aux;
    }

    aux = arvCaminho(arv->dir, c, altura);
    if (!aux)
    {
        strcat(aux, "1");
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

Arv *arvLibera(Arv *arv)
{
    if (!arvVazia(arv))
    {
        arvLibera(arv->esq);
        arvLibera(arv->dir);
        free(arv);
    }
    return NULL;
}

int arvVazia(Arv *arv)
{
    return arv ? 0 : 1;
}
#include "../include/Arvore.h"
#include "../include/Codificador.h"
#include "../include/DecodificadorUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct arvore
{
    char c;   // byte armazenado
    int peso; // quantidade de vezes que o byte aparece
    Arv *esq; // ponteiro para nó à esquerda
    Arv *dir; // ponteiro para nó à direita
};

char arvGetChar(Arv *arv, BitComp *bc)
{
    if (!arvVazia(arv))
    {
        if (arvVazia(arv->esq) && arvVazia(arv->dir))
        {
            return arv->c;
        }
        if (getBitArq(bc))
        {
            return arvGetChar(arv->dir, bc);
        }
        else
        {
            return arvGetChar(arv->esq, bc);
        }
    }
}

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
            string[altura] = '\0';
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
    Arv *arv = (Arv *)x;
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

int arvAltura(Arv *a)
{
    if (!arvVazia(a))
    {
        int qtdD, qtdE;
        qtdD = arvAltura(a->dir);
        qtdE = arvAltura(a->esq);
        return (qtdD > qtdE) ? (qtdD + 1) : (qtdE + 1);
    }
    return 0;
}

tList *arvInitList()
{
    return NewList(sizeof(Arv), arvLibera);
}

int arvCompara(void *x, void *y)
{
    Arv *arv1 = (Arv *)x;
    Arv *arv2 = (Arv *)y;

    if (arv2->peso < arv1->peso)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void arvImprime(void *a)
{
    Arv *arv = (Arv *)a;

    if (!arvVazia(arv))
    {
        if (arv->esq == NULL && arv->dir == NULL)
        {
            printf("1%c", arv->c);
        }
        else
        {
            printf("0");
        }
        arvImprime(arv->esq);
        arvImprime(arv->dir);
    }
}

void arvSerializa(bitmap *bm, Arv *arv)
{
    if (!arvVazia(arv))
    {
        if (arv->esq == NULL && arv->dir == NULL)
        {
            bitmapAppendLeastSignificantBit(bm, '1');
            //padrao de bits do byte na folha
            for (int i = 7; i >= 0; i--)
                bitmapAppendLeastSignificantBit(bm, (arv->c >> i));
        }
        else
        {
            bitmapAppendLeastSignificantBit(bm, '0');
        }
        arvSerializa(bm, arv->esq);
        arvSerializa(bm, arv->dir);
    }
}

Arv *arvDesserializa(BitComp *bc)
{
    Arv *new = malloc(sizeof(Arv));

    if (getBitArq(bc))
    {
        new->esq = NULL;
        new->dir = NULL;
        new->c = getByteArq(bc);
    }
    else
    {
        new->esq = arvDesserializa(bc);
        new->dir = arvDesserializa(bc);
    }
    return new;
}

int arvSomaPesos(Arv *arv1, Arv *arv2)
{
    return arv1->peso + arv2->peso;
}

int arvQtdBits(Arv *arv)
{
    if (!arvVazia(arv))
    {
        if (arvVazia(arv->esq) && arvVazia(arv->dir))
        {
            return 9;
        }
        return arvQtdBits(arv->esq) + arvQtdBits(arv->dir) + 1;
    }
    return 0;
}
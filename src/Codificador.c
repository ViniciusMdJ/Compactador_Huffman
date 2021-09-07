#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Codificador.h"
#include "../include/Lista.h"

void Compacta(char *nomeArq)
{
    int *pesos = DefinePesos(nomeArq);
    char parada = IndiceParada(pesos);

    tList *listaArv = ListaArvores(pesos);

    Arv *arvore = AlgoritimoHuffman(listaArv);
    //arvImprime(arvore);
    printf("tam bits arv: %d\n", arvQtdBits(arvore));

    char **caminhos = DefineCaminhos(arvore, pesos);

    /*for (int i = 0; i < 256; i++)
    {
        if (caminhos[i])
        {
            printf("%c %d %s\n", i, pesos[i], caminhos[i]);
        }
    }*/

    free(pesos);
}

int *DefinePesos(char *nomeArq)
{
    FILE *arq = fopen(nomeArq, "rb");
    if (!arq)
    {
        printf("Arquivo %s não aberto\n", nomeArq);
        exit(1);
    }

    int *pesos = malloc(sizeof(int) * 256);
    char byte;

    for (int i = 0; i < 256; i++)
    {
        pesos[i] = 0;
    }

    while (fread(&byte, 1, 1, arq) >= 1)
    {
        pesos[byte]++;
    }

    fclose(arq);
    return pesos;
}

tList *ListaArvores(int *pesos)
{
    tList *listaArv = arvInitList();

    //pra cada posição do vetor que for maior que 0
    //aloca uma arvore e chama addOrdered

    for (int i = 0; i < 256; i++)
    {
        if (pesos[i] > 0)
        {
            Arv *arvore = arvCria(i, pesos[i], NULL, NULL);
            AddOrdered(listaArv, arvore, arvCompara);
            //printf("adicionado %c\n", i);
            free(arvore);
        }
    }
    return listaArv;
}

Arv *AlgoritimoHuffman(tList *listaArv)
{
    Arv *arv1, *arv2, *aux;

    while (1)
    {
        arv1 = removeReturnBase(listaArv);
        arv2 = removeReturnBase(listaArv);
        if (arvVazia(arv2))
        {
            break;
        }

        aux = arvCria(1, arvSomaPesos(arv1, arv2), arv1, arv2);
        AddOrdered(listaArv, aux, arvCompara);
        free(aux);
    }

    return arv1;
}

char IndiceParada(int *pesos)
{
    for (int i = 0; i < 256; i++)
    {
        if (pesos[i] == 0)
        {
            pesos[i]++;
            return i;
        }
    }
    return -1;
}

char **DefineCaminhos(Arv *arv, int *pesos)
{
    char **Caminhos = malloc(sizeof(char *) * 256);

    for (int i = 0; i < 256; i++)
    {
        if (pesos[i] > 0)
        {
            Caminhos[i] = arvCaminho(arv, i, 0);
        }
        else
        {
            Caminhos[i] = NULL;
        }
    }

    return Caminhos;
}
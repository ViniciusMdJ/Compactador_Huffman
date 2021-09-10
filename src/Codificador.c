#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Codificador.h"
#include "../include/Lista.h"
#include "../include/bitmap.h"

struct codificador
{
    int *pesos;
    char **caminhos;
    char parada;
    Arv *arvore;
    bitmap *mapa;
};

void destroyCod(Cod *dados)
{
    if (dados)
    {
        if (dados->pesos)
            free(dados->pesos);
        if (dados->caminhos)
        {
            for (int i = 0; i < 256; i++)
            {
                if (dados->caminhos[i])
                {
                    free(dados->caminhos[i]);
                }
            }
            free(dados->caminhos);
        }
        arvLibera(dados->arvore);
        if (dados->mapa)
        {
            bitmapLibera(dados->mapa);
        }
        free(dados);
    }
}

int tamBitsArquivo(Cod *dados)
{
    int tam = 0, i;
    for (i = 0; i < 256; i++)
    {
        if (dados->pesos[i] > 0)
        {
            tam += strlen(dados->caminhos[i]) * dados->pesos[i];
        }
    }
    //soma 8 para o byte de parada depois da serialização da arvore
    tam += arvQtdBits(dados->arvore) + 8;

    return tam;
}

void Compacta(char *nomeArq)
{
    Cod *dados = malloc(sizeof(Cod));

    dados->pesos = DefinePesos(nomeArq);
    dados->parada = IndiceParada(dados->pesos);

    tList *listaArv = ListaArvores(dados->pesos);

    dados->arvore = AlgoritimoHuffman(listaArv);
    DestroyList(listaArv);

    DefineCaminhos(dados);
    /*for (int i = 0; i < 256; i++)
    {
        printf("byte %u: %d tam: %ld\n", i, dados->pesos[i], strlen(dados->caminhos[i]));
    }*/

    printf("tam bits arq: %d\n", tamBitsArquivo(dados));

    dados->mapa = bitmapInit(tamBitsArquivo(dados));

    EscreveBitmapCompactado(dados, nomeArq);

    EscreveCompactado(dados, nomeArq);

    printf("tamMax: %d, usado: %d\n", bitmapGetMaxSize(dados->mapa), bitmapGetLength(dados->mapa));

    destroyCod(dados);
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

    int aux;
    while (fread(&byte, 1, 1, arq) >= 1)
    {
        aux = byte & 0xff;
        //printf("byte: %u\n", aux);
        pesos[aux]++;
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

void DefineCaminhos(Cod *dados)
{
    dados->caminhos = malloc(sizeof(char *) * 256);

    for (int i = 0; i < 256; i++)
    {
        if (dados->pesos[i] > 0)
        {
            dados->caminhos[i] = arvCaminho(dados->arvore, i, 0);
        }
        else
        {
            dados->caminhos[i] = NULL;
        }
    }
}

void setCaminhoMapa(Cod *dados, int byte)
{
    if (dados->caminhos[byte] == NULL)
    {
        printf("nao tem caminho para o byte %c\n", byte);
        return;
    }
    char *caminho = dados->caminhos[byte];
    for (int i = 0; caminho[i] != '\0'; i++)
    {
        bitmapAppendLeastSignificantBit(dados->mapa, caminho[i]);
    }
}

void EscreveBitmapCompactado(Cod *dados, char *nomeArq)
{
    FILE *arq = fopen(nomeArq, "rb");
    if (!arq)
    {
        printf("Arquivo %s não aberto\n", nomeArq);
        exit(1);
    }

    arvSerializa(dados->mapa, dados->arvore);
    for (int i = 7; i >= 0; i--)
        bitmapAppendLeastSignificantBit(dados->mapa, (dados->parada >> i));

    char byte;
    int aux;
    while (fread(&byte, 1, 1, arq) >= 1)
    {
        aux = byte & 0xff;
        setCaminhoMapa(dados, aux);
    }

    printf("passou aqui\n");
    aux = dados->parada & 0xff;
    setCaminhoMapa(dados, aux);

    fclose(arq);
}

void EscreveCompactado(Cod *dados, char *nomeArq)
{
    char *compactado = malloc(sizeof(char) * (strlen(nomeArq) + 6));
    //copia o nome do arquivo e concatena o .comp
    strcpy(compactado, nomeArq);
    strcat(compactado, ".comp");
    FILE *arq = fopen(compactado, "wb");
    if (!arq)
    {
        printf("Arquivo %s nao aberto\n", compactado);
        exit(1);
    }
    //pega o tamanho em bytes do bitmap
    int tam = (bitmapGetLength(dados->mapa) + 7) / 8;
    fwrite(bitmapGetContents(dados->mapa), 1, tam, arq);

    fclose(arq);
    free(compactado);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Codificador.h"
#include "../include/Lista.h"
#include "../include/bitmap.h"

#define MEGABYTE 1048576

struct codificador
{
    int *pesos;
    char **caminhos;
    unsigned int qtdBytes;
    Arv *arvore;
    bitmap *mapa;
};

void Compacta(char *nomeArq)
{
    Cod *dados = malloc(sizeof(Cod));

    DefinePesos(nomeArq, dados);

    tList *listaArv = ListaArvores(dados);

    AlgoritimoHuffman(listaArv, dados);
    //arvImprime(dados->arvore);
    DestroyList(listaArv);

    DefineCaminhos(dados);

    printf("tam bits arq: %d\n", tamBitsArquivo(dados));

    EscreveCompactado(dados, nomeArq);

    destroyCod(dados);
}

void DefinePesos(char *nomeArq, Cod *dados)
{
    FILE *arq = fopen(nomeArq, "rb");
    if (!arq)
    {
        printf("Arquivo %s não aberto\n", nomeArq);
        exit(1);
    }

    dados->pesos = calloc(sizeof(int), 256);
    unsigned char byte;
    unsigned int aux = 0;

    while (fread(&byte, 1, 1, arq) >= 1)
    {
        //printf("byte: %u\n", aux);
        dados->pesos[byte]++;
        aux++;
    }
    dados->qtdBytes = aux;

    fclose(arq);
}

tList *ListaArvores(Cod *dados)
{
    tList *listaArv = arvInitList();

    //pra cada posição do vetor que for maior que 0
    //aloca uma arvore e chama addOrdered

    for (int i = 0; i < 256; i++)
    {
        if (dados->pesos[i] > 0)
        {
            Arv *arvore = arvCria(i, dados->pesos[i], NULL, NULL);
            AddOrdered(listaArv, arvore, arvCompara);
            free(arvore);
        }
    }
    return listaArv;
}

void AlgoritimoHuffman(tList *listaArv, Cod *dados)
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

    dados->arvore = arv1;
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
    unsigned int tam = 0, i;
    for (i = 0; i < 256; i++)
    {
        if (dados->pesos[i] > 0)
        {
            tam += strlen(dados->caminhos[i]) * dados->pesos[i];
        }
    }
    //soma 32 para um interio com aquantidade de bytes do arquivo depois da serialização da arvore
    tam += arvQtdBits(dados->arvore) + 32;

    return tam;
}

void EscreveCompactadoarq(Cod *dados, char *nomeArq)
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

void EscreveCompactado(Cod *dados, char *nomeArq){
    char *compactado = malloc(sizeof(char) * (strlen(nomeArq) + 6));
    //copia o nome do arquivo e concatena o .comp
    strcpy(compactado, nomeArq);
    strcat(compactado, ".comp");
    FILE *arqComp = fopen(compactado, "wb");
    if (!arqComp)
    {
        printf("Arquivo %s nao aberto\n", compactado);
        exit(1);
    }

    FILE *arqOrig = fopen(nomeArq, "rb");
    if (!arqOrig)
    {
        printf("Arquivo %s não aberto\n", nomeArq);
        exit(1);
    }

    unsigned int tamBitsTotal = tamBitsArquivo(dados); 
    unsigned int tamBytesTotal = (tamBitsTotal + 7) / 8;
    //1.048.576 = 1 megabytes
    //8.388.608 = bits em 1 megabytes
    int i;
    if(tamBytesTotal > MEGABYTE){
        dados->mapa = bitmapInit(MEGABYTE << 3);
    }
    else{
        dados->mapa = bitmapInit(tamBitsTotal);
    }
    arvSerializa(dados->mapa, dados->arvore);
    for(i = 31; i >= 0; i--){
        bitmapAppendLeastSignificantBit(dados->mapa, dados->qtdBytes >> i);
    }

    char *caminhoAtual;
    int tamCaminho = 0, bitcaminho = 0;

    do{
        int qtdBits; //quantidade de bits para escrever
        if(tamBytesTotal > MEGABYTE){
            qtdBits = MEGABYTE << 3;
        }
        else{
            qtdBits = tamBitsTotal;
        }

        if(!dados->mapa){
            dados->mapa = bitmapInit(qtdBits);
        }

        unsigned char byte;


        for(i = bitmapGetLength(dados->mapa); i < qtdBits; i++){
            if(tamCaminho == bitcaminho){
                fread(&byte, 1, 1, arqOrig);
                caminhoAtual = dados->caminhos[byte];
                tamCaminho = strlen(caminhoAtual);
                bitcaminho = 0;
            }
            bitmapAppendLeastSignificantBit(dados->mapa, caminhoAtual[bitcaminho]);
            bitcaminho++;
        }

        fwrite(bitmapGetContents(dados->mapa), 1, (bitmapGetLength(dados->mapa)+7) >> 3, arqComp);

        tamBytesTotal -= qtdBits >> 3;
        tamBitsTotal -= qtdBits;
        bitmapLibera(dados->mapa);
        dados->mapa = NULL;
    }while(tamBitsTotal > 0);


    free(compactado);
    fclose(arqComp);
    fclose(arqOrig);
}
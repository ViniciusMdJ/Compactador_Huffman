#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Decodificador.h"
#include "../include/Arvore.h"
#include "../include/DecodificadorUtils.h"

struct decodificador
{
    BitComp *bc;
    Arv *arv;
    FILE *desc;
    unsigned int qtd;
};

void Descompacta(char *nomeArq)
{
    Dec *dados = malloc(sizeof(Dec));
    dados->bc = InitBitComp(nomeArq);
    dados->arv = arvDesserializa(dados->bc);
    //arvImprime(dados->arv);
    dados->qtd = 0;
    for(int i = 0; i < 4; i++){
        dados->qtd <<= 8;
        dados->qtd += getByteArq(dados->bc);
    }
    //retira o ".comp" do nome do arquivo
    nomeArq[strlen(nomeArq) - 5] = '\0';
    dados->desc = fopen(nomeArq, "wb");
    if(!dados->desc){
        printf("Arquivo %s não aberto\n", nomeArq);
        exit(1);
    }
    Decodifica(dados);
    destroyDec(dados);
}

void Decodifica(Dec *dados)
{
    char byte;
    for(int i = 0; i < dados->qtd; i++)
    {
        byte = arvGetChar(dados->arv, dados->bc);
        fwrite(&byte, 1, 1, dados->desc);
    }
}

void destroyDec(Dec *dec)
{
    if (dec)
    {
        if (dec->bc)
        {
            DestroyBitComp(dec->bc);
        }
        arvLibera(dec->arv);
        if (dec->desc)
        {
            fclose(dec->desc);
        }
        free(dec);
    }
}
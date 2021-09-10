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
    char parada;
};

void Descompacta(char *nomeArq)
{
    Dec *dados = malloc(sizeof(Dec));
    dados->bc = InitBitComp(nomeArq);
    dados->arv = arvDesserializa(dados->bc);
    //arvImprime(dados->arv);
    dados->parada = getByteArq(dados->bc);
    //retira o ".comp" do nome do arquivo
    nomeArq[strlen(nomeArq) - 5] = '\0';
    dados->desc = fopen(nomeArq, "wb");
    Decodifica(dados);
    destroyDec(dados);
}

void Decodifica(Dec *dados)
{
    char byte;
    while (1)
    {
        byte = arvGetChar(dados->arv, dados->bc);
        if (byte == dados->parada)
        {
            break;
        }
        else
        {
            fwrite(&byte, 1, 1, dados->desc);
        }
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
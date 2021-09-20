#include "../include/DecodificadorUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bitComp
{
    FILE *arq;
    char byte;
    int index;
};

BitComp *InitBitComp(char *nomeArq)
{
    FILE *arq = fopen(nomeArq, "rb");
    if (!arq)
    {
        printf("Arquivo %s não aberto\n", nomeArq);
        exit(1);
    }

    BitComp *bc = malloc(sizeof(BitComp));
    bc->arq = arq;
    bc->index = 7;
    fread(&(bc->byte), 1, 1, bc->arq);

    return bc;
}

unsigned char getByteArq(BitComp *bc)
{
    char byte = 0;
    for (int i = 0; i < 8; i++)
    {
        byte = byte << 1;
        if (getBitArq(bc))
        {
            byte++;
        }
    }

    return byte;
}

int getBitArq(BitComp *bc)
{
    int bit = (bc->byte & (0x01 << bc->index));
    bc->index--;
    if (bc->index < 0)
    {
        bc->index = 7;
        fread(&(bc->byte), 1, 1, bc->arq);
    }
    return bit;
}

void DestroyBitComp(BitComp *bc)
{
    if (bc)
    {
        if (bc->arq)
        {
            fclose(bc->arq);
        }
        free(bc);
    }
}

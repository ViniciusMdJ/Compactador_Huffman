#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Codificador.h"

#define getBit(valor, bit) (valor & (0x01 << bit))

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Parametros insuficientes\n");
        exit(1);
    }
    //Compacta
    else if (strcmp(argv[1], "Compacta") == 0)
    {
        Compacta(argv[2]);
    }
    //Descompacta
    else if (strcmp(argv[1], "Descompacta") == 0)
    {
        //chama descompacta
    }
    else
    {
        printf("Parametro errado, insira Compacta ou Descompacta\n");
    }

    return 0;
}
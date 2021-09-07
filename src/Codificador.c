#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Codificador.h"
#include "../include/Lista.h"
#include "../include/Arvore.h"

void Compacta(char* nomeArq){

    int *pesos = DefinePesos(nomeArq);

    for(int i=0;i<256; i++){
        if(pesos[i] > 0){
            printf("byte %c: %d\n", i, pesos[i]);
        }
    }




    free(pesos);
}

int* DefinePesos(char* nomeArq){
    FILE* arq = fopen(nomeArq, "rb");
    if(!arq){
        printf("Arquivo %s não aberto\n", nomeArq);
        exit(1);
    }

    int *pesos = malloc(sizeof(int) * 256);
    char byte;

    for(int i = 0; i < 256; i++){
        pesos[i] = 0;
    }

    while(fread(&byte, 1, 1, arq) >= 1){
        pesos[byte]++;
    }
    
    return pesos;
}

tList* ListaArvores(int* pesos){
    tList* listaArv = arvInitList();

    //fazer função para comparar arvore e rotornar 1 se ela for menor
    //pra cada posição do vetor que for maior que 0
    //aloca uma arvore e chama addOrdered



}
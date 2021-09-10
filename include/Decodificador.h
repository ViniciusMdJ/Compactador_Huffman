#ifndef DECODIFICADOR_H
#define DECODIFICADOR_H

typedef struct decodificador Dec;

void Descompacta(char *nomeArq);

static void Decodifica(Dec *dados);

static void destroyDec(Dec *dec);

#endif
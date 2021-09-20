#ifndef DECODIFICADORUTILS_H
#define DECODIFICADORUTILS_H

typedef struct bitComp BitComp;

BitComp *InitBitComp(char *nomeArq);

unsigned char getByteArq(BitComp *x);

int getBitArq(BitComp *x);

void DestroyBitComp(BitComp *bc);

#endif
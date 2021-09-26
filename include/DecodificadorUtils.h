#ifndef DECODIFICADORUTILS_H
#define DECODIFICADORUTILS_H

/**
 * @brief TAD que manipula os bits do arquivo compactado.
*/ 
typedef struct bitComp BitComp;

/**
 * @brief Inicializa o struct para manipular os bits do arquivo.
 * @param *caminhoArq Caminho do arquivo a ser aberto.
 * @pre A string deve conter o caminho para abrir o arquivo.
 * @post Se o arquivo não for aberto ele terminha o programa com erro, senão retorna o ponteiro normalmente.
 * @return Ponteiro do struct alocado.
*/
BitComp *InitBitComp(char *caminhoArq);

/**
 * @brief Pega os proximos 8 bits do arquivo.
 * @param *x Struct com os dados.
 * @pre O struct deve ja estar inicializado, dever do usuario.
 * @post O struct ja atualiza o arquivo para o proximo bit a ser lido.
 * @return O byte lido do arquivo, 0 para zero.
*/
unsigned char getByteArq(BitComp *x);

/**
 * @brief Pega os proximo bit do arquivo.
 * @param *x Struct com os dados.
 * @pre O struct deve ja estar inicializado, dever do usuario.
 * @post O struct ja atualiza o arquivo para o proximo bit a ser lido.
 * @return O bit lido do arquivo.
*/
int getBitArq(BitComp *x);

/**
 * @brief Libera o struct alocado com o arquivo.
 * @param *x Struct com os dados.
 * @pre O struct deve ja estar inicializado, dever do usuario.
 * @post Struct todo liberado.
*/
void DestroyBitComp(BitComp *bc);

#endif
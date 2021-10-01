#ifndef DECODIFICADOR_H
#define DECODIFICADOR_H

// Estrutura auxiliar que reúne as informações necessárias para descompactar.
typedef struct decodificador Dec;

/**
 * @brief Inicializa o struct Dec.
 * @return Retorna o ponteiro do struct alocado.
*/
static Dec *InitDec();

/**
 * @brief Descompacta um arquivo .comp.
 * @param nomeArq String do nome do arquivo.
 * @pre nomeArq tem o caminho correto para o arquivo.
 * @post  Arquivo descompactado como o esperado.
*/
void Descompacta(char *nomeArq);

/**
 * @brief Escreve no arquivo, cujo ponteiro está na estrutura Dec, o mapa de bits, também contido em Dec.
 * @param dados Ponteiro para a estrutura auxiliar Dec.
 * @pre dados preenchido corretamente e != NULL.
 * @post Mapa de bits escrito como esperado.
*/
static void Decodifica(Dec *dados);

/**
 * @brief Libera a estrutura auxiliar Dec, inclusive seus componentes.
 * @param dec Ponteiro para a estrutura Dec.
*/
static void destroyDec(Dec *dec);

#endif
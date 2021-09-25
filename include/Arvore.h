#ifndef ARVORE_H
#define ARVORE_H

#include "../include/Lista.h"
#include "../include/bitmap.h"
#include "../include/DecodificadorUtils.h"

// Estrutura da árvore
typedef struct arvore Arv;

/**
 * @brief Caminha pela árvore para retornar um byte que corresponde ao byte lido.
 * @param arv Árvore binária de caracteres.
 * @param bc Ponteiro para a estrutura auxiliar BitComp.
 * @pre Árvore binária construída e bc preenchido corretamente.
 * @return Byte correspondente na árvore.
*/
char arvGetChar(Arv *arv, BitComp *bc);

//A altura sempre que for chamada a função tem q ser 0(ZERO)
/**
 * @brief Consulta o caminho de um byte na árvore binária.
 * @param arv Árvore Binária.
 * @param c Byte à ser procurado.
 * @param altura Altura atual da busca.
 * @pre altura = 0, arv definida corretamente.
 * @return String com o caminho para o byte na árvore (0 -> esquerda, 1 -> direita).
*/
char *arvCaminho(Arv *arv, const char c, int altura);

/**
 * @brief Aloca e preenche um nó da árvore binária.
 * @param c Byte do nó.
 * @param peso Número de vezes que o byte aparece.
 * @param esq Ponteiro para o nó à esquerda.
 * @param dir Ponteiro para o nó à direita.
 * @return Nó da árvore criado.
*/
Arv *arvCria(char c, int peso, Arv *esq, Arv *dir);

/**
 * @brief Libera uma árvore e seus nós da memória.
 * @param arv Árvore à ser liberada.
*/
void arvLibera(void *arv);

/**
 * @brief Calcula a altura de uma árvore binária.
 * @param a Árvore binária.
 * @return Altura da árvore.
*/
int arvAltura(Arv *a);

/**
 * @brief Verifica se o ponteiro de uma árvore é válido.
 * @param arv Árvore.
 * @return 1 Se inválido, 0 Senão.
*/
int arvVazia(Arv *arv);

/**
 * @brief Inicia uma lista de árvores. 
 * @return Ponteiro para a lista de árvores.
*/
tList *arvInitList();

/**
 * @brief Calcula se um nó x tem peso maior ou igual que um nó y.
 * @param x Nó de uma árvore.
 * @param y Nó de uma árvore.
 * @pre x e y não são nulos (são válidos).
 * @return 1 Se tiver peso maior ou igual, 0 senão.
*/
int arvCompara(void *x, void *y);

/**
 * @brief Imprime a serialização de uma árvore binária.
 * @param arv Ponteiro para a árvore binária.
*/
void arvImprime(void *arv);

/**
 * @brief Calcula a soma dos pesos de duas árvores binárias.
 * @param arv1 Árvore binária.
 * @param arv2 Árvore binária.
 * @pre arv1 != NULL, arv2 != NULL.
 * @return Soma dos pesos.
*/
int arvSomaPesos(Arv *arv1, Arv *arv2);

/**
 * @brief Calcula a quantidade de bits necessária para a serialização de uma árvore binária.
 * @param arv Ponteiro para a árvore binária.
 * @return Quantidade de bits para a serialização da árvore.
*/
int arvQtdBits(Arv *arv);

/**
 * @brief Coloca a serialização de uma árvore binária em um mapa de bits.
 * @param bm Ponteiro para o mapa de bits.
 * @param arv Ponteiro para a árvore binária.
 * @pre bm != NULL.
*/
void arvSerializa(bitmap *bm, Arv *arv);

/**
 * @brief Dada uma serialização de uma árvore binária em um arquivo, constrói a árvore.
 * @param bc Ponteiro para a estrutura auxiliar BitComp.
 * @pre bc preenchido corretamente e != NULL.
 * @post Ponteiro para o arquivo avançado.
 * @return Ponteiro para a árvore binária construída.
*/
Arv *arvDesserializa(BitComp *bc);

#endif
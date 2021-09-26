#ifndef CODIFICADOR_H
#define CODIFICADOR_H

#include "../include/Lista.h"
#include "../include/Arvore.h"


/**
 * @brief TAD que contem os dados para compactar o arquivo. 
*/ 
typedef struct codificador Cod;

/**
 * @brief Compacta o arquivo o arquivo com o nome passado.
 * @param *nomeArq O nome do arquivo a ser compactado.
 * @pre O arquivo deve existir, verificado na função.
 * @post O arquivo compactado, o nome é o mesmo com a extenção '.comp'.
*/
void Compacta(char *nomeArq);

/**
 * @brief Define a quantidade de vezes que cada byte aparece no arquivo.
 * @param *nomeArq O nome do arquivo a ser compactado.
 * @param *dados Struct com os dados para compactar o arquivo.
 * @pre O struct deve ja estar inicializado, dever do usuario.
 * @post Aloca um vetor de 256 posições com a quantidade de vezes que cada byte apareceu.
*/
static void DefinePesos(char *nomeArq, Cod *dados);

/**
 * @brief Cria a lista de arvores com os pesos dos bytes.
 * @param *dados Struct com os dados para compactar o arquivo.
 * @pre O struct e o vetor com os pesos devem ja estar inicializados, dever do usuario.
 * @post Lista de arvores com os pesos e os bytes, todas são folha e raiz ao mesmo tempo.
 * @return Lista de arvores com os pesos.
*/
static tList *ListaArvores(Cod *dados);

/**
 * @brief Execulta o algoritimo de Huffman na lista passada e armazena no dados.
 * @param *listaArv Lista de arvores com pesos e bytes.
 * @param *dados Struct com os dados para compactar o arquivo.
 * @pre Lista e dados devem estar alocados, dever do usuario.
 * @post A lista fica vazia e a arvore de Huffman é colocada no dados.
*/
static void AlgoritimoHuffman(tList *listaArv, Cod *dados);

/**
 * @brief Define os caminhos da avore para cada byte que aparece no arquivo.
 * @param *dados Struct com os dados para compactar o arquivo.
 * @pre A arvore ja deve estar criada, dever do usuario.
 * @post É criado um vetor de strings com os caminho para os bytes na arvore.
*/
static void DefineCaminhos(Cod *dados);

/**
 * @brief Libera a memoria do struct Cod.
 * @param *dados Struct com os dados para compactar o arquivo.
 * @pre o struct deve estar alocado, dever do usuario.
 * @post Toda a memoria do struct liberada.
*/
static void destroyCod(Cod *dados);

/**
 * @brief Calcula a quantidade de bits nescessarios para compactar o arquivo.
 * @param *dados Struct com os dados para compactar o arquivo.
 * @pre Os caminhos e os pesos devem estar definidos, dever do usuario.
 * @post É colocado no dados a quantidade de bits do arquivo compactado.
*/
static int tamBitsArquivo(Cod *dados);

/**
 * @brief 
 * @param 
 * @pre 
 * @post 
 * @return 
*/
static void EscreveCompactado(Cod *dados, char *nomeArq);

#endif
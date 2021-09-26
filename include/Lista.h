#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief TAD de Lista generica.
*/
typedef struct list tList;

/**
 * @brief Função generica com um ponteiro para ser passada em alguma funções do TAD.
 * @param *x ponteiro generico a ser recebido, info da celula.
 * @pre A função tem que fazer os casting's nescessarios.
*/
typedef void (*fptrGeneric)(void *x);

/**
 * @brief Função generica com dois ponteiros para ser passada em alguma funções do TAD.
 * @param *x ponteiro do dado da celula.
 * @param *y ponteiro passado para a função.
 * @pre A função tem que fazer os casting's nescessarios.
*/
typedef void (*fptrGeneric2)(void *x, void *y);

/**
 * @brief Função generica para comparar dois ponteiros.
 * @param *x info da celula da lista.
 * @param *find Ponteiro passado na função a ser comparado.
 * @pre A função tem que fazer os casting's nescessarios.
 * @return Deve retornar 0 se falso, e diferente de zero pra verdadeiro.
*/
typedef int (*fptrCompare)(void *x, void *find);

/**
 * @brief Inicializa uma nova lista generida.
 * @param DataSize Tamanho do ponteiro a ser alocado na lista.
 * @param Destroy Função para liberar o ponteiro alocado.
 * @return Um ponteiro de tLista alocado, com o tamanho e a função pra liberar salvos.
*/
tList *NewList(int DataSize, fptrGeneric Destroy);

/**
 * @brief Libera a lista inteira alocada.
 * @param *list Lista generica.
 * @pre Lista deve estar alocada.
 * @post Lista toda liberada.
*/
void DestroyList(tList *list);

/**
 * @brief Adiciona o ponteiro passado no inicio da lista passada.
 * @param *list Lista generica.
 * @param *data Ponteiro a ser inserido na lista.
 * @pre A lista passada tem que ser valida, é verificado dentro da função, e o ponteiro passado tem que ter o tamanho passado quando foi iniciado essa lista, responsabilidade do usuario.
 * @post Lista com o ponteiro colocado no inicio, usuario deve se encarregar de liberar o anterior.
*/
void addBase(tList *list, void *data);

/**
 * @brief Adiciona o ponteiro passado no final da lista passada.
 * @param *list Lista generica.
 * @param *data Ponteiro a ser inserido na lista.
 * @pre A lista passada tem que ser valida, é verificado dentro da função, e o ponteiro passado tem que ter o tamanho passado quando foi iniciado essa lista, responsabilidade do usuario.
 * @post Lista com o ponteiro alocado inserido no final, usuario deve se encarregar de liberar o anterior.
*/
void addEnd(tList *list, void *data);

/**
 * @brief Adiciona um novo ponteiro na lista osdenado de acordo com a função passada.
 * @param *list Lista generica.
 * @param *data Ponteiro a ser inserido na lista.
 * @param function Função para comparar os dados da lista e o novo a ser inserido, ela deve retornar 1 caso o dados deva ser inserido naquel lugar.
 * @pre A lista passada tem que ser valida, é verificado dentro da função.
 * @post Lista com o novo dados inserido ordenado de acordo com a função.
*/
void AddOrdered(tList *list, void *data, fptrCompare function);

/**
 * @brief Remove e libera o primeiro ponteiro da lista.
 * @param *list Lista generica.
 * @pre A lista passada tem que ser valida, é verificado dentro da função.
 * @post Lista com a primeira celula retirada.
*/
void RemoveBase(tList *list);

/**
 * @brief Remove e e retorna o primeiro ponteiro da lista.
 * @param *list Lista generica.
 * @pre A lista passada tem que ser valida, é verificado dentro da função.
 * @post Lista com a primeira celula retirada. 
 * @return O ponteiro do primeiro dado da lista.
*/
void *removeReturnBase(tList *list);

/**
 * @brief Remove e libera o ultimo ponteiro da lista.
 * @param *list Lista generica.
 * @pre A lista passada tem que ser valida, é verificado dentro da função.
 * @post Lista com a última celula retirada.
*/
void RemoveEnd(tList *list);

/**
 * @brief Função que percorre por toda a lista passando o ponteiro da informação da célula pra função.
 * @param *list Lista generica.
 * @param genericFunction Função generica que manipula o ponterio do dado.
 * @pre A lista e a função passada tem que ser valida, é verificado dentro da função.
 * @post Lista com os dados manipulados de acordo com a função
*/
void genericFunctionList(tList *list, fptrGeneric genericFunction);

/**
 * @brief Função que passa por toda a lista passando o ponteiro da informação da célula pra função passada.
 * @param *list Lista generica.
 * @param *find Ponteiro a ser passado tambem para a função.
 * @param genericFunction Função generica que manipula o ponterio do dado junto com ponteiro passado para função.
 * @pre A lista e a função passada tem que ser valida, é verificado dentro da função.
 * @post Lista com os dados manipulados de acordo com a função.
*/
void genericFunction2List(tList *list, void *find, fptrGeneric2 genericFunction);

/**
 * @brief Conta de acordo com a função passada.
 * @param *list Lista generica.
 * @param *find Ponteiro a ser passado tambem para a função.
 * @param funcition Função para comparar os ponteiros e devolver um inteiro.
 * @pre A lista e a função passada tem que ser valida, é verificado dentro da função.
 * @post Lista não alterada.
 * @return Soma dos retornos da função.
*/
int Counter(tList *list, void *find, fptrCompare function);

/**
 * @brief Procura o primeiro item comparado com o ponteiro passado de acordo com a função.
 * @param *list Lista generica.
 * @param *find Ponteiro a ser passado tambem para a função.
 * @param function Função para comparar os ponteiros e devolver um inteiro.
 * @post Lista não alterada.
 * @return Primeiro ponteiro que a função retornar verdadeiro, ou NULL caso não ache.
*/
void *SearchList(tList *list, void *find, fptrCompare function);

/**
 * @brief Procura o primeiro item comparado com o ponteiro passado de acordo com a função e remove ele da lista.
 * @param *list Lista generica.
 * @param *find Ponteiro a ser passado tambem para a função.
 * @param function Função para comparar os ponteiros e devolver um inteiro.
 * @post Lista sem o item caso achado.
 * @return Primeiro ponteiro que a função retornar verdadeiro, ou NULL caso não ache.
*/
void *SearchRemoveList(tList *list, void *find, fptrCompare function);

/**
 * @brief Checa se o ponteiro é valido.
 * @param *x Ponteiro qualquer.
 * @pre Ponteiro ser valido, checado na função.
 * @post Se o ponteiro for NULL interrompe o programa com exit().
*/
void Check(void *x);


#endif //LISTA_H
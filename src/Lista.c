#include "Lista.h"

typedef struct ListNode tListNode;

struct ListNode
{
    void *info;
    tListNode *next;
    tListNode *prev;
};

struct list
{
    int DataSize;
    tListNode *first;
    tListNode *last;
    fptrGeneric FreeFunc;
};

tList *NewList(int DataSize, fptrGeneric destroy)
{
    tList *new = malloc(sizeof(tList));

    Check(new);

    new->DataSize = DataSize;
    new->first = NULL;
    new->last = NULL;
    new->FreeFunc = destroy;

    return new;
}

void DestroyList(tList *list)
{
    tListNode *a;

    while (list->first)
    {
        a = list->first;
        list->first = a->next;
        if (list->FreeFunc)
        {
            list->FreeFunc(a->info);
        }
        free(a->info);
        free(a);
    }
    free(list);
}

void addBase(tList *list, void *data)
{
    Check(list);

    tListNode *newData = malloc(sizeof(tListNode));
    Check(newData);

    newData->info = malloc(list->DataSize);
    memcpy(newData->info, data, list->DataSize);

    if (list->first)
    {
        list->first->prev = newData;
    }
    newData->prev = NULL;
    newData->next = list->first;
    list->first = newData;

    if (list->last == NULL)
    {
        list->last = newData;
    }
}

void addEnd(tList *list, void *data)
{
    Check(list);

    tListNode *newData = malloc(sizeof(tListNode));
    Check(newData);

    newData->info = malloc(list->DataSize);
    memcpy(newData->info, data, list->DataSize);
    newData->next = NULL;

    if (list->first == NULL)
    {
        list->first = newData;
    }

    if (list->last)
    {
        list->last->next = newData;
    }
    newData->prev = list->last;
    list->last = newData;
}

void AddOrdered(tList* list, void *data, fptrCompare function){
    Check(list);

    tListNode *newData = malloc(sizeof(tListNode));
    Check(newData);

    newData->info = malloc(list->DataSize);
    memcpy(newData->info, data, list->DataSize);

    tListNode* p;
    for(p = list->first; p != NULL; p = p->next){
        if(function(p->info, data)){
            break;
        }
    }

    if(!list->first){
        list->first = newData;
    }

    if(p){
        newData->next = p;
        newData->prev = p->prev;
        p->prev->next = newData;
        p->prev = newData;
    }
    else{
        if (list->last){
            list->last->next = newData;
        }
        newData->prev = list->last;
        list->last = newData;
        newData->next = NULL;
    }
}

void RemoveBase(tList *list)
{
    Check(list);

    if (list->first == NULL)
    {
        return;
    }

    tListNode *remove = list->first;

    if (list->first == list->last)
    {
        list->first = NULL;
        list->last = NULL;
    }
    else
    {
        list->first = remove->next;
        list->first->prev = NULL;
    }

    if (list->FreeFunc)
    {
        list->FreeFunc(remove->info);
    }

    free(remove->info);
    free(remove);
}

void *removeReturnBase(tList *list)
{
    Check(list);

    if (list->first == NULL)
    {
        return NULL;
    }

    tListNode *remove = list->first;
    void *aux = remove->info;

    if (list->first == list->last)
    {
        list->first = NULL;
        list->last = NULL;
    }
    else
    {
        list->first = remove->next;
        list->first->prev = NULL;
    }

    free(remove);
    return aux;
}

void RemoveEnd(tList *list)
{
    Check(list);

    if (list->last == NULL)
    {
        return;
    }

    tListNode *remove = list->last;

    if (list->first == list->last)
    {
        list->first = NULL;
        list->last = NULL;
    }
    else
    {
        remove->prev->next = NULL;
        list->last = remove->prev;
    }

    if (list->FreeFunc)
    {
        list->FreeFunc(remove->info);
    }

    free(remove->info);
    free(remove);
}

void genericFunctionList(tList *list, fptrGeneric genericFunction)
{
    if (!genericFunction)
    {
        printf("Funcao nao valida\n");
        return;
    }
    Check(list);

    tListNode *node;

    for (node = list->first; node != NULL; node = node->next)
    {
        genericFunction(node->info);
    }
}


void genericFunction2List(tList *list, void *data, fptrGeneric2 genericFunction){
    if (!genericFunction)
    {
        printf("Funcao nao indicada\n");
        return;
    }
    Check(list);

    tListNode *node;

    for (node = list->first; node != NULL; node = node->next)
    {
        genericFunction(node->info, data);
    }
}

int Counter(tList *list, void *find, fptrCompare function){
    if (!function)
    {
        printf("Funcao nao indicada\n");
        return 0;
    }
    Check(list);

    tListNode *p;
    int qtd = 0;

    for (p = list->first; p != NULL; p = p->next)
    {
        qtd += function(p->info, find);
    }

    return qtd;
}


void *SearchList(tList *list, void *find, fptrCompare function)
{
    tListNode *p;

    for (p = list->first; p != NULL; p = p->next)
    {
        if (function(p->info, find) == 1)
        {
            return p->info;
        }
    }

    return NULL;
}

void *SearchRemoveList(tList *list, void *find, fptrCompare function)
{
    tListNode *p;
    void *returned;

    for (p = list->first; p != NULL; p = p->next)
    {
        if (function(p->info, find))
        {
            returned = p->info;
            p->prev->next = p->next;
            free(p);
            return returned;
        }
    }

    return NULL;
}

void Check(void *x)
{
    if (x == NULL)
    {
        printf("Memoria nao alocada\n");
        exit(1);
    }
}
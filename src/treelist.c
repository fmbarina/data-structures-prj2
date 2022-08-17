#include "tree.h"
#include "treelist.h"
#include <stdlib.h>
#include <stdio.h>
#include "assertr.h"

typedef struct cel_st tCel;

struct cel_st
{
    tCel *prox;
    tTree *tree;
};

struct st_tree_list
{
    tCel *prim;
    tCel *ult;
};

tTreeList *tree_list_inic()
{
    tTreeList *lista = (tTreeList *)malloc(sizeof(tTreeList));
    lista->prim = NULL;
    lista->ult = NULL;
    return lista;
}

void tree_list_free(tTreeList* list)
{
    assertr(list != NULL, "free mas tTreeList nunca foi alocado");

    tCel * cel = list->prim;
    while (cel != NULL)
    {
        tCel * prox = cel->prox;
        free(cel);
        cel = prox;
    }
    free(list);
}

void tree_list_insert(tTreeList *lista, tTree *tree)
{
    tCel *cel = (tCel *)malloc(sizeof(tCel));
    cel->tree = tree;
    
    /* If the list is empty */
    if (lista->prim == NULL)
    {
        lista->prim = cel;
        lista->ult = cel;
    }
    else
    {
        /* Search where to insert cell */
        tCel *i;
        tCel *ant = NULL;
        for (i = lista->prim; i != NULL && tree_weight(tree) > tree_weight(i->tree); i = i->prox)
            ant = i;

        /* Insert */
        if (ant)
            ant->prox = cel;
        
        cel->prox = i;

        /* When inserted at beggining */
        if (ant == NULL)
        {
            lista->prim = cel;
        }
        /* When inserted at end */
        else if (i == NULL)
        {
            lista->ult = cel;
        }
    }
}

void tree_list_remove(tTreeList *lista, tTree *tree)
{
    tCel *ant = NULL;
    for (tCel *i = lista->prim; i != NULL; i = i->prox)
    {
        if (i->tree == tree)
        {

            /* Single element in the list */
            if (lista->prim == lista->ult)
            {
                lista->prim = NULL;
                lista->ult = NULL;
            }

            /* First element in the list */
            else if (lista->prim == i)
            {
                lista->prim = i->prox;
            }

            /* Last element in the list */
            else if (lista->ult == i)
            {
                lista->ult = ant;
                lista->ult->prox = NULL;
            }

            /* Default case/middle element in the list */
            else
            {
                ant->prox = i->prox;
            }

            free(i);
            return;
        }
        ant = i;
    }
    printf("Árvore não encontrada ou lista vazia!\n");
}

void tree_list_print(tTreeList *lista)
{
    if (lista->prim == NULL && lista->ult == NULL)
    {
        printf("Lista vazia!\n");
    }
    else
    {
        for (tCel *i = lista->prim; i != NULL; i = i->prox)
        {
            printf("Peso: %d\n", tree_weight(i->tree));
        }
    }
    printf("\n");
}

tTree *huffman_algorithm(tTreeList *l_arv)
{
    tTree *T1, *T2, *TR;
    while (!is_unitary(l_arv))
    {
        T1 = l_arv->prim->tree;
        T2 = l_arv->prim->prox->tree;
        TR = tree_init('\0', tree_weight(T1) + tree_weight(T2), T1, T2);
        tree_list_insert(l_arv, TR);
        tree_list_remove(l_arv, T1);
        tree_list_remove(l_arv, T2);
    }
    return TR; 
}

int is_unitary(tTreeList *lista_arv)
{
    /* There are two cases in which prim == ult */

    /* When list is empty */
    if (lista_arv->prim == NULL)
        return 0;                               
    
    /* When list has only a single item */
    return (lista_arv->prim == lista_arv->ult); 
}

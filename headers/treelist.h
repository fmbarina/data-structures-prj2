/**
 * @file treelist.h
 * @author Felipe M. Barina
 * @author Vitor F. Calmon
 * @brief Manage singly linked list of trees with sentinel.
 * @date 2022-08-16 
 * 
 */
#ifndef LISTA_ARV_H_
#define LISTA_ARV_H_

#include "tree.h"

typedef struct st_tree_list tTreeList;

/**
 * @brief Create empty tree list.
 * 
 * @return tTreeList* Tree list created. 
 */
tTreeList * tree_list_inic();

void tree_list_free(tTreeList* list);

/**
 * @brief Insert tree in tree list with respect to ascending weight order.
 * @param list List with the new tree.
 * @param tree Tree to be inserted.
 */
void tree_list_insert(tTreeList * list, tTree * tree);

/**
 * @brief Remove tree from tree list.
 * 
 * @param list List of trees without the tree passed.
 * @param tree Tree to be removed.
 */
void tree_list_remove(tTreeList * list, tTree * tree);

/**
 * @brief Print tree list.
 * 
 * @param list List of trees to be printed.
 */
void tree_list_print(tTreeList * list);

/**
 * @brief Check if tree list only contains one tree.
 * 
 * @param list List of trees to be checked.
 * @return int If tree list is unitary (1), if not (0).
 */
int is_unitary(tTreeList * list);

/**
 * @brief Apply the Huffman algorithm to the tree list.
 * 
 * @param list List of trees to be optimized.
 * @return tTree* Optimized tree.
 */
tTree * huffman_algorithm(tTreeList * list);

#endif /* LISTA_ARV_H_ */
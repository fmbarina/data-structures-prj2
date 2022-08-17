/**
 * @file tree.h
 * @author Felipe M. Barina
 * @author Vitor F. Calmon
 * @brief Manage trees.
 * @date 2022-08-16
 * 
 */
#ifndef ARVORE_H_
#define ARVORE_H_

#include <stdio.h>
#include "bits.h"

typedef struct tree_st tTree;

/**
 * @brief Create empty tree.
 * 
 * @return tTree* Empty tree created.
 */
tTree* tree_init_empty();

/**
 * @brief Create tree with passed parameters.
 * 
 * @param c Character of tree.
 * @param weight Frequency of tree's character.
 * @param e Tree to the left.
 * @param d Tree to the right.
 * @return tTree* Tree created with passed parameters.
 */
tTree* tree_init (char c, unsigned long long int weight, tTree* e, tTree* d);

/**
 * @brief Free the memory allocated in by the tree.
 * 
 * @param a Tree to be freed.
 * @return tTree* Tree freed.
 */
tTree* tree_free (tTree* tree);

/**
 * @brief Check if tree is empty.
 * 
 * @param tree The tree.
 * @return int If tree is empty (1), if not (0).
 */
int tree_empty (tTree* tree);

/**
 * @brief Print the tree with their informations.
 * 
 * @param tree Tree to be printed.
 */
void tree_print (tTree* tree);

/**
 * @brief Return tree's info (character).
 * 
 * @param tree Tree.
 * @return char Tree's info (character).
 */
char tree_info (tTree* tree);

/**
 * @brief Check if tree is a leaf (does not have other trees below)
 * 
 * @param tree Tree to be checked.
 * @return int If tree is empty (1), if not (0).
 */
int tree_is_leaf(tTree* tree);

/**
 * @brief Return tree's weight.
 * 
 * @param tree Tree.
 * @return int Tree's weight.
 */
int tree_weight(tTree * tree);

/**
 * @brief Serialize the given tree to a sequence of bits.
 * 
 * @param tree Tree to be serialized.
 * @return tBits* Sequence of bits.
 */
tBits* tree_serialize(tTree* tree);

/**
 * @brief Deserialize the given sequence of bits into a tree.
 * 
 * @param bs tBits sequence of bits.
 * @return tTree* Tree.
 */
tTree* tree_deserialize(tBits* bs);

/**
 * @brief Navegate through the tree.
 * 
 * @param tree Tree.
 * @param dir Direction to navegate: right (1), or left (0).
 * @return tTree* Tree where the navegation has taken.
 */
tTree* tree_nav(tTree* tree, unsigned char dir);

#endif /* ARVORE_H_ */

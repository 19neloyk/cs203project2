#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "restaurant.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
#include "ArrayList.h"


/**
 * @struct BTNode
 * BinaryTree node that holds left and right nodes and holds a restaurant 
 * 
*/
typedef struct BTNode_struct{
    struct BTNode_struct* left;
    struct BTNode_struct* right;
    Restaurant* rest;

} BTNode;

/**
 * @struct BinaryTree
 * BinaryTree that holds root BinaryTree Node
 * 
*/
typedef struct BinaryTree_struct{
    BTNode* root;

} BinaryTree; 


/**
 * Creates a binary tree (deals with malloc)
 */
BinaryTree* createBT();

/**
 * Creates a binary tree node (deals with malloc)
 * @param r the restaurant we want to create a node of
 */
BTNode* createBTNode(Restaurant* r);

/**
* Insert element into binary tree lexicographically based on name
* @param r pointer to restaraunt to insert into the tree
* @param tree the tree we would like to insert into
*/
void insertInBTName(Restaurant* r, BinaryTree* tree);


/**
* Insert element into binary tree lexicographically based on location
* @param r pointer to restaraunt to insert into the tree
* @param tree the tree we would like to insert into
*/
void insertInBTLocation(Restaurant* r, BinaryTree* tree);

/**
 * Remove element from binary tree lexicographically based on name
 * @param r pointer to restaraunt to remove from the tree
 * @param tree the tree we would like to remove from
*/
void removeFromBTName(Restaurant* r, BinaryTree* tree);

/**
 * Remove element from binary tree lexicographically based on location
 * @param r pointer to restaraunt to remove from the tree
 * @param tree the tree we would like to remove from
*/
void removeFromBTLocation(Restaurant* r, BinaryTree* tree);

/**
 * Print BT in order
 * @param tree the tree we would like to print
 */
void printBT(BinaryTree* tree);

/**
 * Build location index as BinaryTree
 * @param tree the knowledge base tree we build out from
 * @return the tree that represents the location indexing structure
 */
BinaryTree* buildLocationIndex(BinaryTree* tree);

/**
 * Searches for tree based on the criteria
 * @param tree knowledge base tree organized by name
 * @param locationIndex tree organized by location
 * @param day numerical value for day
 * @param time string val of the time to search for 
 * @param city string of city to search for 
 * @param categories array of cateogries to search for 
 * @param numCategories number of categories in the categoris array
 * @param cost numercail value for cost 
 * @param categoriesUsingDisjunctions determines whether we look for categories conjunctively (the default) or disjunctively
 */ 
extern void searchForCriteria(BinaryTree* tree, BinaryTree* locationIndex, int day, char* time, char* city, char** category, int numCategories, int cost, bool categoriesUsingDisjunctions);


#endif
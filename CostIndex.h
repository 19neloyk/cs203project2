#ifndef COSTINDEX_H
#define COSTINDEX_H

#include <stdbool.h>
#include "IntArray.h"

/**
 * @struct Node
 * Creates a node to be used in the creation of CostLinkedLists
 * Contins the restuarant index 
 */ 
typedef struct Node_struct{
    struct Node_struct* next; 
    struct Node_struct* prev;
    int data; // data is going to be the restIndex; 

} Node; 

/**
 * @struct CostLinkedList
 * Creates a doubly linked list of Nodes 
 */ 
typedef struct CostLinkedList_struct{
    int size; 
    Node* head; 
    Node* tail; 

} CostLinkedList; 

/**
 * @struct CostIndex
 * Contains a linked list for each of the price brakets 
 */ 
typedef struct CostIndex_struct{
    CostLinkedList* low;
    CostLinkedList* med;
    CostLinkedList* high; 
} CostIndex;

extern CostIndex* createCostIndex(); 


/**
 * Inserts a cost and restuarant pair into the index 
 * @param ci CostIndex pointer 
 * @param cVal cost value
 * @param restIndex restaurant index 
 */ 
extern void insertInCostIndex(CostIndex *ci, int cVal, int restIndex); 

/**
 * Inserts a restuarant into the specified CostLinkedList
 * Helper to insertInCostIndex 
 * @param cll CostLinkedList pointer
 */ 
extern void insertInCostLinkedList(CostLinkedList *cll, int restIndex); 

/**
 * Given a restaurant index, returns the cost
 * @param ci CostIndex to search
 * @param restIndex restaurantIndex to search for
 * 
 * @param returns the cost 1 = $, 2 = $$, 3 = $$, 0 if resturant was not found 
 * (not currently in use)
 */ 
extern int searchCostIndex(CostIndex *ci, int restIndex);

/**
 * Searchs for a resturant in a CostLinkedList
 * Helper to searchCostIndex
 * @param cll CostLinkedList to search
 * @param restIndex to search for 
 * 
 * @return true if restIndex was found in cll, false if not
 */ 
extern bool searchCostLinkedList(CostLinkedList *cll, int restIndex);

/**
 * Given a cost, return an IntArray of all the resturant indices that match the cost 
 * @param ci CostIndex to search
 * @param cost to search for 
 * 
 * @return IntArray of the restuarant indices that match 
 */ 
extern IntArray* getRestaurantsFromCost(CostIndex *ci, int cost);

/**
 * Puts all of the data in a CostLinkedList into an IntArray
 * @param cll 
 * 
 * @return IntArray of the restuarant indices 
 */ 
extern IntArray* getRestsFromLL(CostLinkedList *cll); 

/**
 * Prints the contents of the CostIndex to the terminal 
 * @param ci CostIndex to print 
 */ 
extern void printCostIndex(CostIndex* ci); 

/**
 * Prints the contents of a CostLinkedList 
 * Helper to printCostIndex
 * @param cll CostLinkedList to print 
 */ 
extern void printCostLinkedList(CostLinkedList * cll); 

/**
 * Frees the linked lists, nodes, and object iself of a CostIndex
 * @param ci CostIndex to free
 */ 
extern void costIndexDestructor(CostIndex* ci); 

/**
 * Frees the nodes in the linked list and linked list itself 
 * Helper to the costIndex Destructor 
 * @param cll costLinkedList to free
 */ 
extern void costLinkedListDestructor(CostLinkedList* cll); 



#endif
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "restaurant.h"

/**
 * @struct RestNode
 * Creatse a node to be used in the creation of the LinkedList
 */ 
typedef struct RestNode_struct{
    struct RestNode_struct* next;
    struct RestNode_struct* prev;
    Restaurant* r;
} RestNode; 

/**
 * @struct LinkedList
 * Creates a linkesList of pointers to Restaurants
 */ 
typedef struct LinkedList_struct{
    int size;
    RestNode* head;
    RestNode* tail;
} LinkedList; 

/**
 * Creates an empty LinkedList
 * @return pointer to LinkedLIst created 
 */ 
extern LinkedList* createLinkedList();

/**
 * Sorted insert into Linked List. Prioritizes rank, city, first category, then cost 
 * @param ll LinkedList to insert into
 * @param r restaurant to insert 
 */ 
extern void insertInLinkedList(LinkedList* ll, Restaurant* r); 

/**
 * Insert to head of linked list
 * @param ll Linked List to insert into 
 * @param cNode node to insert
 * @param curr node in ll to insert right before
 */ 
extern void insertAtHead(LinkedList*ll, RestNode* cNode, RestNode* curr);

/**
 * Insert to body of linked list
 * @param ll Linked List to insert into 
 * @param cNode node to insert
 * @param curr node in ll to insert right before
 */ 
extern void insertAtBody(LinkedList*ll, RestNode* cNode, RestNode* curr);




/**
 * Print the contents of the LinkedList 
 * @param ll LinkedList to free
 */ 
extern void printLinkedList(LinkedList* ll); 

/**
 * Free the linked list 
 * @param ll LinkedList to free
 */ 
extern void linkedListDestructor(LinkedList* ll); 
#endif 
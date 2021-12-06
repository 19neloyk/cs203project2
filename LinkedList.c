#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "LinkedList.h"

/**
 * Creates an Empty LinkedList
 * Object is malloc'd here
 * Sets the size to 0 and the head and tail to NULL
 *
 * @return pointer to LinkedList created
 */
LinkedList *createLinkedList()
{
    LinkedList *ll = malloc(sizeof(LinkedList));
    ll->size = 0;
    ll->head = NULL;
    ll->tail = NULL;
    return ll;
}

/**
 * Sorted insert into LinkedList. First prioritizes rank (high->low) then if rank matches, cost (low->high)
 * @param ll LinkedList to insert into
 */
void insertInLinkedList(LinkedList *ll, Restaurant *r)
{
    // first by rank (high->low) and then by cost (low->high)
    RestNode *cNode = malloc(sizeof(RestNode));
    cNode->r = r;
    cNode->next = NULL;
    cNode->prev = NULL;

    // empty insertion
    if (ll->size == 0)
    {
        ll->head = cNode;
        ll->tail = cNode;
        ll->size += 1;
        return;
    }

    RestNode *curr = ll->head;
    int cCount = ll->size;
    for (int i = 0; i < cCount; i++)
    {
        // rank
        // city
        // category (first?)
        // cost

        if (r->rank > curr->r->rank){
            if (i == 0){
                insertAtHead(ll, cNode, curr);
            }
            else{
                insertAtBody(ll, cNode, curr);
            }
            return;
        } else if (r->rank == curr->r->rank){
            if (strcmp(r->city, curr->r->city) > 0){
                if (i == 0){
                    insertAtHead(ll, cNode, curr);
                } else {
                    insertAtBody(ll, cNode, curr);
                }
                return; 
            } else if (strcmp(r->city, curr->r->city) == 0){
                // compare the first categories
                if (strcmp(r->category[0], curr->r->category[0]) > 0){
                    if (i == 0){
                        insertAtHead(ll, cNode, curr);
                    } else {
                        insertAtBody(ll, cNode, curr);
                    }
                    return; 
                } else if (strcmp(r->category[0], curr->r->category[0]) == 0){
                    if (r->cost <= curr->r->cost){
                        if (i == 0){
                            insertAtHead(ll, cNode, curr);
                        } else {
                            insertAtBody(ll, cNode, curr);
                        }
                        return;
                    }
                }
            }
        }

        if (i != ll->size - 1){
            curr = curr->next;
        } else {
            // last element, insert at end
            cNode->prev = curr;
            curr->next = cNode;
            ll->tail = cNode;
            ll->size += 1;
        }
    }
}

/**
 * Insert to head of linked list, reassigns the relavent next/prevs
 * Increments ll->size, sets new head of ll 
 * @param ll Linked List to insert into 
 * @param cNode node to insert
 * @param curr node in ll to insert right before
 */ 
void insertAtHead(LinkedList *ll, RestNode *cNode, RestNode *curr)
{
    // insert at head
    cNode->next = curr;
    curr->prev = cNode;
    ll->head = cNode;

    ll->size += 1;
}

/**
 * Insert to body of linked list, reassigns the relevant next/prevs
 * Increments ll->size
 * @param ll Linked List to insert into 
 * @param cNode node to insert
 * @param curr node in ll to insert right before
 */ 
void insertAtBody(LinkedList *ll, RestNode *cNode, RestNode *curr)
{
    // insert in body of linked list
    cNode->prev = curr->prev;
    cNode->next = curr;

    if (curr->prev != NULL)
    {
        curr->prev->next = cNode;
    }

    curr->prev = cNode;

    ll->size += 1;
}

/**
 * Prints of the contents of the Linked List by traversing through
 * and calling printRestaurant (see restaurant.c)
 */
void printLinkedList(LinkedList *ll)
{
    printf("__________________________________________________\n\n");
    RestNode *curr = ll->head;
    for (int i = 0; i < ll->size; i++)
    {
        printRestaurant(curr->r);
        if (i != ll->size - 1)
        {
            curr = curr->next;
        }
        printf("__________________________________________________\n\n");
    }
}

/**
 * Traverses the linked list and frees each node
 * Frees the linked list itself
 * @param ll linked list to free
 */
void linkedListDestructor(LinkedList *ll)
{
    RestNode *curr = ll->head;
    int llSize = ll->size;
    for (int i = 0; i < llSize; i++)
    {
        RestNode *temp = NULL;
        if (i != llSize - 1)
        {
            temp = curr->next;
        }
        free(curr);
        curr = temp;
    }
    free(ll);
}
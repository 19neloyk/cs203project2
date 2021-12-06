#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "CostIndex.h"

/**
 * Creates an CostIndex which consists of 3 CostLinkedlists
 * low = all $ restaruants
 * med = all $$ restaurants 
 * high = all $$$ restaurants
 * (kind of like a hashmap that has a high collison rate)
 * handles mem alloc and initalizing fields to basic values 
 * @return CostIndex 
 */ 
CostIndex* createCostIndex(){
    CostIndex* c = malloc(sizeof(CostIndex)); 

    CostLinkedList* low = malloc(sizeof(CostLinkedList));
    CostLinkedList* med = malloc(sizeof(CostLinkedList));
    CostLinkedList* high = malloc(sizeof(CostLinkedList));

    low->size = 0; 
    low->head = NULL; 
    low->tail = NULL; 

    med->size = 0; 
    med->head = NULL; 
    med->tail = NULL; 

    high->size = 0; 
    high->head = NULL; 
    high->tail = NULL; 

    c->low = low;
    c->med = med; 
    c->high = high;
    return c; 

}

/**
 * Inserts the restIndex into the right CostLinkedList
 * 
 */ 
void insertInCostIndex(CostIndex *ci, int cVal, int restIndex){
    if(cVal == 1){
        insertInCostLinkedList(ci->low, restIndex); 
    } else if (cVal == 2){
        insertInCostLinkedList(ci->med, restIndex); 
    } else if (cVal == 3){
        insertInCostLinkedList(ci->high, restIndex); 
    }
    return; 
}

/**
 * Inserts restIndex into the back of the linked list 
 * @param cll CostLinkedList to insert into
 * @param restIndex restaurant index which will become the Node data 
 */ 
void insertInCostLinkedList(CostLinkedList *cll, int restIndex){
    // create nodes and stuff 
    Node* curr = malloc(sizeof(Node));
    curr->next = NULL; 
    curr->prev = NULL; 
    curr->data = restIndex; 

    if(cll->size == 0){
        cll->head = curr; 
        cll->tail = curr; 
    } else {
        // insert at back 
        curr->prev = cll->tail; 
        cll->tail->next = curr; 
        cll->tail = curr; 
    }
    cll->size += 1; 
    return; 
}

/**
 * Given a restuarant index, searches the costLinkedLists to see which one it is in
 * @param ci CostIndex to search
 * @param restIndex to search for 
 * 
 * @return int the numerical cost value 
 */ 
int searchCostIndex(CostIndex *ci, int restIndex){
    int result = 0; 
    if(searchCostLinkedList(ci->low, restIndex) == true){
        result = 1; 
    } else if (searchCostLinkedList(ci->med, restIndex) == true){
        result = 2;
    } else if (searchCostLinkedList(ci->high, restIndex) == true){
        result = 3;
    }
    return result;
}

/**
 * Searches a cost linked list by iterating through and comparing the Node data with restIndex
 * @param cll CostLinkedList to search
 * @param restIndex to search for
 * @return true if found, false if not found 
 */ 
bool searchCostLinkedList(CostLinkedList *cll, int restIndex){
    Node* curr = cll->head;
    for(int i = 0; i < cll->size; i++){
        if(restIndex == curr->data){
            return true; 
        }

        if(i != cll->size-1){
            curr = curr->next; 
        }
    }
    return false; 
}

/**
 * Given a numericla cost value, returns all the restuarant indices that match that
 * in an IntArray (see IntArray.c) 
 * @return IntArray with all of the restuarants, NULL if numerical cost value was incorrect 
 */ 
IntArray* getRestaurantsFromCost(CostIndex *ci, int cost){
    if(cost == 1){
        return getRestsFromLL(ci->low);
    } else if (cost == 2){
        return getRestsFromLL(ci-> med);
    } else if(cost == 3){
        return getRestsFromLL(ci->high); 
    }
    return NULL; 
}

/**
 * Basically converts the CostLinkedList to an IntArray 
 * by iterating through the CostLinkedlist
 * @param cll CostLinkedList to convert
 * @return IntArray of all the restaruant indicies that are in the cll 
 */ 
IntArray* getRestsFromLL(CostLinkedList *cll){
    IntArray* arr = createIntArray();
    Node* curr = cll->head; 
    for(int i = 0; i < cll->size; i++){
        insertInIntArray(arr, curr->data); 
        if(i != cll->size-1){
            curr = curr->next; 
        }
    }
    return arr; 
}

/**
 * Prints low/med/high linked lists 
 */ 
void printCostIndex(CostIndex* ci){
    printf("Indices of $ Restaurants: \n");
    printCostLinkedList(ci->low); 
    printf("\nIndices of $$ Restaurants: \n");
    printCostLinkedList(ci->med);
    printf("\nIndices of $$$ Restaurants: \n");
    printCostLinkedList(ci->high);
    printf("\n"); 

}

/**
 * Prints contents of the CostLinkedList by 
 * traversing through the LinkedList 
 */ 
void printCostLinkedList(CostLinkedList* cll){
    Node* curr = cll->head; 
    for(int i = 0; i < cll->size; i++){
        printf("%d ", curr->data); 
        if(i != cll->size-1){
            curr = curr->next; 
        }
    }
}


/**
 * Frees each linked list in the CostIndex and the CostIndex itself 
 * 
 * @param ci CostIndex to free
 */ 
void costIndexDestructor(CostIndex* ci){
    costLinkedListDestructor(ci->low); 
    costLinkedListDestructor(ci->med); 
    costLinkedListDestructor(ci->high); 
    free(ci); 
}

/**
 * Frees all the nodes in the linked list and the linked list itself
 * @param cll linkedlist to free
 */ 
void costLinkedListDestructor(CostLinkedList* cll){
    Node* curr = cll->head; 
    int cllSize = cll->size; 
    for(int i = 0; i < cllSize; i++){
        Node* temp = NULL;
        if(i != cllSize-1){
            temp = curr->next; 
        } 
        free(curr); 
        curr = temp;
    }
    free(cll); 
}

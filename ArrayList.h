#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "restaurant.h"

/**
 * @struct ArrayList
 * creates an ArrayList that holds an Array of restaurant pointers 
 */ 
typedef struct ArrayList_struct{
    int size; 
    int maxSize;
    // an array of pointers  
    Restaurant** restArr; 

} ArrayList; 


/**
 * Creates an empty ArrayList
 * Does not need to be malloc'd ahead of time 
 * @return pointer to ArrayList object 
 */
extern ArrayList* createArrayList(); 

/**
 * Inserts a restaurant pointer into the ArrayList
 * @param self ArrayList pointer
 * @param r Restaurant pointer to insert 
 */ 
extern void insert(ArrayList* self, Restaurant* r); 



/**
 * Gets the Restaurant pointer from the ArrayList at the specified index
 * @param arr ArrayList to seach
 * @param index 
 * 
 * @return pointer to Restaurant if found, NULL if index is out of bounds 
 */ 
extern Restaurant* at(ArrayList *arr, int index); 

/**
 * Prints the contents of the ArrayList in a nice format
 * @param self ArrayList to print 
 */ 
extern void printArray(ArrayList* self); 

/**
 * Frees the pointer to the ArrayList and the inside array
 * @param self ArrayList to shallow destroy
 */
extern void arrayListShallowDestructor(ArrayList* self);

/**
 * Frees the pointer to the Arraylist, and each of the restaurants in the ArrayList
 * @param self ArrayList to deep destroy
 */ 
extern void arrayListDestructor(ArrayList* self); 


#endif
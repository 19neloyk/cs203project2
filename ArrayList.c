#include <stdio.h>
#include <stdlib.h>

#include "ArrayList.h"

/**
 * Creates an empty ArrayList of size 0, maxSize 10
 * Handles mallocing object and inner restArr(restaurant array)
 * @return pointer to ArrayList
 */ 
ArrayList* createArrayList()
{
    ArrayList *self = malloc(sizeof(ArrayList));
    self->restArr = malloc(sizeof(Restaurant*) * 10);
    self->size = 0;
    self->maxSize = 10;
    return self;
}

/**
 * Inserts to the back of the ArrayList 
 * If the maxSize needs to be increase, the maxSize is doubled 
 * Copies the values over 
 * @param self ArrayList pointer
 * @param r Restaurant pointer, to insert 
 */ 
void insert(ArrayList *self, Restaurant *r)
{
    if (self->size + 1 > self->maxSize)
    {
        // double the size of the array
        self->maxSize *= 2;
        Restaurant** temp = self->restArr; 
        self->restArr = malloc(sizeof(Restaurant*) * self->maxSize);
        // copy the values over 
        for(int i = 0; i < self->size; i++){
            self->restArr[i] = temp[i]; 
        }
        free(temp); 
    }

    // NOTE: right now it's just inserting to the back of the array... no sorted order!!
    Restaurant* tempRest = r; 
    //self->restArr[self->size] = r;
    self->restArr[self->size] = tempRest; 
    
    self->size++;
}

/**
 * Get the restaurant at a given index from the restArr
 * @param arr ArrayList
 * @param index 
 * 
 * @return Restaurant object at the index, or NULL if the index was out of range 
 */ 
Restaurant* at(ArrayList *arr, int index){
    if(index < arr->size){
        return arr->restArr[index]; 
    }
    return NULL; 
}

/**
 * Prints the contents by calling the printRestaurant function defined in restaurant.c
 * @param self ArrayList pointer 
 */ 
void printArray(ArrayList *self)
{
    printf("__________________________________________________\n\n");
    for (int i = 0; i < self->size; i++)
    {

        printRestaurant(self->restArr[i]);
        printf("__________________________________________________\n\n");
    }
}

/**
 * Frees the underlying restArr and the object itself
 * @param self ArrayList to free
 */ 
void arrayListShallowDestructor(ArrayList *self){
    free(self->restArr);
    free(self); 
}

/**
 * Frees the restaurants in the underlying restArr using restaurantDestructor from restaurants.c 
 * Frees the underlying restArr and the object itself
 * @param self ArrayList to free
 */ 
void arrayListDestructor(ArrayList *self)
{
    // free each of the restaurants 
    for(int i = 0; i < self->size; i++){
        // takes care of freeing internals and object itself
         Restaurant* tempRest = self->restArr[i]; 
         restaurantDestructor(self->restArr[i]);
         //free(self->restArr[i]);
       
    }
    // free restaurant array
    free(self->restArr);
    // finally, free the object itself 
    free(self);
}

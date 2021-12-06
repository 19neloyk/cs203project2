#include <stdio.h>
#include <stdlib.h>

#include "IntArray.h"

/**
 * Creates empty IntArray with size 0 and maxSize = 10
 * @return pointer to IntArray created 
 */ 
IntArray* createIntArray(){
    IntArray *arr = malloc(sizeof(IntArray));
    arr->arr = calloc(10, sizeof(int)); 
    arr->size = 0; 
    arr->maxSize = 10; 
    return arr;
}

/**
 * Insert to back of IntArray
 * If more space is needed, doubles the size of the IntArray and then inserts
 * @param arr IntArray to insert into 
 * @param val int to insert 
 */ 
void insertInIntArray(IntArray* arr, int val){
    if(arr->size + 1 > arr->maxSize){
        arr->maxSize *= 2;
        int* temp = arr->arr;
        arr->arr = calloc(arr->maxSize, sizeof(int));
        for(int i = 0; i < arr->size; i++){
            arr->arr[i] = temp[i];
        }
        free(temp);
    }

    arr->arr[arr->size] = val;
    arr->size += 1; 
}

/**
 * Find the int a given index using direct access to underlying array 
 * @param arr IntArray to search from 
 * @param index to get int from 
 * 
 * @return arr[index] or -1 if index was out of bounds 
 * -1 is fine for a return type b/c the use case is to store the restIndices which have to be >=0
 */  
int getIntAt(IntArray* arr, int index){
    if(index < arr->size){
        return arr->arr[index];
    } else {
        return -1; 
    }
}

/**
 * Print the contents of the IntArray by iterating through the underlying array 
 * @param arr IntArray to print 
 */ 
void printIntArray(IntArray* arr){
    printf("IntArr:\n");
    for(int i = 0; i < arr->size; i++){
        printf("%d ", arr->arr[i]); 
    }
    printf("\n");
}

/**
 * Free the underlying array and IntArray
 */ 
void intArrayDestructor(IntArray* arr){
    free(arr->arr);
    free(arr); 
}
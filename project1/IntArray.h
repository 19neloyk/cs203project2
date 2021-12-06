#ifndef INTARRAY_H
#define INTARRAY_H

/**
 * @struct IntArray
 * Creates an ArrayList for ints 
 */ 
typedef struct IntArray_struct{
    int size; 
    int maxSize; 
    int* arr; 

} IntArray; 

/**
 * Creates an empty IntArray
 * Handles the malloc'ing 
 * @return pointer to IntArray created 
 */ 
IntArray* createIntArray();

/**
 * Insert to back of IntArray
 * 
 */ 
extern void insertInIntArray(IntArray* arr, int val);

/**
 * Find the int a given index
 * @param arr IntArray to search from 
 * @param index to get int from 
 * 
 * @return arr[index] or -1 if index was out of bounds 
 */  
extern int getIntAt(IntArray* arr, int index);

/**
 * Print the contents of the IntArray
 * @param arr IntArray to print 
 */ 
extern void printIntArray(IntArray* arr);

/**
 * Free the IntArray
 */ 
extern void intArrayDestructor(IntArray* arr); 

#endif
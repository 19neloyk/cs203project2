#ifndef CITYINDEX_H
#define CITYINDEX_H

#include "IntArray.h"

/**
 * @struct CityNode
 * Creates a node to be used in the creation of the CityIndex
 * Contains the city name and the restuarant index it corresponds to
 */ 
typedef struct CityNode_struct{
    struct CityNode_struct* next; 
    struct CityNode_struct* prev;
    char* data; // city name 
    int restIndex; // restaurant index 

} CityNode; 

/**
 * @struct CityIndex
 * Creates a lexiographically sorted doubly linked list of the cities in the knowledge base 
 */ 
typedef struct CityIndex_struct{
    int size; 
    CityNode* head;
    CityNode* tail; 

} CityIndex;

/**
 * Creates a CityIndex object
 * Takes care of the malloc'ing
 * @return pointer to CityIndex created 
 */ 
extern CityIndex* createCityIndex(); 

/**
 * Insert a new city/restuarant pair into its sorted position in the index
 * @param c CityIndex pointer
 * @param city string of the city to insert
 * @param restIndex restaurant index 
 */ 
extern void insertInCityIndex(CityIndex* c, char* city, int restIndex);

/**
 * Returns all the restaurant indices that are associated with a specified city 
 * @param c CityIndex to search
 * @param city city to serach for
 * 
 * @return IntArray pointer of all the restaurant indices that have the specified city
 */ 
extern IntArray* searchCityIndex(CityIndex* c, char* city);


/**
 * Prints out the contents of the CityIndex
 * @param c CityIndex pointer
 */ 
extern void printCityIndex(CityIndex* c);

/**
 * Free the CityIndex
 * @param c CityIndex to free 
 */ 
extern void cityIndexDestructor(CityIndex* c);

#endif
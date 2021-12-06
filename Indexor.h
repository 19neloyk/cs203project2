#ifndef INDEXOR_H
#define INDEXOR_H

#include "ArrayList.h"
#include "CostIndex.h"
#include "CityIndex.h"
#include "TimeIndex.h"
#include "IntArray.h"

/**
 * @struct Indexor
 * A container for all the indexing structures 
 */ 
typedef struct Indexor_struct{

    CityIndex* cities;
    CostIndex* costs; 
    CityIndex* categories;
    TimeIndex* times; 
    
} Indexor; 

/**
 * Cretes an Indexor object 
 * Handles malloc'ing w/in function
 * @return pointer to Indexor object created 
 */ 
extern Indexor* createIndex(); 

/**
 * Inserts all the restaurants in the knowledge base into the indices 
 * @param arr knowledge base
 * @param index Indexor 
 */ 
extern void indexRestaurants(ArrayList *arr, Indexor* index); 

/**
 * Frees the contents of the indices (all of th indices in the Indexor object)
 * @param index to free 
 */ 
extern void indexDestructor(Indexor* index); 

/**
 * Assigns ranks then organizes the restaurants by their ranks 
 * @param arr knowledge base
 * @param index
 * @param day numerical value for day
 * @param time string val of the time to search for 
 * @param city string of city to search for 
 * @param categories array of cateogries to search for 
 * @param numCategories number of categories in the categoris array
 * @param cost numercail value for cost 
 */ 
extern void processUserQuery(ArrayList* arr, Indexor* index, int day, char* time, char* city, char** category, int numCategories, int cost); 

/**
 * Assigns ranks to the restaurants 
 * @param arr knowledge base
 * @param index
 * @param day numerical value for day
 * @param time string val of the time to search for 
 * @param city string of city to search for 
 * @param categories array of cateogries to search for 
 * @param numCategories number of categories in the categoris array
 * @param cost numercail value for cost 
 * 
 * @return a tally that determines the rank 
 */ 
extern int** assignRanks(ArrayList* arr, Indexor* index, int day, char* time, char* city, char** category, int numCategories, int cost); 

/**
 * Sorts of the restaurants according to their ranks
 * Prints out the results to the terminal
 * @param arr knowledge base
 * @param tally the ranks
 * @param numCatgories the number of categories that have to match
 */ 
extern void rankRestaurants(ArrayList* arr, int** tally, int numCategories); 


#endif 
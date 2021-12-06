#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "restaurant.h"
#include "FileReader.h"
#include "Indexor.h"
#include "ArrayList.h"

/**
 * @struct Query
 * Creates a container to hold a user's search query 
 */ 
typedef struct Query_struct{
    int day;
    char* time;
    char* city;
    char** category;
    int numCategories;
    int cost; 

} Query; 

/**
 * Creates a Query object 
 * Takes care of the malloc'ing
 * @return pointer to created Query object 
 */ 
extern Query* createQuery();

/**
 * Frees the contents of a Query and the object itself
 * @param q Query to free
 */ 
extern void queryDestructor(Query* q);

/**
 * Prints the contents of a query 
 * @param q pointer to Query to print 
 */ 
extern void printQuery(Query *q);

/**
 * Function that gets called in main, Creates the knowledge base and indexing structures
 * Process user queries 
 * restaurant txt file is specified here
 */ 
extern void control(); 

/**
 * Determines the program flow given a user's query
 * @param query User's query 
 * @param arr restaurant knowledge base
 * @param index container of all the indexing structures 
 */ 
extern void processQuery(char* query, ArrayList* arr, Indexor* index); 

/**
 * Read in the user's query
 * 
 * @return user's query in a string 
 */ 
extern char* getQuery(); 

/**
 * Get rid of any extra spaces that might be at the end of a user's query 
 * @param s query to trim 
 */ 
extern void trimQuery(char* s); 


/**
 * Processes a user's search query, queries the user for more info 
 * 
 * @param arr restaurant knowledge base
 * @param index container of indexing structures 
 */ 
extern void searchQuery(ArrayList *arr, Indexor* index); 

/**
 * Given a category query, parse it and add the category array to the Query object
 * Helper to searchQuery
 * @param qCategory query
 * @param q Query object to add to 
 */ 
extern void processCategory(char* qCategory, Query* q); 

/**
 * Given a cost query, parse it and add the cost to the Query object 
 * Helper to searchQuery
 * @param qCost query
 * @param q Query object to add to 
 */ 
extern void processCost(char* qCost, Query* q); 

/**
 * Given a time query, parse it and add the time info to the Query object
 * Helper to searchQuery
 * @param qTime query
 * @param q Query object 
 */ 
extern void processTime(char* qTime, Query* q); 



#endif
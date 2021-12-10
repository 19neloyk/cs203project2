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
    bool categoriesAreDisjunctive;
    char* name;
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
 * Controls the flow of the program for PROJECT2. 
 * Reads in the restaurant file and populates the knowledge file (see FileReader.c for implementaiton of readIn)
 * Creates all the indexing stuctores and populates them (see Indexor.c for implementaiton detaails)
 * Controls the user queries flow 
 */ 
void controlProject2();




/**
 * Determines the program flow given a user's query
 * @param query User's query 
 * @param arr restaurant knowledge base
 * @param index container of all the indexing structures 
 */ 
extern void processQuery(char* query, ArrayList* arr, Indexor* index); 

/**
 * Determines the program flow given a user's query for Project2
 * 
 * @param query User's query 
 * @param tree restaurant knowledge base tree by name
 * @param locationIndex restaurant knowledge base tree by location --> no need for extra complicated indexing structures
 */ 
extern void processQueryProject2(char* query, BinaryTree* tree, BinaryTree* locationIndex); 

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
 * Processes a user's search query, queries the user for more info 
 * 
 * @param tree restaurant knowledge base tree by name
 * @param locationIndex restaurant knowledge base tree by location
 */ 
extern void searchQueryProject2(BinaryTree* tree, BinaryTree* locationIndex); 


/**
 * Called when the user wants to add a new restaurant to the knowledge base manually
 * @param tree knowledge base
 * @param index indices
 */ 
extern void addQueryProject2(BinaryTree* tree, BinaryTree* locationIndex);


/**
 * Called when the user wants to modify a restaurant in the knowledge base
 * @param tree the knowledge base tree
 */ 
extern void modifyQueryProject2(BinaryTree* tree);

/**
 * Called when the user wants to see information about a restaurant in the knowledge base
 * @param tree the knowledge base tree
 */ 
extern void matchQueryProject2(BinaryTree* tree);

/**
 * Called when the user wants to write a file to the knowledge base
 * @param tree the knowledge base tree
 * @param locationIndex the index tree for location
 */ 
void writeQueryProject2(BinaryTree* tree, BinaryTree* locationIndex);

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
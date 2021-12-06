#ifndef FILEREADER_H
#define FILEREADER_H

#include "restaurant.h"
#include "ArrayList.h"


/**
 * Reads in a txt file and populates an ArrayList with them 
 * @param fileName string of the name of the txt file
 * @return ArrayList of Resturants read in from the file, null if there was an error 
 */
ArrayList* readIn(char* filePath); 

/**
 * Reads in the name of a restaurant and puts in in the specified restaurant object
 * Helper to readIn()
 * @param curr pointer to resturant to insert into
 * @param linea line to process 
 */ 
void readName(Restaurant* curr, char* linea); 

/**
 * Reads in the city of a restaurant and puts in in the specified restaurant object
 * Helper to readIn()
 * @param curr pointer to resturant to insert into
 * @param linea line to process 
 */ 
void readCity(Restaurant* curr, char* linea); 

/**
 * Reads in the categories of a restaurant and puts in in the specified restaurant object
 * Helper to readIn()
 * @param curr pointer to resturant to insert into
 * @param linea line to process 
 */ 
void readCategories(Restaurant* curr, char* linea); 

/**
 * Reads in the times a restuarant opens/closes  and puts in in the specified restaurant object
 * Helper to readIn()
 * @param curr pointer to resturant to insert into
 * @param linea line to process 
 */ 
void readTimes(Restaurant* curr, char* linea); 

/**
 * Processes the open/close times of a restaurant and inserts it into the resturant object
 * Helper to readTimes
 * @param line line to process
 * @param day day of the week (Sunday, Monday, etc)
 * @param dayNum corresponding day numerically (0 = Sunday, 1 = Monday, etc)
 * @param timeArr time array to insert 9into 
 * 
 */ 
void openClose(char* line, char* day, int dayNum, char*** timeArr); 

/**
 * Reads in the cost of restaurant and puts in in the specified restaurant object
 * Helper to readIn()
 * @param curr pointer to resturant to insert into
 * @param linea line to process 
 */
void readCost(Restaurant* curr, char* linea); 

#endif
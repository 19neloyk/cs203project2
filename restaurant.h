#ifndef RESTAURANT_H
#define RESTAURANT_H
#include <stdbool.h>
/**
 * @struct Restaurant
 * @var Restaurant::name 
 * @var Restaurant::city
 * @var Restaurant::category
 * @var Restaurant::open
 * @var Restaurant::rank 
 * @var Restaurant::cost
 * @var Restaurant::reviewers 
 */
typedef struct Restaurant_struct{
    char* name; 
    char* city; 
    char** category; // make sure to put a null at the end of the category. Malloc an extra char* as a result 
    int numCategory; 
    char*** times; 
    float rank; 
    int cost; 
    int reviewers; 

} Restaurant; 

/**
 * Creates an empty Resturant object (acts like a constructor)
 * @return Restuarant object 
 */ 
extern Restaurant* createEmptyRestuarant(Restaurant* r); 

/**
 * Creates a Restaurant object (acts like a constructor)
 * @param name (char*)
 * @param city (char*)
 * @param category (char**)
 * @param times (int**)
 * @param rank (float)
 * @param cost (int)
 * @param reviewers (int)
 * @return restaurant object 
 * 
 */

extern Restaurant* createRestaurant(char* name, char* city, char** category, int numCategory, char*** times, float rank, int cost, int reviewers); 

/**
 * Set the name of the restaurant
 * @param r restaurant to set name of 
 * @param nm name of restaurant 
 */ 
extern void setName(Restaurant* r, char* nm); 

/**
 * Set the city of the restaurant
 * @param r restaurant to set city of 
 * @param cty city
 */ 
extern void setCity(Restaurant* r, char* cty);

/**
 * Set the categories of the restaurant
 * @param r restaurant to set the categories of 
 * @param catsArr category array
 * @param numCategory number of categories to insert 
 */ 
extern void setCategory(Restaurant* r, char** catsArr, int numCategory);  
extern void setTime(Restaurant* r, char*** hrs); 

//Check if a given restaurant is a match with the given criteria 
extern bool checkMatch(Restaurant* r, int day, char* time, char* city, char** category, int numCategories, int cost, bool categoriesUsingDisjunctions);

/**
 * Prints the restaurant to the terminal 
 * @param r the restaurant to print 
 */
extern void printRestaurant(Restaurant* r); 

/**
 * Frees the memory of a Restaurant object (acts like a destructor)
 * @param r the restaurant to free 
 */
extern void restaurantDestructor(Restaurant* r); 

#endif
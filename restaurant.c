#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "restaurant.h"

/**
 * Creates an empty Resturant object (acts like a constructor)
 * Pre-allocates space for all of the strings 
 * @return Restuarant object 
 */
Restaurant *createEmptyRestuarant(Restaurant* r)
{
    //Restaurant *r = malloc(sizeof(Restaurant));
    r->name = calloc(100, sizeof(char));
    r->city = calloc(100, sizeof(char));

    // category 
    r->category = malloc(2 * sizeof(char *));
    for(int i = 0; i < 2; i++){
        r->category[i] = calloc(100, sizeof(char)); 
    }
    r->numCategory = 2; 


    //times 
    char*** hrs  = malloc(7 * sizeof(char**));
    for (int i = 0; i < 7; i++)
    {
        hrs[i] = malloc(2 * sizeof(char*));
        //char** temp = hrs[i];
        //temp[0] = calloc(6, sizeof(char)); 
        //temp[1] = calloc(6, sizeof(char)); 
        hrs[i][0] = calloc(6, sizeof(char)); 
        hrs[i][1] = calloc(6, sizeof(char)); 
    }
    r->times = hrs;
    r->rank = -1;
    r->cost = -1;
    r->reviewers = -1;
    return r;
}

/**
 * Creates a Restaurant object (acts like a constructor)
 * Reassigns the fields. Use either this "constructor" or the other one to prevent memory leaks 
 * @param name (char*) dynammic 
 * @param city (char*) dynammic 
 * @param category (char**) dynammic 
 * @param times (char***) dynammic 
 * @param rank (float)
 * @param cost (int)
 * @param reviewers (int)
 * 
 */

Restaurant *createRestaurant(char *name, char *city, char **category, int numCategory, char ***times, float rank, int cost, int reviewers)
{
    Restaurant *r = malloc(sizeof(Restaurant));
    r->name = name;
    r->city = city;
    r->category = category;
    r->numCategory = numCategory;
    r->times = times;
    r->rank = rank;
    r->cost = cost;
    r->reviewers = reviewers;
    return r;
}

/**
 * Frees the current name of the restaurant and assigns a new one
 * @param r restuarant to change
 * @param nm new name 
 */ 
void setName(Restaurant *r, char *nm)
{
    free(r->name); 
    r->name = strdup(nm);
    return;
}

/**
 * Frees the current city of the restaurant and assigns a new one
 * @param r restuarant to change
 * @param cty new city
 */ 
void setCity(Restaurant *r, char *cty)
{
    free(r->city); 
    r->city = strdup(cty);
    return;
}

/**
 * Frees the current category array of the restaurant and assigns a new one
 * @param r restuarant to change
 * @param catsArr new category array
 * @param numCatgory number of new categories 
 */ 
void setCategory(Restaurant *r, char **catsArr, int numCategory)
{
    int counter = 0; 

    for(int i = 0; i < r->numCategory; i++){
        free(r->category[i]);
    }
    free(r->category); 
    r->category = catsArr; 
    r->numCategory = numCategory; 
    return;
}

/**
 * Frees the current timeof the restaurant and assigns a new one
 * @param r restuarant to change
 * @param hrs new times table 
 */ 
void setTime(Restaurant* r, char*** hrs){
    for(int i = 0; i < 7; i++){
        free(r->times[i][0]); 
        free(r->times[i][1]); 
        free(r->times[i]); 
    }
    free(r->times); 
    r->times = hrs; 
}
/**
 * Prints the restaurant to the terminal 
 * @param r the restaurant to print 
 */
void printRestaurant(Restaurant *r)
{
    // Commented out format is sometimes useful for debugging 
    /*
    printf("***%s***\n\n", r->name);
    printf("Ranking:**%.1f**# of Reviews:**%d**\n\n", r->rank, r->reviewers);
   
   for(int i = 0; i < r->numCategory; i++){
       if (i == 0){
           printf("**%s** ", r->category[i]);
       } else {
           printf("- **%s** ", r->category[i]);
       }
   }

    // print the cost
    if (r->cost == 1)
    {
        printf("| $ | ");
    }
    else if (r->cost == 2)
    {
        printf("| $$ | ");
    }
    else
    {
        printf("| $$$ | ");
    }

    printf("Location: **%s**\n\n", r->city);
    //print times
    printf("Hours of Operation:\n");
    for (int i = 0; i < 7; i++)
    {
        if (i == 0)
        {
            printf("Sunday: ");
        }
        else if (i == 1)
        {
            printf("Monday: ");
        }
        else if (i == 2)
        {
            printf("Tuesday: ");
        }
        else if (i == 3)
        {
            printf("Wednesday: ");
        }
        else if (i == 4)
        {
            printf("Thursday: ");
        }
        else if (i == 5)
        {
            printf("Friday: ");
        }
        else
        {
            printf("Saturday: ");
        }

        
        if (strstr(r->times[i][0], ":") == NULL)
        {
            printf(" closed\n");
        }
        else
        {
            printf("***%s*** - ***%s***\n", r->times[i][0], r->times[i][1]);
        }
    }
    printf("\n");
    */
    
    printf("***%s***\n\n", r->name);
    printf("Ranking: %.1f | # of Reviews: %d\n\n", r->rank, r->reviewers);
   
   for(int i = 0; i < r->numCategory; i++){
       if (i == 0){
           printf("%s ", r->category[i]);
       } else {
           printf("- %s ", r->category[i]);
       }
   }

    // print the cost
    if (r->cost == 1)
    {
        printf("| $ | ");
    }
    else if (r->cost == 2)
    {
        printf("| $$ | ");
    }
    else
    {
        printf("| $$$ | ");
    }

    printf("Location: %s\n\n", r->city);
    //print times
    printf("Hours of Operation:\n");
    for (int i = 0; i < 7; i++)
    {
        if (i == 0)
        {
            printf("Sunday: ");
        }
        else if (i == 1)
        {
            printf("Monday: ");
        }
        else if (i == 2)
        {
            printf("Tuesday: ");
        }
        else if (i == 3)
        {
            printf("Wednesday: ");
        }
        else if (i == 4)
        {
            printf("Thursday: ");
        }
        else if (i == 5)
        {
            printf("Friday: ");
        }
        else
        {
            printf("Saturday: ");
        }

        
        if (strstr(r->times[i][0], ":") == NULL)
        {
            printf(" closed\n");
        }
        else
        {
            printf("%s - %s\n", r->times[i][0], r->times[i][1]);
        }
    }
    printf("\n");
    
}

bool isTimeValid (Restaurant* r, int day, char* time) {
    if (day == -1) {
        return true;
    }
    
    char* openTimeDay = r->times[day][0];
    char* closeTimeDay = r->times[day][1];

    int openHr, openMin, curHr, curMin, closeHr, closeMin;    
    sscanf(openTimeDay, "%d:%d", &openHr, &openMin);
    sscanf(closeTimeDay, "%d:%d", &closeHr, &closeMin);
    sscanf(time, "%d:%d", &curHr, &curMin);

    if (curHr < openHr || curHr > openHr) {
        return false;
    }
    if (curHr == openHr && curMin < openMin) {
        return false;
    }
    if (curHr == closeHr && curMin > closeMin) {
        return false;
    }

    return true;

}

bool isCityValid(Restaurant* r, char* city) {
    if (strstr(city, "*")) {
        return true;
    }
    char* restCity = r->city;
    if (strcmp(restCity, city) == 0) {
        return true;
    }
    return false;
} 

bool isCategoryValid(Restaurant* r, char** categories, int numCategories, bool categoriesUsingDisjunctions) {
    if (numCategories == 0) {
        return true;
    }

    char** restCategories = r->category;
    int numRestCategories = r->numCategory;

    //Case for disjunctions using "OR"
    if (categoriesUsingDisjunctions) {
        printf("NEW–––––––\n");
        for (int i = 0; i < numCategories ; i ++) {
            printf("%s ->", categories[i]);
            for (int j = 0 ; j < numRestCategories ; j ++) {
                printf("%s  ", restCategories[j]);
                printf(" with cmp val %d  ;", strcmp(categories[i], restCategories[j]) );
                if (j == numRestCategories - 1) {
                    printf("\n");
                }
                if (strcmp(categories[i], restCategories[j]) == 0) {
                    printf("YUHHHH\n");
                    return true;
                }
            }
        }
        return false;
    }

    //Case for conjunctions using ","
    for (int i = 0; i < numCategories ; i ++) {
        for (int j = 0 ; j < numRestCategories ; j ++) {
            if (strcmp(categories[i], restCategories[j]) == 0) {
                break;
            }
            if (j == numRestCategories - 1) {
                return false;
                }
        }
    }
    return true;
}

bool isCostValid (Restaurant* r, int cost) {
    if (cost < r->cost) {
        return false;
    }
    return true;
}


bool checkMatch(Restaurant* r, int day, char* time, char* city, char** categories, int numCategories, int cost, bool categoriesUsingDisjunctions) {
    bool timeValid;
    bool cityValid; 
    bool categoryValid; 
    bool costValid;
    timeValid = isTimeValid(r, day, time);
    cityValid = isCityValid(r, city);
    categoryValid = isCategoryValid(r, categories, numCategories, categoriesUsingDisjunctions);
    costValid = isCostValid(r, cost);
    return (timeValid && cityValid && categoryValid && costValid);
}

/**
 * Frees the memory of a Restaurant object (acts like a destructor)
 * @param r the restaurant to free 
 */
void restaurantDestructor(Restaurant *r)
{
    //printf("Restaurant destructor called\n"); 
    free(r->city); 
    free(r->name); 

    /*
    int counter = 0; 
    while(r->category[counter] != NULL){
       // printf("free category[counter]\n"); 
        free(r->category[counter]); 
        counter++; 
    }
    */
    for(int i = 0; i < r->numCategory; i++){
        free(r->category[i]);
    }
    free(r->category);


    for (int i = 0; i < 7; i++)
    {
        free(r->times[i][0]); 
        free(r->times[i][1]); 
        free(r->times[i]); 
    }
    free(r->times);

    // finally, free the restaurant
    free(r);
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Indexor.h"
#include "LinkedList.h"
#include "restaurant.h"

/**
 * Creates an Indexor objects and intializes the indices to NULL
 * @return pointer to Indexor object created 
 */ 
Indexor *createIndex()
{
    Indexor *x = malloc(sizeof(Indexor));
    x->cities = NULL;
    x->costs = NULL;
    x->categories = NULL;
    x->times = NULL;
    return x;
}

/**
 * The indices are created here
 * For each of the restaurants in the knowledge base, 
 * each of the costs, cities, categories, and times are inserted into their respective indexing structures
 * @param arr knowledge base
 * @param index Indexor to assign the created indices to
 */ 
void indexRestaurants(ArrayList *arr, Indexor *index)
{
    // index = createIndex();
    CostIndex *cost = createCostIndex();
    CityIndex *city = createCityIndex();
    CityIndex *category = createCityIndex();
    TimeIndex *time = createTimeIndex();

    for (int i = 0; i < arr->size; i++)
    {
        Restaurant *curr = at(arr, i);

        // category
        for (int j = 0; j < curr->numCategory; j++)
        {
            insertInCityIndex(category, curr->category[j], i);
        }

        // times
        for (int j = 0; j < 7; j++)
        {
            if (strcmp(curr->times[j][0], "") != 0)
            {
                insertInTimeIndex(time, j, curr->times[j][0], curr->times[j][1], i);
            }
        }

        insertInCostIndex(cost, curr->cost, i);
        insertInCityIndex(city, curr->city, i);
    }

    index->categories = category;
    index->cities = city;
    index->costs = cost;
    index->times = time;
}


/**
 * Calls all the destructors for each index
 * Finally, frees the container itself 
 */ 
void indexDestructor(Indexor *index)
{
    costIndexDestructor(index->costs);
    cityIndexDestructor(index->cities);
    timeIndexDestructor(index->times);
    cityIndexDestructor(index->categories);

    free(index);
}

/**
 * Driver function that calls assignRanks and rankRestaurants 
 * @param arr knowledge base
 * @param index
 * @param day numerical value for day
 * @param time string val of the time to search for 
 * @param city string of city to search for 
 * @param categories array of cateogries to search for 
 * @param numCategories number of categories in the categoris array
 * @param cost numercail value for cost 
 */ 
void processUserQuery(ArrayList *arr, Indexor *index, int day, char *time, char *city, char **category, int numCategories, int cost)
{
    int **toPass = assignRanks(arr, index, day, time, city, category, numCategories, cost);
    rankRestaurants(arr, toPass, numCategories);
}

/**
 * Assigns ranks then organizes the restaurants by their ranks 
 * @param tree knowledge base tree organized by name
 * @param locationIndex tree organized by location
 * @param day numerical value for day
 * @param time string val of the time to search for 
 * @param city string of city to search for 
 * @param categories array of cateogries to search for 
 * @param numCategories number of categories in the categoris array
 * @param cost numercail value for cost 
 * @param categoriesUsingDisjunctions determines whether we look for categories conjunctively (the default) or disjunctively
 */ 
void processUserQueryProject2(BinaryTree* tree, BinaryTree* locationIndex, int day, char* time, char* city, char** category, int numCategories, int cost, bool categoriesUsingDisjunctions) {
    LinkedList *exactMatches = createLinkedList();
    
}

/**
 * Assigns ranks to the restaurants by searching each of the indices and asssinging
 * a rank to each one of the restaruants in the knowledge base 
 * Also accounts for wildcard input 
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
int **assignRanks(ArrayList *arr, Indexor *index, int day, char *time, char *city, char **category, int numCategories, int cost)
{
    
    int **results = calloc(arr->size, sizeof(int *));
    for (int i = 0; i < arr->size; i++)
    {
        results[i] = calloc(4, sizeof(int));
    }

    // add if statements to account for wildcards
    if (strstr(time, "*"))
    {
        for (int i = 0; i < arr->size; i++)
        {
            results[i][0] = 1;
        }
    }
    else
    {
        IntArray *matchingTimes = searchTimeIndex(index->times, day, time);
        for (int i = 0; i < matchingTimes->size; i++)
        {
            results[getIntAt(matchingTimes, i)][0] = 1;
        }
        intArrayDestructor(matchingTimes);
    }

    if (strstr(city, "*"))
    {
        for (int i = 0; i < arr->size; i++)
        {
            results[i][1] = 1;
        }
    }
    else
    {
        IntArray *matchingCities = searchCityIndex(index->cities, city);
        for (int i = 0; i < matchingCities->size; i++)
        {
            results[getIntAt(matchingCities, i)][1] = 1;
        }
        intArrayDestructor(matchingCities);
    }

    // for each of the categories
    if (numCategories == 0)
    {
        for (int i = 0; i < arr->size; i++)
        {
            results[i][2] = 1;
        }
    }
    else
    {
        for (int i = 0; i < numCategories; i++)
        {
            IntArray *matchingCategories = searchCityIndex(index->categories, category[i]);
            for (int j = 0; j < matchingCategories->size; j++)
            {
                results[getIntAt(matchingCategories, j)][2] += 1;
            }
            intArrayDestructor(matchingCategories);
        }
    }

    // cost is also special
    if (cost == 1000)
    {
        for (int i = 0; i < arr->size; i++)
        {
            results[i][3] = 1;
        }
    }
    else
    {
        if (cost > 0)
        {
            IntArray *addLows = getRestaurantsFromCost(index->costs, 1);
            for (int i = 0; i < addLows->size; i++)
            {
                results[getIntAt(addLows, i)][3] += 1;
            }
            intArrayDestructor(addLows);
            if (cost > 1)
            {
                // add mediums in
                IntArray *addMediums = getRestaurantsFromCost(index->costs, 2);
                for (int j = 0; j < addMediums->size; j++)
                {
                    results[getIntAt(addMediums, j)][3] += 1;
                }
                intArrayDestructor(addMediums);
                if (cost > 2)
                {
                    IntArray *addHighs = getRestaurantsFromCost(index->costs, 3);
                    for (int k = 0; k < addHighs->size; k++)
                    {
                        results[getIntAt(addHighs, k)][3] += 1;
                    }
                    intArrayDestructor(addHighs);
                }
            }
        }
    }

    return results;
}

// old implementation that didn't user rank/cost 
/*
void rankRestaurants(ArrayList *arr, int **tally, int numCategories)
{
    ArrayList *exactMatches = createArrayList();
    ArrayList *distOnes = createArrayList();
    // add other things later
    int goal = 0; 

    // might change the categories here 
    if(numCategories == 0){
        goal = 4; 
    } else {
        goal = 3 + numCategories;
    }
    
    // get the sums from the tally
    for (int i = 0; i < arr->size; i++)
    {
        int sum = 0;
        for (int j = 0; j < 4; j++)
        {
            sum += tally[i][j];
        }
         //printf("Sum: %d - ", sum);
         //printf("%d, %d, %d, %d\n", tally[i][0], tally[i][1], tally[i][2], tally[i][3]);
        if (sum == goal)
        {
            insert(exactMatches, at(arr, i));
        }
        else if (sum == goal - 1)
        {
            // figure out what is causing the distance 
            insert(distOnes, at(arr, i));
        }
    }

    // DESTROY TALLY
    for (int i = 0; i < arr->size; i++)
    {
        free(tally[i]);
    }
    free(tally);

    printf("EXACT MATCHES: \n");
    if (exactMatches->size == 0)
    {
        printf("No results exactly matched your search\n");
    }
    printArray(exactMatches);

    printf("DISTANCE ONES");
    if(distOnes->size == 0){
        printf("No restaurants of distance 1 were found\n"); 
    }
    printArray(distOnes);

    arrayListShallowDestructor(distOnes);
    arrayListShallowDestructor(exactMatches);
}
*/

/**
 * Constructs linked lists that are sorted according to rank and cost (see LinkedList.c)
 * Finds the exact matches and distance ones and prints out these restaurants to the terminal 
 * @param arr knowledge base
 * @param tally the ranks
 * @param numCatgories the number of categories that have to match
 */ 
void rankRestaurants(ArrayList *arr, int **tally, int numCategories)
{
    LinkedList *exactMatches = createLinkedList();
    LinkedList *allButOpen = createLinkedList();
    LinkedList *allButCost = createLinkedList();
    LinkedList *allButCity = createLinkedList();
    LinkedList *allButCategory = createLinkedList();
    // add other things later
    int goal = 0; 

    // might change the categories here 
    if(numCategories == 0){
        goal = 4; 
    } else {
        goal = 3 + numCategories;
    }
    
    // get the sums from the tally
    for (int i = 0; i < arr->size; i++)
    {
        int sum = 0;
        for (int j = 0; j < 4; j++)
        {
            sum += tally[i][j];
        }
         //printf("Sum: %d - ", sum);
         //printf("%d, %d, %d, %d\n", tally[i][0], tally[i][1], tally[i][2], tally[i][3]);
        if (sum == goal)
        {
            insertInLinkedList(exactMatches, at(arr, i));
        }
        else if (sum == goal - 1)
        {
            // if open deviated 
            if(tally[i][0] == 0){
                insertInLinkedList(allButOpen, at(arr, i)); 
            } else if (tally[i][1] == 0){
                insertInLinkedList(allButCity, at(arr, i)); 
                
            } else if (tally[i][3] == 0){
                insertInLinkedList(allButCost, at(arr, i)); 
            } else if (tally[i][2] != numCategories){ // might be tricky with the wildcard??
                insertInLinkedList(allButCategory, at(arr, i)); 
            } 
     
        }
        
    }

    // DESTROY TALLY
    for (int i = 0; i < arr->size; i++)
    {
        free(tally[i]);
    }
    free(tally);

    printf("EXACT MATCHES: \n");
    if (exactMatches->size == 0)
    {
        printf("No results exactly matched your search\n");
    }
    printLinkedList(exactMatches); 

    printf("MATCHED ALL BUT OPEN TIME:\n");
    if(allButOpen->size == 0){
        printf("No restaurants of this kind were found\n"); 
    }
    printLinkedList(allButOpen);
    
    printf("MATCHED ALL BUT CITY:\n");
    if(allButCity->size == 0){
        printf("No restaurants of this kind were found\n"); 
    }
    printLinkedList(allButCity);

    printf("MATCHED ALL BUT CATEGORY:\n");
    if(allButCategory->size == 0){
        printf("No restaurants of this kind were found\n"); 
    }
    printLinkedList(allButCategory);

    printf("MATCHED ALL BUT COST:\n");
    if(allButCost->size == 0){
        printf("No restaurants of this kind were found\n"); 
    }
    printLinkedList(allButCost);

    linkedListDestructor(exactMatches);
    linkedListDestructor(allButOpen);
    linkedListDestructor(allButCity);
    linkedListDestructor(allButCategory); 
    linkedListDestructor(allButCost); 
}

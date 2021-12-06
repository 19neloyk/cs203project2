#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "FileReader.h"

/**
 * Reads in the text file
 * Makes sure that it's a valid file to read in 
 * If not, the program exits and prints an error message
 * Controls what datatype to readin based on the line numbers
 * @param filePath name of the file to read in 
 */

ArrayList *readIn(char *filePath)
{
    // open the file in read mode
    FILE *file;
    if ((file = fopen(filePath, "r")) == NULL)
    {
        printf("Error opening file\n");
        exit(1); // exits from the whole program
    }

    ArrayList *arr = createArrayList();
    Restaurant *current = malloc(sizeof(Restaurant));
    createEmptyRestuarant(current);

    // read in the file line by line
    int lineSize = 255;
    char *line = calloc(lineSize, sizeof(char));
    int lineNum = 0;
    while (fgets(line, lineSize, file))
    {

        if (*line == '\n')
        {
            lineNum = 0;

            Restaurant *temp = current;
            insert(arr, temp);
            //current = createEmptyRestuarant();
            current = malloc(sizeof(Restaurant));
            createEmptyRestuarant(current);
            // printf("Created new restaurant\n");
        }
        else
        {
            if (lineNum == 0)
            {
                // name
                readName(current, line);
                lineNum = 1;
            }
            else if (lineNum == 1)
            {
                // city
                readCity(current, line);
                lineNum = 2;
            }
            else if (lineNum == 2)
            {
                // category
                readCategories(current, line);
                lineNum = 3;
            }
            else if (lineNum == 3)
            {
                // open time
                readTimes(current, line);
                lineNum = 4;
            }
            else if (lineNum == 4)
            {

                // cost
                readCost(current, line);
                
                lineNum = 5;
            }
            else if (lineNum == 5)
            {
                //rank
                char *ptr3 = line;
                current->rank = atof(ptr3);
                lineNum = 6;
            }
            else if (lineNum == 6)
            {
                // reviewers
                char *ptr4 = line;
                current->reviewers = atoi(ptr4);
                
            }
        }
        free(line);
        line = calloc(lineSize, sizeof(char));
    }

    // insert and free the final restaurant
    insert(arr, current);

    // free the last line
    free(line);

    // close the file
    fclose(file);

    return arr;
}

/**
 * Reads in the name of the restaruant 
 * Gets rid of \n and spaces 
 * @param curr Restuarant to assign the name to 
 * @param linea the line read in from the file 
 * 
 */ 
void readName(Restaurant *curr, char *linea)
{
    char *ptr = linea;
    if (ptr[strlen(ptr) - 1] == '\n')
    {
        ptr[strlen(ptr) - 1] = '\0';
    }
    if(ptr[strlen(ptr)-1] == ' '){
        ptr[strlen(ptr) - 1] = '\0';
    }
    setName(curr, ptr);

}

/**
 * Reads in the city of the restaurant
 * Gets rid of null term and spaces
 * @param curr Restaurant to assign the city to 
 * @param linea the line read in from the file 
 */
void readCity(Restaurant *curr, char *linea)
{

    char *ptr = linea;
    if (ptr[strlen(ptr) - 1] == '\n')
    {
        ptr[strlen(ptr) - 1] = '\0';
    }

    if(ptr[strlen(ptr)-1] == ' '){
        ptr[strlen(ptr) - 1] = '\0';
    }
    setCity(curr, ptr);

}

/**
 * Reads in the categories of the restaurant
 * Parses based on comma followed by a space
 * Creates a category array 
 * @param curr restaurant to assign the category array to 
 * @param linea the line read in from the file 
 */ 
void readCategories(Restaurant *curr, char *linea)
{

    int counter = 1;
    //int b = 0;
    for(int i = 0; i < strlen(linea); i++){
        if(linea[i] == '\n'){
            break; 
        } else if (linea[i] == ','){
            counter++; 
        }
    }
    
    // note used to calloc counter + 1 ... uneccesary? 
    char **cats = calloc(counter, sizeof(char *));
    for (int i = 0; i < counter; i++)
    {
        cats[i] = calloc(100, sizeof(char));
    }

    // get to the right point in the string
    char *ptr2 = linea;
    const char s[2] = ",";
    char *token = strtok(ptr2, s);
    int a = 0;
    while (token != NULL)
    {
        if (a > 0)
        {
            if (token[strlen(token) - 1] == '\n')
            {
                token[strlen(token) - 1] = '\0';
            }
            if (token[strlen(token) - 1] == ' ')
            {
                token[strlen(token) - 1] = '\0';
            }

            int j = 0;
            for (int i = 1; i < strlen(token); i++)
            {
                cats[a][j] = token[i];
                
                j++;
            }
        }
        else
        {
            if (token[strlen(token) - 1] == '\n')
            {
                token[strlen(token) - 1] = '\0';
            }
            if (token[strlen(token) - 1] == ' ')
            {
                token[strlen(token) - 1] = '\0';
            }
            for (int i = 0; i < strlen(token); i++)
            {
                cats[a][i] = token[i];
            }
        }
        token = strtok(NULL, s);
        a++;
    }

    //cats[counter] = NULL; // end of category needs a NULL right now
   
    setCategory(curr, cats, counter);
}

/**
 * Reads in the time for the restaurant
 * Parses based on the day and assigns open/close time
 * Creates a time array that is assigned to the restuarant
 * @param curr restaruant to assign the time array to 
 * @param linea the line read in from the file 
 */ 
void readTimes(Restaurant *curr, char *linea)
{
    char ***times = malloc(sizeof(char**) * 7);
    for (int i = 0; i < 7; i++)
    {
        times[i] = malloc(sizeof(char*) * 2);
        times[i][0] = calloc(6, sizeof(char)); //why is this line causing trouble? 
        times[i][1] = calloc(6, sizeof(char));
    }

    if (strstr(linea, "Sunday"))
    {
        openClose(linea, "Sunday", 0, times);
    }
    if (strstr(linea, "Monday"))
    {
        openClose(linea, "Monday", 1, times);
    }
    if (strstr(linea, "Tuesday"))
    {
        openClose(linea, "Tuesday", 2, times);
    }
    if (strstr(linea, "Wednesday"))
    {
        openClose(linea, "Wednesday", 3, times);
    }
    if (strstr(linea, "Thursday"))
    {
        openClose(linea, "Thursday", 4, times);
    }
    if (strstr(linea, "Friday"))
    {
        openClose(linea, "Friday", 5, times);
    }
    if (strstr(linea, "Saturday"))
    {
        openClose(linea, "Saturday", 6, times);
    }
    setTime(curr, times);
    return;
}

/**
 * Reads in the open and close time given the day 
 * Basically starts where the day was found in the input line and reads in chars from there
 * @param line line read in from the file 
 * @param day string of the day to search for, helps you get to the right part of the string
 * @param dayNum the numerical value of the day
 * @param timeArr the times table creaed in readTimes 
 */ 
void openClose(char* line, char* day, int dayNum, char*** timeArr)
{
    char *start = strstr(line, day);
    char *ptr = start;
    int a = 0;
    while (start[a] != ' ')
    {
        ptr++;
        a++;
    }
    ptr++;

    for(int i = 0; i < 5; i ++){
        timeArr[dayNum][0][i] = ptr[i]; 
    }
    // add a zero to the beginning if it wasn't in the right format... 
    
    if(timeArr[dayNum][0][4] == ' '){
        for(int i = 4; i > 0; i--){
            timeArr[dayNum][0][i] = timeArr[dayNum][0][i-1];
        }
        timeArr[dayNum][0][0] = '0'; 
    }
    
    ptr++;
    a++;
    
    while (start[a] != ' ')
    {
        ptr++;
        a++;
    }

    
    for(int i = 0; i < 5; i ++){
        timeArr[dayNum][1][i] = ptr[i]; 
    }

    if(timeArr[dayNum][1][4] == ' '){
        for(int i = 4; i > 0; i--){
            timeArr[dayNum][1][i] = timeArr[dayNum][1][i-1];
        }
        timeArr[dayNum][1][0] = '0'; 
    }
    //printf("close:%s\n", close);
    //timeArr[dayNum][1] = close;
    return;
}

/**
 * Reads in the cost and determines a numerical value for it 
 * $ = 1
 * $$ = 2
 * $$$ = 3
 * @param curr restaurant to assign the cost to 
 * @param linea the line read in from the file 
 */ 
void readCost(Restaurant *curr, char *linea)
{

    int dollars = 0;
    if (strstr(linea, "$$$"))
    {
        dollars = 3;
    }
    else if (strstr(linea, "$$"))
    {
        dollars = 2;
    }
    else if (strstr(linea, "$"))
    {
        dollars = 1;
    }
    curr->cost = dollars;
}

#include "Controller.h"
#include <string.h>

/**
 * Creates the Query object and inializes fields to some default values
 * 
 * @return Query created 
 */ 
Query *createQuery()
{
    Query *q = malloc(sizeof(Query));
    q->day = -1;
    q->time = "";
    q->city = "";
    q->category = NULL;
    q->numCategories = -1; 
    q->cost = -1;
    q->categoriesAreDisjunctive = false;
    return q;
}

/**
 * Frees anything that was malloc'd in the Query
 * Frees the Query itself 
 * Assues that the city, time, and categories were dynamically allocated and assigned at some point 
 */ 
void queryDestructor(Query *q)
{
    free(q->city);
    free(q->time);
    for(int i = 0; i < q->numCategories; i++){
        free(q->category[i]); 
    }
    free(q->category); 
    free(q);
}


/**
 * Prints the contents query, primarly used for debugging 
 * @param q Query to print
 */ 
void printQuery(Query *q)
{
    printf("Your query: \n");
    printf("City: %s\n", q->city); 
    printf("Day: %d, Time: %s\n", q->day, q->time);
    printf("Num categories %d\n", q->numCategories); 
    printf("Categories: ");
    for (int i = 0; i < q->numCategories; i++)
    {
        printf("%s ", q->category[i]);
    }
    printf("\nCost: %d\n", q->cost);
}

/**
 * Controls the flow of the program. 
 * Reads in the restaurant file and populates the knowledge file (see FileReader.c for implementaiton of readIn)
 * Creates all the indexing stuctores and populates them (see Indexor.c for implementaiton detaails)
 * Controls the user queries flow 
 */ 
void control()
{
    ArrayList *rests = readIn("restaurants.txt");
    Indexor *index = createIndex();
    indexRestaurants(rests, index);

    while (true)
    {
        char *queryy = getQuery();
        processQuery(queryy, rests, index);
        free(queryy);
    }
}


/**
 * Controls the flow of the program for PROJECT2. 
 * Reads in the restaurant file and populates the knowledge file (see FileReader.c for implementaiton of readIn)
 * Creates all the indexing stuctores and populates them (see Indexor.c for implementaiton detaails)
 * Controls the user queries flow 
 */ 
void controlProject2()
{

    BinaryTree* rests = readINBT("restaurants.txt");

    BinaryTree* locInd = buildLocationIndex(rests);
    while (true)
    {
        char *queryy = getQuery();
        processQueryProject2(queryy, rests, locInd);
        free(queryy);
    }
}



/**
 * Determines what the user wants based on their query
 * p = print the knowledge base (in original readIn order)
 * s = search the knowledge base
 * x = exit the program (destructors are called here to clean up the program)
 * 
 * @param query user's query, got it from getQuery
 * @param arr ArrayList, the knowledge base 
 * @param index Indexor, the indices of all the restaurants in the knowledge base
 */ 
void processQuery(char *query, ArrayList *arr, Indexor *index)
{
   
    if (strcmp(query, "p") == 0)
    {
        printArray(arr);
    }
    else if (strcmp(query, "x") == 0)
    {
        free(query);
        arrayListDestructor(arr);
        indexDestructor(index);
        printf("Goodbye!\n");
        exit(0);
    }
    else if (strcmp(query, "s") == 0)
    {
        searchQuery(arr, index); 
    }
    else
    {
        printf("Invalid command. Valid input: \np - print all restaurants\ns - search for a restaurant\nx - exit the program\n");
    }
}


void processQueryProject2(char* query, BinaryTree* tree, BinaryTree* locationIndex) {
    if (strcmp(query, "p") == 0)
    {
        printBT(tree);
    }
    else if (strcmp(query, "x") == 0)
    {
        //COMMENTS DIRECTLY BELOW ARE FUNCTIONS REQUIRED TO FREE THE ARRAY VERSION OF THIS PROGRAM
        /*
        free(query);
        arrayListDestructor(arr);
        indexDestructor(index);
        */
        printf("Goodbye!\n");
        exit(0);
    }
    else if (strcmp(query, "s") == 0)
    {
        searchQueryProject2(tree, locationIndex); 
    }
    else if (strcmp(query, "a") == 0) {
        addQueryProject2(tree, locationIndex);
    }
    else if (strcmp(query, "m") == 0) {
        modifyQueryProject2(tree);
    }
    else if (strcmp (query, "e") == 0) {
        matchQueryProject2(tree);
    }
    else if (strcmp (query, "w") == 0) {
        writeQueryProject2(tree, locationIndex);
    }
    else if (strcmp (query, "r") == 0) {
        removeQueryProject2(tree, locationIndex);
    }
    else
    {
        printf("Invalid command. Valid input: \np - print all restaurants\ns - search for a restaurant\nx - exit the program\na - add a restaurant\nm ??? modify a restaurant specified by name and location\ne ??? print information of specified restaurant based on name and location\nw ??? write another file's restaurants to this database\nr ??? remove a restaurant from the database specified by name and location\n");
    }
}



/**
 * Reads in the user's query into a string that is returned
 * 100 characters are read in (more than enough for a query)
 * 
 * @return char* of the user's query, read in from the terminal 
 */ 
char* getQuery()
{
    // should I dynamically allocate this instead?
    char *query = malloc(sizeof(char) * 100);
    printf("Query: ");
    scanf(" %100[^\n]s", query);
    return query;
}

/**
 * Get rid of any extra spaces that the user may have put at the end
 * Replace spaces with \0 null terminating char 
 * @param s string to possibly trim 
 */ 
void trimQuery(char* s){
    while(s[strlen(s)-1] == ' '){
        s[strlen(s)-1] = '\0'; 
    }
}

/**
 * Called when the user wants to search the knowledge base
 * @param arr knowledge base
 * @param index indices
 */ 
void searchQuery(ArrayList* arr, Indexor* index)
{
    Query *q = createQuery();
    
    char *qCity = malloc(sizeof(char) * 100);
    printf("City: ");
    scanf(" %100[^\n]s", qCity);
    trimQuery(qCity); 

    q->city = qCity; 
    

    char *qCategory = malloc(sizeof(char) * 100);
    printf("Categories: ");
    
    scanf(" %100[^\n]s", qCategory);
    trimQuery(qCategory); 
    if(strstr(qCategory, "*")){
        q->numCategories = 0; 
        
    } else {
       
        processCategory(qCategory, q); 
    }
    

    // process the cost
    char *qCost = malloc(sizeof(char) * 50);
    printf("Cost ($, $$, $$$): ");
    scanf(" %50[^\n]s", qCost);
    trimQuery(qCost); 
    
    processCost(qCost, q);
     
    // process the time
    char *qTime = malloc(sizeof(char) * 50);
    printf("Time (day/hr ex. Monday/13:00): ");
    scanf(" %50[^\n]s", qTime);
    trimQuery(qTime); 

    if(strstr(qTime, "*")){
        q->time = calloc(2, sizeof(char)); 
        q->time[0] = '*'; 
    } else {
        processTime(qTime, q);
    }
    


    processUserQuery(arr, index, q->day, q->time, q->city, q->category, q->numCategories, q->cost);
    
    //printQuery(q);

    free(qCategory); 
    free(qCost);
    free(qTime);
    queryDestructor(q);
}

/**
 * Parses the category query
 * Assumes comma separated, no space in between 
 * Figures out the number of categories and mallocs based off of that 
 * Called in searchQuery
 * @param qCategory string containing the user's query 
 * @param q Query object
 */ 
void processCategoryProject2(char *qCategory, Query *q)
{
    // parse that string
    // check restaurant class to see whether we are suppose to malloc the strings that go in the array
    int counter = 1;
    // EITHER USES "OR" (DISJUNCTION) or "," (CONJUNCTION)
    // both of these strings cannot be within the string
    bool usingOR = false;

    // Checks for how many commas as an indicator
    // of how much to allocate the array used for queries
    for(int i = 0; i < strlen(qCategory); i++){
        if(qCategory[i] == '\n'){
            break;
        } else if (qCategory[i] == ','){
            counter++; 
        } 
    }

    // Checks for how many commas as an indicator
    // of how much to allocate the array used for queries
    for(int i = 0; i < strlen(qCategory) - 1; i++){
        if(qCategory[i] == '\n'){
            break;
        } else if (qCategory[i] == 'O' && qCategory[i + 1] == 'R'){
            counter++; 
            usingOR = true;
        } 
    }

    // allocate array
    char **cats = calloc(counter, sizeof(char *));
    for (int i = 0; i < counter; i++)
    {
        cats[i] = calloc(100, sizeof(char));
    }

    char *ptr2 = qCategory;
    char *token;

    //Choose delimiter based on if we are using
    if (usingOR) {
        token = strtok(ptr2, " OR ");
    } else {
        token =  strtok(ptr2, ",");  
    }

    int a = 0;
    while (token != NULL)
    {

        if (token[strlen(token) - 1] == '\n')
        {
            token[strlen(token) - 1] = '\0';
        }
        int j = 0;
        for (int i = 0; i < strlen(token); i++)
        {
            cats[a][i] = token[i];
        }

        if (usingOR) {
            token = strtok(NULL, " OR ");
        } else {
            token =  strtok(NULL, ",");  
        }

        a++;
    }

    q->numCategories = counter;
    q->category = cats;
    q->categoriesAreDisjunctive = usingOR;
}

/**
 * Called when the user wants to search the knowledge base
 * @param tree knowledge base tree
 * @param locationIndex tree organized by location serving as index 
 */ 
void searchQueryProject2(BinaryTree* tree, BinaryTree* locationIndex)
{
    Query *q = createQuery();
    
    char *qCity = malloc(sizeof(char) * 100);
    printf("City: ");
    scanf(" %100[^\n]s", qCity);
    trimQuery(qCity); 

    q->city = qCity; 
    

    char *qCategory = malloc(sizeof(char) * 100);
    printf("Categories: ");
    
    scanf(" %100[^\n]s", qCategory);
    trimQuery(qCategory); 
    if(strstr(qCategory, "*")){
        q->numCategories = 0; 
    } else {
        processCategoryProject2(qCategory, q); 
    }
    

    // process the cost
    char *qCost = malloc(sizeof(char) * 50);
    printf("Cost ($, $$, $$$): ");
    scanf(" %50[^\n]s", qCost);
    trimQuery(qCost); 
    
    processCost(qCost, q);
     
    // process the time
    char *qTime = malloc(sizeof(char) * 50);
    printf("Time (day/hr ex. Monday/13:00): ");
    scanf(" %50[^\n]s", qTime);
    trimQuery(qTime); 

    if(strstr(qTime, "*")){
        q->time = calloc(2, sizeof(char)); 
        q->time[0] = '*'; 
    } else {
        processTime(qTime, q);
    }

    searchForCriteria(tree, locationIndex, q->day, q->time, q->city, q->category, q->numCategories, q->cost, q->categoriesAreDisjunctive);

    //printQuery(q);
    free(qCategory); 
    free(qCost);
    free(qTime);
    queryDestructor(q);
}


/**
 * Called when the user wants to add a restaurant to the knowledge base
 * @param tree knowledge base
 * @param index indices
 */ 
void addQueryProject2(BinaryTree* tree, BinaryTree* locationIndex) {
    Restaurant* toAdd = (Restaurant*) malloc (sizeof(Restaurant));
    createEmptyRestuarant(toAdd);

    int lineSize = 300;
    char *line = (char*) malloc(sizeof(char) * 300);
    printf("Name: ");
    scanf(" %200[^\n]s", line);
    readName(toAdd, line);

    printf("City: ");
    scanf(" %200[^\n]s", line);
    readCity(toAdd, line);

    printf("Categories: ");
    scanf(" %200[^\n]s", line);
    readCategories(toAdd, line);

    printf("Times: ");
    scanf(" %200[^\n]s", line);
    readTimes(toAdd, line);

    printf("Cost: ");
    scanf(" %200[^\n]s", line);
    readCost(toAdd, line);

    printf("Rank: ");
    scanf(" %200[^\n]s", line);
    toAdd->rank = atof(line);

    printf("Reviewers: ");
    scanf(" %200[^\n]s", line);
    toAdd->reviewers = atoi(line);

    insertInBTName(toAdd, tree);
    insertInBTLocation(toAdd, locationIndex);

    printf("Restaurant has been added!\nHere is the content:\n??????????????????????????????????????????????????????????????????????????????????????????????????????\n");
    printRestaurant(toAdd);
}

/**
 * Called when the user wants to modify a restaurant in the knowledge base
 * @param tree the knowledge base tree
 */ 
extern void modifyQueryProject2(BinaryTree* tree){
    Restaurant* modified = (Restaurant*) malloc (sizeof(Restaurant));
    createEmptyRestuarant(modified);

    int lineSize = 300;
    char *line = (char*) malloc(sizeof(char) * 300);
    printf("Name: ");
    scanf(" %200[^\n]s", line);
    readName(modified, line);

    printf("City: ");
    scanf(" %200[^\n]s", line);
    readCity(modified, line);

    printf("Categories: ");
    scanf(" %200[^\n]s", line);
    readCategories(modified, line);

    printf("Times: ");
    scanf(" %200[^\n]s", line);
    readTimes(modified, line);

    printf("Cost: ");
    scanf(" %200[^\n]s", line);
    readCost(modified, line);

    printf("Rank: ");
    scanf(" %200[^\n]s", line);
    modified->rank = atof(line);

    printf("Reviewers: ");
    scanf(" %200[^\n]s", line);
    modified->reviewers = atoi(line);

    Restaurant* toBeModified = findRestaurantName(tree, modified->name, modified->city);

    if (toBeModified == NULL) {
        printf("Unfortunately, a restaurant with that name or location does not exist\n????????????????????????????????????????????????????????????????????????????????????????????????\n");
        return;
    }

    setTime(toBeModified, modified->times);
    setCategory(toBeModified, modified->category, modified->numCategory);
    toBeModified->cost = modified->cost;
    toBeModified->rank = modified->rank;
    toBeModified->reviewers = modified->reviewers;

    //Do not free modified right now or there will be errors

    printf("Restaurant has been modified!\nHere is the content:\n??????????????????????????????????????????????????????????????????????????????????????????????????????\n");
    printRestaurant(toBeModified);
}


/**
 * Called when the user wants to modify a restaurant in the knowledge base
 * @param tree the knowledge base tree
 */ 
extern void matchQueryProject2(BinaryTree* tree){
    //Create a model restaurant to use as querying information
    Restaurant* model = (Restaurant*) malloc (sizeof(Restaurant));
    createEmptyRestuarant(model);

    int lineSize = 300;
    char *line = (char*) malloc(sizeof(char) * 300);
    printf("Name: ");
    scanf(" %200[^\n]s", line);
    readName(model, line);

    printf("City: ");
    scanf(" %200[^\n]s", line);
    readCity(model, line);

    Restaurant* match = findRestaurantName(tree, model->name, model->city);
    if (match == NULL) {
        printf("Unfortunately, a restaurant with that name or location does not exist\n????????????????????????????????????????????????????????????????????????????????????????????????\n");
        return;
    }

    //Do not free modified right now or there will be errors
    printf("Restaurant has been found!\nHere is the content:\n??????????????????????????????????????????????????????????????????????????????????????????????????????\n");
    printRestaurant(match);
}

/**
 * Called when the user wants to write a file to the knowledge base
 * @param tree the knowledge base tree
 * @param locationIndex the index tree for location
 */ 
void writeQueryProject2(BinaryTree* tree, BinaryTree* locationIndex ) {
    char* filePath = (char *) malloc(150 * sizeof(char));
    printf("Filename: ");
    scanf(" %100[^\n]s", filePath);

    // open the file in read mode
    FILE *file;
    if ((file = fopen(filePath, "r")) == NULL)
    {
        printf("Error opening file\n");
        return;
    }


    Restaurant *current = malloc(sizeof(Restaurant));
    createEmptyRestuarant(current);

     // read in the file line by line
    int lineSize = 255;
    char *line = calloc(lineSize, sizeof(char));
    int lineNum = 0;
    while (fgets(line, lineSize, file))
    {
        //Case when we encounter the next restaurant
        if (*line == '\n')
        {
            lineNum = 0;
            Restaurant *temp = current;
            insertInBTName(temp, tree);
            insertInBTLocation(temp, locationIndex);
            //insertInBTLocation(temp, tree);
            //current = createEmptyRestuarant();
            current = malloc(sizeof(Restaurant)); //To make the next restaurant
            createEmptyRestuarant(current);
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
    insertInBTName(current, tree);
    insertInBTLocation(current, locationIndex);
    // free the last line
    free(line);
    free(filePath);

    // close the file
    fclose(file);

}



/**
 * Called when the user wants to remove a file from the knowledge base
 * @param tree the knowledge base tree
 * @param locationIndex the index tree for location
 */ 
void removeQueryProject2(BinaryTree* tree, BinaryTree* locationIndex) {
    //Create a model restaurant to use as querying information
    Restaurant* model = (Restaurant*) malloc (sizeof(Restaurant));
    createEmptyRestuarant(model);

    int lineSize = 300;
    char *line = (char*) malloc(sizeof(char) * 300);
    printf("Name: ");
    scanf(" %200[^\n]s", line);
    readName(model, line);

    printf("City: ");
    scanf(" %200[^\n]s", line);
    readCity(model, line);

    removeNodeByNameBST(tree, model->name, model->city);
    removeNodeByLocationBST(locationIndex, model->name, model->city);
    printf("Removal process has successfully completed\n");
}


/**
 * Parses the category query
 * Assumes comma separated, no space in between 
 * Figures out the number of categories and mallocs based off of that 
 * Called in searchQuery
 * @param qCategory string containing the user's query 
 * @param q Query object
 */ 
void processCategory(char *qCategory, Query *q)
{
    // parse that string
    // check restaurant class to see whether we are suppose to malloc the strings that go in the array
    int counter = 1;

    //printf("QCATEGORY STRLEN: %ld\n", strlen(qCategory)); 
    for(int i = 0; i < strlen(qCategory); i++){
        if(qCategory[i] == '\n'){
            break;
        } else if (qCategory[i] == ','){
            counter++; 
        }
    }
    // allocate array
    char **cats = calloc(counter, sizeof(char *));
    for (int i = 0; i < counter; i++)
    {
        cats[i] = calloc(100, sizeof(char));
    }

    char *ptr2 = qCategory;
    const char s[2] = ",";
    char *token = strtok(ptr2, s);
    int a = 0;
    while (token != NULL)
    {

        if (token[strlen(token) - 1] == '\n')
        {
            token[strlen(token) - 1] = '\0';
        }
        int j = 0;
        for (int i = 0; i < strlen(token); i++)
        {
            cats[a][i] = token[i];
        }
        token = strtok(NULL, s);
        a++;
    }

    q->numCategories = counter;
    q->category = cats;
}

/**
 * Assigns a numerical value to the cost
 * $ = 1
 * $$ = 2
 * $$$ = 3
 * 0 if the querr mistakenly did not contain any $ amount 
 * @param qCost string containing cost value
 * @param q Query objec t
 */ 
void processCost(char *qCost, Query *q)
{
    int dollars = 0;
    if (strstr(qCost, "$$$"))
    {
        dollars = 3;
    }
    else if (strstr(qCost, "$$"))
    {
        dollars = 2;
    }
    else if (strstr(qCost, "$"))
    {
        dollars = 1;
    } 
    else if (strstr(qCost, "*")){
        dollars = 1000; 
    }
    q->cost = dollars;
}

/**
 * Determines what day was in qTime and assigns a numerical value
 * for (Sunday, Monday,..., Saturday) the ints (0, 1,..., 6) are assigned
 * Assumes input was formatted correctly day/hr ex. Monday/12:00
 * @param qTime string containing time info 
 * @param q Query object 
 */ 
void processTime(char *qTime, Query *q)
{
    // first process the day
    int day = -1;
    if (strstr(qTime, "Sunday")){
        day = 0;
    }
    else if (strstr(qTime, "Monday")){
        day = 1;
    }
    else if (strstr(qTime, "Tuesday")){
        day = 2;
    }
    else if (strstr(qTime, "Wednesday")){
        day = 3;
    }
    else if (strstr(qTime, "Thursday")){
        day = 4;
    }
    else if (strstr(qTime, "Friday")){
        day = 5;
    }
    else if (strstr(qTime, "Saturday")){
        day = 6;
    }

    char *time = calloc(6, sizeof(char));

    int a = 0;
    char *start = qTime;
    while (start[a] != '/')
    {
        qTime++;
        a++;
        if (a > 50)
        {
            // if it gets here, something was invalid about the input
            break;
        }
    }
    qTime++;

    for (int i = 0; i < 5; i++)
    {
        time[i] = qTime[i];
    }

    // looking for a null terminating here from the calloc
    if (time[4] == '\0')
    {
        for (int i = 4; i > 0; i--)
        {
            time[i] = time[i - 1];
        }
        time[0] = '0';
    }

    q->day = day;
    q->time = time;
}


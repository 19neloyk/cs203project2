#include "BinaryTree.h"

BinaryTree* createBT() {
    BinaryTree* tree = (BinaryTree*) malloc(sizeof(BinaryTree));
    tree->root = NULL;
    return tree;
}

BTNode* createBTNode(Restaurant* r) {
    BTNode* node = (BTNode*) malloc(sizeof(BTNode));
    node->rest = r;
    node->left = NULL;
    node->right = NULL;
    return node;
} 

void printBTHelper(BTNode* node) {
    if (node->left != NULL) {
        printBTHelper(node->left);    
    }
    printRestaurant(node->rest);
    printf("__________________________________________________\n\n");
    if (node->right != NULL) {
        printBTHelper(node->right);    
    }
}

void printBT(BinaryTree* tree) {
    if (tree->root == NULL) {
        return;
    }

    printf("__________________________________________________\n\n");
    printBTHelper(tree->root);
}



//We traverse the initial tree inorder with recursion
//Then add the current node to the locationIndex tree
void buildLocationIndexHelper(BinaryTree* locationIndex, BTNode* node) {
    if (node->left != NULL) {
        buildLocationIndexHelper(locationIndex,node->left);
    }
    insertInBTLocation(node->rest, locationIndex);

    if (node->right != NULL) {
        buildLocationIndexHelper(locationIndex,node->right);
    }
}


BinaryTree* buildLocationIndex(BinaryTree* tree) {
    BinaryTree* locationIndex = createBT();
    if (tree->root != NULL) {
        buildLocationIndexHelper(locationIndex, tree->root);
    }
    return locationIndex;
}


//Recursive helper function to searchForCriteria()
//Uses inorder traversal to see all the elements
void searchHelper(ArrayList* matches, BTNode* current, int day, char* time, char* city, char** category, int numCategories, int cost, bool categoriesUsingDisjunctions) {
    if (current->left != NULL) {
        searchHelper(matches, current->left, day, time, city, category, numCategories, cost, categoriesUsingDisjunctions);
    }
    //Now do checking do see if this should 
    if (checkMatch(current->rest, day, time, city, category, numCategories, cost, categoriesUsingDisjunctions)) {
        insert(matches, current->rest);
    }
    if (current->right != NULL) {
        searchHelper(matches, current->right, day, time, city, category, numCategories, cost, categoriesUsingDisjunctions);
    }
}

//Uses an in order traversal in order to ensure that this code runs very well
void searchForCriteria(BinaryTree* tree, BinaryTree* locationIndex, int day, char* time, char* city, char** category, int numCategories, int cost, bool categoriesUsingDisjunctions) {
    ArrayList* matches = createArrayList();
    if (strstr(city, "*")) {
        if (tree->root != NULL) {
            searchHelper(matches, tree->root, day, time, city, category, numCategories, cost, categoriesUsingDisjunctions);
        }
    } else {
        //Use location index in case of name wildcard
        if (locationIndex->root != NULL) {
            searchHelper(matches, locationIndex->root, day, time, city, category, numCategories, cost, categoriesUsingDisjunctions);
        }
    }

    printArray(matches);
;
    arrayListShallowDestructor(matches);
}


/**
 * Used for tree node comparisons in insertion, removal, and search for name
 * If a > b, return 1; if b < a; return -1; if a == b return 0
 */
int compareRestaurantName(Restaurant* a, Restaurant* b) {
    return strcmp(a->name, b->name);
}

/**
 * Used for tree node comparisons in insertion, removal, and search for location
 * If a > b, return 1; if b < a; return -1; if a == b return 0
 */
int compareRestaurantLocation(Restaurant* a, Restaurant* b) {
    return strcmp(a->city, b->city);
}



void insertInBTName(Restaurant* r, BinaryTree* tree) {
    BTNode* newNode = createBTNode(r);

    if (tree->root == NULL) {
        tree->root = newNode;
        return;
    }

    //Current restaurant in BT
    BTNode* cur = tree->root;

    //Represents trailing value of cur
    BTNode* trailing = NULL;

    while (cur != NULL) {
        trailing = cur;
        if (compareRestaurantName(newNode->rest, cur->rest) <= 0) {
            cur = cur-> left;
        } else {
            cur = cur-> right;
        }
        
    }

    if (compareRestaurantName(newNode->rest, trailing->rest) <= 0) {
        trailing->left = newNode;
    } else {
        trailing->right = newNode;
    }

    return;
}


void insertInBTLocation(Restaurant* r, BinaryTree* tree) {
    BTNode* newNode = createBTNode(r);

    if (tree->root == NULL) {
        tree->root = newNode;
        return;
    }

    //Current restaurant in BT
    BTNode* cur = tree->root;

    //Represents trailing value of cur
    BTNode* trailing = NULL;

    while (cur != NULL) {
        trailing = cur;
        if (compareRestaurantLocation(newNode->rest, cur->rest) <= 0) {
            cur = cur-> left;
        } else {
            cur = cur-> right;
        }
    }

    if (compareRestaurantLocation(newNode->rest, trailing->rest) <= 0) {
        trailing->left = newNode;
    } else {
        trailing->right = newNode;
    }

    return;
}

/**
 * @param tree the three we would like to search for hte restaurant in
 * @param name the name of the restaurant that we are searching for
 * @param city the location of the restaurant that we are searching for
 * @return the Restaurant node that has been found
 */
Restaurant* findRestaurantName(BinaryTree* tree, char* name, char* city) {


    BTNode* cur = tree->root;

    if (cur == NULL) {
        return NULL;
    }

    while (cur != NULL) {
        Restaurant* curRest = cur->rest;
        char* curName = curRest->name;
        char* curCity = curRest->city;
        if (strcmp(name, curName) <= 0) {
            if (strcmp(city, curCity) == 0 ) {
                return  curRest;
            }
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }

    //No restaurant found
    return NULL;
}


/**
 * @param tree the three we would like to search for hte restaurant in
 * @param name the name of the restaurant that we are searching for
 * @param city the location of the restaurant that we are searching for
 * @return the Restaurant node that has been found
 */
Restaurant* findRestaurantLocation(BinaryTree* tree, char* name, char* city) {
    BTNode* cur = tree->root;

    if (cur == NULL) {
        return NULL;
    }

    while (cur != NULL) {
        Restaurant* curRest = cur->rest;
        char* curName = curRest->name;
        char* curCity = curRest->city;
        if (strcmp(city, curCity) <= 0) {
            if (strcmp(name, curName) == 0 ) {
                return  curRest;
            }
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }

    //No restaurant found
    return NULL;
}
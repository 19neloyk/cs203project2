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
/**
 * Remove a restaurant node from the main tree node (based on name)
 * @param root represents root of the current node we are exploring 
 * @param name name of the restaurant that we are looking for
 * @param location location of the restaurant that we are looking for
 * @return value of root node
 */ 
BTNode* removeNodeName(BTNode* root, char* name, char* location) {
    if (root == NULL) {
        return root;
    }
    //Traverse left subtree
    if (strcmp(name, root->rest->name) < 0  || (strcmp(name, root->rest->name) == 0 && strcmp(location, root->rest->city) != 0)) {
        root->left = removeNodeName(root->left, name, location);
    //Traverse right subtree
    } else if (strcmp(name, root->rest->name) > 0 || (strcmp(name, root->rest->name) == 0 && strcmp(location, root->rest->city) != 0)) {
        root->right = removeNodeName(root->right, name, location);

    //Case where there is a match; removal happens
    } else {
        //Case with one or zero child nodes
        if (root->left == NULL) {
            BTNode* temp = root->right;
            //Destroy the node here >>>
            return temp;
        }
        else if (root->right == NULL) {
            BTNode* temp = root->left;
            //Destroy the node here >>>
            return temp;
        }

        //Node with two children
        //We have to get the minimum element on the right subtree
        BTNode* aboveSuccessor = root;
        BTNode* successor = root->right;
        BTNode* underSuccessor = successor-> left;
        while (underSuccessor != NULL) {
            aboveSuccessor = successor;
            successor = underSuccessor;
            underSuccessor = underSuccessor->left;
        }

        // Now the correct values for aboveSuccessor, successor, and underSuccessor are present
        // We now remove successor (which by construction of our loop is a leaf, so it is 
        // really not so complicated) 
        aboveSuccessor->left = NULL;
        successor->right = root->right;
        root = successor;
        return root;
    }
    return root;
}

/**
 * Remove a restaurant node from the main tree node (based on name)
 * @param root represents root of the current node we are exploring 
 * @param name name of the restaurant that we are looking for
 * @param location location of the restaurant that we are looking for
 */ 
void removeNodeByNameBST(BinaryTree* tree, char* name, char* location) {
    tree->root = removeNodeName(tree->root, name, location);
}



/**
 * Remove a restaurant node from the index location tree node (based on location)
 * @param root represents root of the current node we are exploring 
 * @param name name of the restaurant that we are looking for
 * @param location location of the restaurant that we are looking for
 * @return value of root node
 */ 
BTNode* removeNodeLocation(BTNode* root, char* name, char* location) {
    if (root == NULL) {
        return root;
    }
    //Traverse left subtree
    if (strcmp(name, root->rest->name) < 0  || (strcmp(name, root->rest->name) == 0 && strcmp(location, root->rest->city) != 0)) {
        root->left = removeNodeLocation(root->left, name, location);
    //Traverse right subtree
    } else if (strcmp(name, root->rest->name) > 0 || (strcmp(name, root->rest->name) == 0 && strcmp(location, root->rest->city) != 0)) {
        root->right = removeNodeLocation(root->right, name, location);

    //Case where there is a match; removal happens
    } else {
        //Case with one or zero child nodes
        if (root->left == NULL) {
            BTNode* temp = root->right;
            //Destroy the node here >>>
            return temp;
        }
        else if (root->right == NULL) {
            BTNode* temp = root->left;
            //Destroy the node here >>>
            return temp;
        }

        //Node with two children
        //We have to get the minimum element on the right subtree
        BTNode* aboveSuccessor = root;
        BTNode* successor = root->right;
        BTNode* underSuccessor = successor-> left;
        while (underSuccessor != NULL) {
            aboveSuccessor = successor;
            successor = underSuccessor;
            underSuccessor = underSuccessor->left;
        }

        //Now the correct values for aboveSuccessor, successor, and underSuccessor are present
        //We now remove successor (which by construction of our loop is a leaf) 
        aboveSuccessor->left = NULL;
        successor->right = root->right;
        root = successor;
        return root;
    }
    return root;
}

/**
 * Remove a restaurant node from the index location tree node (based on location)
 * @param root represents root of the current node we are exploring 
 * @param name name of the restaurant that we are looking for
 * @param location location of the restaurant that we are looking for
 */ 
void removeNodeByLocationBST(BinaryTree* locationIndex, char* name, char* location) {
    locationIndex->root = removeNodeLocation(locationIndex->root, name, location);
}
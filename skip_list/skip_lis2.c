#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Node structure for the skip list
typedef struct Node {
    int key;
    struct Node** forward;
} Node;

// Skip list structure
typedef struct SkipList {
    int maxLevels;
    int level;
    Node* header;
} SkipList;

// Function to create a new node with a given key and number of levels
Node* createNode(int key, int levels) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->forward = (Node**)malloc(sizeof(Node*) * levels);
    return newNode;
}

// Function to create a new skip list with a given maximum number of levels
SkipList* createSkipList(int maxLevels) {
    SkipList* skipList = (SkipList*)malloc(sizeof(SkipList));
    skipList->maxLevels = maxLevels;
    skipList->level = 0;

    // Create header node
    skipList->header = createNode(INT_MIN, maxLevels);

    // Initialize forward pointers of header to NULL
    for (int i = 0; i < maxLevels; i++) {
        skipList->header->forward[i] = NULL;
    }

    return skipList;
}

// Function to generate a random level for a new node
int randomLevel(int maxLevels) {
    int level = 1;
    while (rand() % 2 == 0 && level < maxLevels) {
        level++;
    }
    return level;
}

// Function to insert a key into the skip list
void insert(SkipList* skipList, int key) {
    Node* update[skipList->maxLevels];
    Node* current = skipList->header;

    for (int i = skipList->level - 1; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    int newLevel = randomLevel(skipList->maxLevels);

    if (newLevel > skipList->level) {
        for (int i = skipList->level; i < newLevel; i++) {
            update[i] = skipList->header;
        }
        skipList->level = newLevel;
    }

    Node* newNode = createNode(key, newLevel);

    for (int i = 0; i < newLevel; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
}

// Function to search for a key in the skip list
Node* search(SkipList* skipList, int key) {
    Node* current = skipList->header;

    for (int i = skipList->level - 1; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->key < key) {
            current = current->forward[i];
        }
    }

    if (current->forward[0] != NULL && current->forward[0]->key == key) {
        return current->forward[0];
    } else {
        return NULL;
    }
}

// Function to delete a key from the skip list
void deleteKey(SkipList* skipList, int key) {
    Node* update[skipList->maxLevels];
    Node* current = skipList->header;

    for (int i = skipList->level - 1; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    // Check if the key to be deleted is present in the skip list
    if (current->forward[0] != NULL && current->forward[0]->key == key) {
        // Iterate through each level
        for (int i = 0; i < skipList->level; i++) {
            // If the forward node at the current level has the key to be deleted, update pointers
            if (update[i]->forward[i] != NULL && update[i]->forward[i]->key == key) {
                Node* temp = update[i]->forward[i];
                update[i]->forward[i] = temp->forward[i];
                free(temp->forward);
                free(temp);
            }
        }

        // Update the level of the skip list if necessary
        while (skipList->level > 1 && skipList->header->forward[skipList->level - 1] == NULL) {
            skipList->level--;
        }
    }
}

// Function to print the elements of the skip list
void printSkipList(SkipList* skipList) {
    printf("Skip List:\n");

    for (int i = skipList->level - 1; i >= 0; i--) {
        Node* current = skipList->header->forward[i];
        printf("Level %d: ", i + 1);

        while (current != NULL) {
            if (current->key != INT_MIN) {
                printf("%d ", current->key);
            }
            current = current->forward[i];
        }

        printf("\n");
    }
}


// Function to free the memory allocated for the skip list
void freeSkipList(SkipList* skipList) {
    Node* current = skipList->header->forward[0];
    Node* temp;

    while (current != NULL) {
        temp = current;
        current = current->forward[0];
        free(temp->forward);
        free(temp);
    }

    free(skipList->header->forward);
    free(skipList->header);
    free(skipList);
}

int main() {
    // Set the maximum number of levels for the skip list
    int maxLevels = 4;

    // Create a skip list
    SkipList* skipList = createSkipList(maxLevels);

    // Insert some keys into the skip list
    insert(skipList, 3);
    insert(skipList, 6);
    insert(skipList, 7);
    insert(skipList, 9);
    insert(skipList, 12);

    // Print the skip list
    printSkipList(skipList);

    // Delete a key from the skip list
    int keyToDelete = 7;
    deleteKey(skipList, keyToDelete);

    // Print the skip list after deletion
    printf("\nAfter deleting %d:\n", keyToDelete);
    printSkipList(skipList);

    // Free the memory allocated for the skip list
    freeSkipList(skipList);

    return 0;
}

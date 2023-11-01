#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 

// Linked List node
struct node {
 
    // this will be the key to our hash function
    char* key;
 
    // the value that the key will map
    char* value;
    struct node* next; //pointer to the next node
};

// it is the constructor for struct node. 
//it takes a pointer to struct node, it asigns value to what struct node requires
//asterisk because we pass the a pointer to a single value
//struct node* type indicates that node is a pointer to a single struct node. 
//The char* types for key and value indicate that these are pointers to strings.
void setNode(struct node* node, char* key, char* value)
{
    //it utilizes the arrow to indicate that we are accessing the members of the struct node pointed to by the node pointer.
    node->key = key; // it is setting the key member of the struct node pointed to by node to the value of the key
    node->value = value;
    node->next = NULL; //sets the next member to NULL.
    return;
};

struct hashMap {
 
    // Current number of elements in hashMap
    // and capacity of hashMap
    int numOfElements, capacity;
 
    // hold base address array of linked list
    // array of pointers to struct node to implement chaining mechanism:
    struct node** arr;
};
 
// constructor of struct hashMap
void initializeHashMap(struct hashMap* mp)
{
 
    // Default capacity in this case
    mp->capacity = 100;
    mp->numOfElements = 0;
 
    // it allocates an array of pointers to struct node with the size of capacity multiplied bt wgat stryct node needs
    mp->arr = (struct node**)malloc(sizeof(struct node*)
                                    * mp->capacity);
    return;
}

int hashFunction(struct hashMap* mp, char* key)
{
    int bucketIndex;
    int sum = 0, factor = 31;
    for (int i = 0; i < strlen(key); i++) {
 
        // sum = sum + (ascii value of
        // char * (primeNumber ^ x))...
        // where x = 1, 2, 3....n
        sum = ((sum % mp->capacity)
               + (((int)key[i]) * factor) % mp->capacity)
              % mp->capacity;
 
        // factor = factor * prime
        // number....(prime
        // number) ^ x
        factor = ((factor % __INT16_MAX__)
                  * (31 % __INT16_MAX__))
                 % __INT16_MAX__;
    }
 
    bucketIndex = sum;
    return bucketIndex;
}




void insert(struct hashMap* mp, char* key, char* value)
{
 
    // Getting bucket index for the given
    // key - value pair

    int bucketIndex = hashFunction(mp, key);
    
    //we need memory to allocate a new struct node called newNode
    struct node* newNode = (struct node*)malloc(
 
        // Creating a new node
        sizeof(struct node));

    // Setting value of node
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

 
    // Bucket index is empty....no collision
    //then directly we asigh newNode to arr[bucketIndex]
    //y setting the next of the newNode to the current head (the original node)
    //then updating mp->arr[bucketIndex] to point to the newNode. 
    //This way, the newNode becomes the new head of the linked list.
    if (mp->arr[bucketIndex] == NULL) {
        mp->arr[bucketIndex] = newNode;
    }
 
    // Collision
    else {
 
        // Adding newNode at the head of
        // linked list which is present
        // at bucket index....insertion at
        // head in linked list
        newNode->next = mp->arr[bucketIndex];
        mp->arr[bucketIndex] = newNode;
    }
    return;
}


char* search(struct hashMap* mp, char* key)
{
 
    // Getting the bucket index
    // for the given key
    int bucketIndex = hashFunction(mp, key);
 
    // Head of the linked list
    // present at bucket index
    struct node* bucketHead = mp->arr[bucketIndex];
    while (bucketHead != NULL) {
 
        // Key is found in the hashMap
        if (strcmp(bucketHead->key, key) == 0) {
            return bucketHead->value;
        }
        bucketHead = bucketHead->next;
    }
 
    // If no key found in the hashMap
    // equal to the given key
    char* errorMssg = (char*)malloc(sizeof(char) * 25); 
    errorMssg = "No data found.\n";
    return errorMssg;
}


int main()
{
 
    // Initialize the value of mp
    struct hashMap* mp
        = (struct hashMap*)malloc(sizeof(struct hashMap));
    initializeHashMap(mp);
 
    insert(mp, "Name", "Sandra");
    insert(mp, "day", "Monday");
    insert(mp, "fruit", "Apple");
    insert(mp, "book", "Harry_Potter");
    insert(mp, "car", "Toyota");
 
    printf("%s\n", search(mp, "Name"));
    printf("%s\n", search(mp, "day"));
    printf("%s\n", search(mp, "fruit"));
    printf("%s\n", search(mp, "book"));
    printf("%s\n", search(mp, "car"));
 
    // Key is not inserted
    printf("%s\n", search(mp, "randomKey"));
 
    return 0;
}
/**
 * Singly linked list library
 * @file sllist.c
 * @author Jeremy Le
 * @date 27th April 2023
*/

/**
 * A struct representing a node in a linked list.
*/
typedef struct node {
    int data;   /**< integer data stored in the node */
    struct node* next;  /**< A pointer to the next node in the list*/
} node_t;

/**
 * Creates a linked list based on input values
 * @param order A character denoting the order of list construction: 'r' for reverse
 * @param size An int representing size of linked list to be created. If 0, creates an empty list.
 * @param ... A variable-length list of ints to be added to the linked list
 * @return Returns a pointer to the head of created list or NULL if error
*/
node_t* createSLL(char order, int size, ...);

/** 
 * @brief Create a linked list using an array as input.
 * @param arr An integer array containing the data to be added to the linked list
 * @param size An integer represneting the size of the array and linked list to be created
 * @return Returns a pointer to the head of created linked list or NULL if error
 */
node_t* createfromArray(int arr[], int size);

/**
 * @brief Adds a node to the head of a linked list.
 * The funtion adds a new node with specified data to the beginning of the linked list.
 * @param head A pointer to the head of the linked list. Passed by reference (e.g. &list).
 * @param data An integer data to be stored in the new node.
 * @return Returns 0 upon successful completion. 1 upon memory allocation failure.
*/
int push(node_t** head, int data);

/**
 * @brief Add node to tail of linked list.
 * The function adds a new node with specified data to the end of linked list.
 * @param head A pointer to the head of the linked list. Passed by reference (e.g. &list).
 * @param data An integert data to be stored in the new node.
 * @return Returns 0 upon successful completion, 1 upon memory allocation failure.
*/ 
int enqueue(node_t** head, int data);

/**
 * @brief Removes a node from the head of a linked list.
 * Removes the first node of the linked list and free its memory, then sets the new node as the head of linked list.
 * @param head A pointer to the head of the linked list. Passed by reference (e.g. &list).
 * @return 0 upon successful completion, 1 otherwise
 */
int pop(node_t** head);

/**
 * @brief Removes a node from tail of linked list.
 * Removes the last node of the linked list and free its memory, then sets the previous node as the last node.
 * @param head A pointer to the head of the linked list. Passed by reference (e.g. &list).
 * @return 0 upon successful completion, 1 otherwise
 */
int removeTail(node_t** head);

/**
 * @brief Destroy a linked list by deallocating memory for all nodes.
 * @param head A pointer to the head of the linked list. Passed by reference (e.g. &list).
 * @return Returns nothing.
*/
void destroy(node_t** head);

/**
 * @brief Deletes all nodes with a matching value in a linked list.
 * @param head A pointer to the head of the linked list. Passed by reference (e.g. &list).
 * @param value The value to be deleted from the linked list.
 * @return Returns nothing.
*/
void deleteMatch(node_t** head, int value);

/**
 * @brief Reverses the order of a linked list
 * This function takes a pointer to the head node of a linked list and reverses the order
 * of the nodes in the list. If the list is empty or has only one node, the function does nothing
 * and returns immediately. The function works by iterating through the list and reversing
 * the 'next' pointers of each node to point to the previous node. At the end of the iteration,
 * the head pointer is updated to point to the new start of the reversed list. 
 * @param head A pointer to the head of the linked list. Passed by reference (e.g. &list).
 * @return Returns nothing.
*/
void reverseList(node_t** head);

/**
 * @brief Deletes all nodes that are duplicated in a linked list.
 * @param head A pointer to the head of the linked list. Passed by reference (e.g. &list).
 * @return Returns nothing.
*/
void deleteDuplicates(node_t** head);

/**
 * @brief Sorts a linked list in ascending order using merge sort algorithm
 * @param head A pointer to the head of the linked list. Passed by reference (e.g. &list).
 * @return Returns nothing.
*/
void mergeSort(node_t** head);

/**
 * @brief A helper function that merges two sorted linked lists into a single sorted linked list.
 * @param head A pointer to the head of the linked list. Passed by reference (e.g. &list).
 * @param left A pointer to the head of the first sorted linked list to be merged.
 * @param right A pointer to the head of the second rst sorted linked list to be merged.
 * @return Returns nothing.
*/
void merge(node_t** head, node_t* left, node_t* right);

/**
 * @brief A help function that splits a linked list into two sub-list halves.
 * @param head A pointer to the head node of the linked list to be split.
 * @param left A pointer to a pointer to the head node of the left sub-list.
 * @param right A pointer to a pointer to the head node of the right sub-list.
 * @return Returns nothing.
*/
void splitList(node_t* head, node_t** left, node_t** right);

/**
 * @brief Prints all elements of a linked list.
 * If the linked list is empty, it prints "Empty list". Otherwise, it prints each
 * element in the list separated by a hyphen, in order from head to tail.
 * The function does not modify the list.
 * @param head A pointer to the head node of the linked list.
 */
void printList(node_t* head);

/**
 * @brief Counts the number of occurences of a given value in the linked list.
 * @param head A pointer to the head node of the linked list.
 * @param value The value to search for in the linked list. 
 * @return Number of occuerenced of the value in the linked list, or -1 if the list is empty.
 */
int count(node_t* head, int value);

/**
 * @brief Counts the number of elements in the linked list.
 * @param head A pointer to the head node of the linked list.
 * @return An integer representing the number of elements in the linked list.
 */
int length(node_t* head);

/**
 * @brief Saves the content of a singly linked list to a file.
 * The function traverses the singly linked list and writes each element's data
 * to the specified file, one element per line. If the list is empty or the
 * file cannot be opened for writing, an error message is printed to stderr.
 * @param head The head pointer of the singly linked list.
 * @param filename The name of the file to save the content to.
 */
void savetoFile(node_t* head, char* filename);

/**
 * @brief Creates a singly linked list from the content of a file.
 * The function reads the content of the specified file, line by line, and
 * constructs a singly linked list containing the read data. Non-valid values
 * in the file are skipped. The created list is returned, or NULL if the file
 * cannot be opened for reading.
 * @param input The name of the file to read the content from.
 * @return A pointer to the head of the created singly linked list, or NULL if the file cannot be opened for reading.
 */
node_t* createfromFile(char* input);

/**
 * @brief Recursively counts the number of occurrences of a specific value in a linked list.
 * @param head Pointer to the head of the linked list.
 * @param value The value to count.
 * @return int The number of occurrences of the value in the linked list.
*/
int recursive_count(node_t* head, int value);

/**
 * @brief Recursively calculates the length of a linked list.
 * @param head pointer to the head of the linked list
 * @return the length of the linked list
 */
int recursive_length(node_t* head);

/**
 * @brief Recursively prints the entire linked list.
 * @param head pointer to the head of the linked list
 */
void recursive_print(node_t* head);

/**
 * @brief Recursively destroys the linked list, freeing all memory allocated for nodes.
 * @param head pointer to the head of the linked list
 */
void recursive_destroy(node_t* head);

/**
 * @brief Count the number of occurences of a given value in a linked list iteratively.
 * @param head A pointer to the head of the linked list.
 * @return The number of nodes in the linked list.
 */
int count_old(node_t** head, int value);

/**
 * @brief Count the number of nodes in a linked list iteratively.
 * @param head A pointer to the head of the linked list.
 * @return The number of nodes in the linked list.
 */
int length_old(node_t** head);

/**
 * @brief Fill an array of integers with unique numbers ranging from 0 to size - 1.
 * @param arr The array to be filled with unique numbers.
 * @param size The size of the array.
 */
void randomUnique(int arr[], int size);

/**
 * @brief Fill an array of integers with random numbers ranging from min to max.
 * @param arr The array to be filled with random numbers.
 * @param size The size of the array.
 * @param min The minimum value of the random numbers.
 * @param max The maximum value of the random numbers.
 */
void randomArray(int arr[], int size, int min, int max);

/**
 * @brief Shuffle the elements of an integer array.
 * @param arr The array to be shuffled.
 * @param size The size of the array.
 */
void shuffle(int arr[], int size);
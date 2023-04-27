/**
 * Singly linked list library
 * @file sllist.c
 * @author Jeremy Le
 * @date 27th April 2023
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "sllist.h"

// Creates a linked list based on input values.
node_t* createSLL(char order, int size, ...) {
    // Create empty list
    if (size <= 0) {
        return NULL;
    }

    va_list args;
    va_start(args, size);
    node_t* head = NULL;                 // Initialise empty list

    if (order == 'r') {
        for (int i = 0; i < size; i++) {
            int data = va_arg(args, int);
            if (push(&head, data) != 0) {
                fprintf(stderr, "Error: failed to create list\n");
                destroy(&head);
                va_end(args);
                return NULL;
            }
        }
    }
    else {
        // To create linked list in same order as input, an array is created.
        int arr[size];
        for (int i = 0; i < size; i++) {
            int data = va_arg(args, int);
            arr[i] = data;
        }
        head = createfromArray(arr, size);
    }

    va_end(args);
    return head;
}

// Create a linked list using an array as input.
node_t* createfromArray(int arr[], int size) {
    node_t* head = NULL;
    for (int i = size - 1; i >= 0; i--) {
        if (push(&head, arr[i])) {
            fprintf(stderr, "Error: failed to create list\n");
            destroy(&head);
            return NULL;
        }
    }

    return head;
}

// Adds a node to the head of a linked list.
int push(node_t** head, int data) {
    // Initialise and allocate memory for new node.
    node_t* new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed in push\n");
        return 1;
    }                                           // When a node is pushed to the head of
                                                // a linked list, the original head ptr
    new_node->data = data;                      // must be updated to point to new head.
    // Set head to new_node in an empty list    // Therefore, the head pointer must be
    if (*head == NULL) {                        // passed BY REFERENCE, so it can be updated
        *head = new_node;                       // within the function's scope.
        new_node->next = NULL;                  // This is achieved by using a double ptr
    }                                           // The function parameter will be the
    // Push new_node to current head.           // address of a ptr, &(node_t* head).
    else {
        new_node->next = *head;
        *head = new_node;  // Update head
    }
    return 0;
}

// Add node to tail of linked list.
int enqueue(node_t** head, int data) {
    // Add node directly to empty list pointer
    if (*head == NULL) {
        push(head, data);   // This is essentially push to empty list.
        return 0;
    }
    // Create new_node
    node_t* new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory in enqueue.\n");
        return 1;
    }
    // Traverse list and point to tail.
    new_node->data = data;
    node_t* ptr = *head;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }
    // Insert new_node to tail.
    ptr->next = new_node;
    new_node->next = NULL;

    return 0;
}

// Removes a node from the head of a linked list.
int pop(node_t** head) {
    if (*head == NULL) {
        fprintf(stderr, "Error: Cannot pop empty list.\n");
        return 1;
    }

    node_t* delete = *head;
    *head = (*head)->next;
    free(delete);

    return 0;
}

// Removes a node from tail of linked list.
int removeTail(node_t** head) {
    if (*head == NULL) {    // Empty list
        fprintf(stderr, "Error: Cannot remove element from empty list.\n");
        return 1;
    }

    node_t* ptr = *head;
    if (ptr->next == NULL) {        //  Remove node from list of one node.
        free(ptr);                  // Due to this case, it is better to pass head ptr
        *head = NULL;               // by reference so we can update it to NULL.
    }
    // Remove node from tail of linked list greater than 1.
    else {              // List greater than one
        while (ptr->next->next != NULL) {   //Traverse to the second last node of list.
            ptr = ptr->next;
        }
        free(ptr->next->next);  // Free last element
        ptr->next = NULL;
    }
    return 0;
}

// Deletes all nodes with a matching value in a linked list.
void deleteMatch(node_t** head, int value) {
    if (*head == NULL) {
        fprintf(stderr, "Error: can't delete from empty list.\n");
    }

    node_t* ptr = *head;
    node_t* delete;
    // delete from head
    while (ptr->data == value) {
        delete = ptr;                   // Delete points to prev element
        ptr = ptr->next;
        free(delete);
    // If linked list is of the same elements.
        if (ptr == NULL) {
            *head = NULL;
            return;
        }
    }
    *head = ptr;

    while (ptr->next != NULL) {
        if (ptr->next->data == value) {
            delete = ptr->next;           // Delete points to next element
            ptr->next = ptr->next->next;  // Maintain link to tail end of nodes
            free(delete);                 // If tail nodes deleted, ptr -> NULL
        }
        else ptr = ptr->next;             // Only advance when next node isn't a match
    }
}

// Deletes all nodes that are duplicated in a linked list.
void deleteDuplicates(node_t** head) {
    // Do nothing if list is empty or only has one node
    if(!head || !(*head)->next) return;

    node_t* outer, *inner, *dupe;
    outer = *head;

    while (outer != NULL && outer->next != NULL) {
        inner = outer;

        while (inner->next != NULL) {
            if (outer->data == inner->next->data) {
                dupe = inner->next;
                inner->next = inner->next->next;
                free(dupe);
            }
            else {
                inner = inner->next;
            }
        }
        outer = outer->next;
    }
}

// Reverses the order of a linked list.
void reverseList(node_t** head) {
    if (!*head || !(*head)->next) return; // If the list is empty or has only one node, do nothing and return

    node_t* ptr = *head;       // Pointer 'ptr' points to the current node
    node_t* prv = NULL;        // Pointer 'prv' points to the previous node

    while (ptr) {              // Iterate through the list until the end is reached
        *head = ptr->next;     // Move 'head' to the next node
        ptr->next = prv;       // Reverse the current node's 'next' pointer
        prv = ptr;             // Move 'prv' to the current node
        ptr = *head;           // Update 'ptr' to the next node
    }
    *head = prv;               // Update 'head' to the new start of the reversed list
}

// Destroy a linked list, deallocating memory for all nodes.
void destroy(node_t** head) {
    // Empty list
    if (*head == NULL) {
        fprintf(stderr, "Error: Cannot destroy empty list.\n");
        return;
    }
    while (*head != NULL) {
        node_t* delete = *head;
        *head = (*head)->next;   // Move head pointer to next node
        free(delete);            // Free the memory of deleted node
    }
    *head = NULL;                // Must pass original head ptr by reference to update
}                                // it to NULL after deleting all nodes.

// Sorts linked list in ascending order using merge sort algorithm
void mergeSort(node_t** head) {
    // Base case when list is empty or only one element
    if (!*head || !(*head)->next) return;

    // Split list into sub-list halves
    node_t* left = *head;
    node_t* right = *head;
    splitList(*head, &left, &right);

    //Recursively sort sublists
    mergeSort(&left);
    mergeSort(&right);

    // Merge sorted sublists
    merge(head, left, right);

    return;
}

// Merges two sorted linked lists.
void merge(node_t** head, node_t* left, node_t* right) {
    // If one of the subarrays is empty, return the non-empty one
    if (!left) {
        *head = right;
        return;
    }
    if (!right) {
        *head = left;
        return;
    }
    // Initialize the head of the merged list with the smallest element
    if (left->data <= right->data) {
        *head = left;
        left = left->next;
    }
    else {
        *head = right;
        right = right->next;
    }
    // Traverse both subarrays and merge them in sorted order
    node_t* tail = *head;
    while (left && right) {
        if (left->data <= right->data) {
            tail->next = left;
            left = left->next;
        }
        else {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }
    // Attach the remaining nodes from the non-empty subarray
    tail->next = left ? left : right;
}

// Splits a linked list into two sub-list halves.
void splitList(node_t* head, node_t** left, node_t** right) {
    // Return if list is empty or has only one element.
    if (!head || !head->next) return;

    // Traverse list with hare moving twice as fast as tortoise (Floyd algorithm)
    node_t* hare = head->next;
    node_t* tortoise = head;
    while (hare) {
        hare = hare->next;
        if (hare) {
            hare = hare->next;
            tortoise = tortoise->next;
        }
    }
    // Split list when hare reaches end (tortoise at middle)
    *left = head;
    *right = tortoise->next;
    tortoise->next = NULL;

    return;
}

// Prints all elements of a linked list.
 void printList(node_t* head) {
    if (head == NULL) {
        printf("Empty list");
        return;
    }
                                        // while (head->next != NULL) sets head to tail
    while (head != NULL) {              // while (head != NULL) traverses all nodes
        printf("-%d", head->data);
        head = head->next;
    }
    printf("\n");
}

//Counts number of elements in the linked list.
int length(node_t* head) {
    if (head == NULL) {         // Passes head pointer BY VALUE, creates a local copy
        return 0;               // This local head pointer can iterate through each
    }                           // node in the original linked list (not copied).
                                // It basically acts as it's own temporary pointer,
    int i = 0;                  // abolishing the need to create a new pointer.
    while (head != NULL) {
        head = head->next;      // node_t* ptr = head; to make this clear ?
        i++;
    }
    return i;
}

// Counts numbers of occurences of a given value in linked list.
int count(node_t* head, int value) {
    if (head == NULL) {
        fprintf(stderr, "Cannot use count function in empty list\n");
        return -1;
    }

    int i = 0;
    while (head != NULL) {   // Iterate through every node in list.
        if (head->data == value) {
            i++;
        }
        head = head->next;
    }
    return i;
}

// Saves content of a linked list to a file.
void savetoFile(node_t* head, char *filename) {
    if(head == NULL) {
        fprintf(stderr, "Error: Empty list, could not save to output.\n");
        return;
    }

    FILE* output = fopen(filename, "w");
    if (output == NULL) {
        fprintf(stderr, "Error: Unable to open file for writing.\n");
        return;
    }

    while (head != NULL) {
        fprintf(output, "%d\n", head->data);
        head = head->next;
    }

    fclose(output);
}

// Creates a singly linked list from the content of a file.
node_t* createfromFile(char* input) {
    FILE* file = fopen(input, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file.\n");
        return NULL;
    }

    int temp;
    int size = 0;
    int scan_return;
    // Find the size of list; handles non-valid values and skips them.
    while ((scan_return = fscanf(file, "%d", &temp)) != EOF) {
        if (scan_return != 1) continue;
        else size++;
    }
    // Reset file ptr, create array of size
    rewind(file);
    int* arr = malloc(sizeof(int) * size);
    int i = 0;
    // Read each line into array
    while ((scan_return = fscanf(file, "%d", &arr[i])) != EOF) {
        if (scan_return != 1) continue;
        else i++;
    }
    // Process array into linked list.
    node_t* head = createfromArray(arr, size);
    // Clean up
    free(arr);
    fclose(file);
    return head;
}

// Recursively counts the number of occurrences of a specific value in a linked list.
int recursive_count(node_t* head, int value) {
    if (head == NULL) return 0;
    else if (head->data == value)
        return 1 + recursive_count(head->next, value);
    else return recursive_count(head->next, value);
}

// Recursively calculates the length of a linked list.
int recursive_length(node_t* head) {
    if (head == NULL) return 0;
    else return 1 + recursive_length(head->next); //
}

// Print entire linked list using recursion.
void recursive_print(node_t* head) {
    if (head == NULL) {
        printf("\n");
    }
    else {
        printf("-%d", head->data);
        recursive_print(head->next);
    }
}

// Recursively destroys the linked list, freeing all memory allocated for nodes.
void recursive_destroy(node_t* head) {
    if (head == NULL) return;
    else {
        node_t* delete = head;
        recursive_destroy(head->next);
        free(delete);
    }
}

// Count the number of a given value in list (mode), iteratively.
int count_old(node_t** head, int value) {
    if (*head == NULL) {
        fprintf(stderr, "Cannot use count function in empty list\n");
        return -1;
    }

    node_t* ptr = *head;
    int i = 0;
    while (ptr != NULL) {   // Iterate through every node in list.
        if (ptr->data == value) {
            i++;
        }
        ptr = ptr->next;
    }
    return i;
}

// Count number of nodes in linked list, iteratively.
int length_old(node_t** head) {
    if (*head == NULL) {        // In this implementation, the double ptr passes the
        return 0;               // original head ptr BY REFERENCE because it is a ptr to
    }                           // another ptr.
                                // This means that *head IS the original ptr and any
    node_t* ptr = *head;          // changes will be reflected in main.
    int i = 0;                  // To circumvent this, a new temp ptr must be created
    while (ptr != NULL) {       // locally and pointed to *head.
        ptr = ptr->next;
        i++;
    }
    return i;
}

// Fill an array of integers with unique numbers ranging from 0 to size - 1.
void randomUnique(int arr[], int size) {

    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    shuffle(arr, size);
}

// Fill an array of integers with random numbers ranging from min to max.
void randomArray(int arr[], int size, int min, int max) {
    for (int i = 0; i < size; i++) {
        // (max - min + 1) is inclusive range. + min shifts number.
        arr[i] = rand() % (max - min + 1) + min;
    }
    shuffle(arr, size);
}

// Shuffle the elements of an integer array.
void shuffle(int arr[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
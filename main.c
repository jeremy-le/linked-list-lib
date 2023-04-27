#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sllist.h"


int main(int argc, char* argv[]) {

    srand(time(NULL));

    node_t* list = NULL;

    // if (argc == 2) {
    // }
    char* filename = argv[1];

    int size = 100;
    int arr[size];
    randomUnique(arr, size);

    list = createfromArray(arr, size);
    //printList(list);

    mergeSort(&list);

    //reverseList(&list);
    //deleteMatch(&list, 50);
    printList(list);
    //printf("Mode: %d\n", count(list, 1));

    //deleteDuplicates(&list);
    //printf("Mode: %d\n", count(list, 1));
    //printList(list);
    savetoFile(list, filename);

    recursive_destroy(list);
}
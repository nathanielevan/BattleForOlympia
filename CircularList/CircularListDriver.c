#include "CircularList.h"
#include <stdlib.h>
#include <stdio.h>

lcType CircListType;
lcElmtList CircListElmt;
lcList CircList;
lcaddress CircListAdd, DelFirstAdd, DelLastAdd;

int main()
{
    printf("Welcome to CircularList!\n");
    printf("Let us initialise the list first before we proceed...\n");
    lcCreateEmpty(&CircList);
    if (lcIsEmpty(CircList)) {
        printf("The list is now initialised and empty.");   
    }
    printf("Please input a number: ");
    scanf("%d\n",&CircListType);
    printf("This number will be inserted as the first element in the list.\n");
    lcInsVFirst(&CircList,CircListType);
    printf("The next number will be inserted as the last element in the list.\n");
    printf("Please input a number: ");
    scanf("%d\n",&CircListType);
    lcInsVLast(&CircList,CircListType);
    printf("2 more numbers to go. Input a number to be inserted as the first element in the list: ");
    scanf("%d\n",&CircListType);
    lcInsVFirst(&CircList,CircListType);
    printf("Last one! Input a number. We'll put it at the back of the list: ");
    scanf("%d\n",&CircListType);
    lcInsVLast(&CircList,CircListType);
    printf("Input a number, we'll search for the number in the list for you: ");
    scanf("%d\n",&CircListType);
    CircListAdd = lcSearch(CircList,CircListType);
    if (CircListAdd != NULL) {
        printf("The number has been found at address %p\n", CircListAdd);
        printf("We'll delete it for you as well.\n");
        lcDelP(&CircList,CircListType);
    }
    else {
        printf("Sorry, the number is not found.\n");
    }
    printf("From this point on the program will be automated.\n");
    printf("We'll delete the first and last element for you.\n");
    lcDelFirst(&CircList, &DelFirstAdd);
    printf("The first address was at memory address %p, now it's deleted.\n", DelFirstAdd);
    lcDelLast(&CircList, &DelLastAdd);
    printf("The last address was at memory address %p, now it's deleted.\n", DelLastAdd);
    printf("Here are the remaining elements:\n");
    lcPrintInfo(CircList);

    return 0;
}
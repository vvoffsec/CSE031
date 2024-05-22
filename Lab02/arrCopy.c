#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int size; // Variable to record size of original array arr
int evenCount = 0, oddCount = 0; // Variables to record sizes of new arrays evenArray and oddArray
int *arr; // Dynamically allocated original array with #elements = size
int *evenArray;  // Dynamically allocated array with #elements = #even elements in arr (evenCount)
int *oddArray;   // Dynamically allocated array with #elements = #odd elements in arr (oddCount)
char *str1 = "Original array's contents: ";
char *str2 = "Contents of new array containing even elements from original: ";
char *str3 = "Contents of new array containing odd elements from original: ";


void printArr(int *a, int size, char *prompt){
	printf("\n");
    printf("%s", prompt);
    if (size == 0) 
    {
        printf("empty");
    }
    for (int i = 0; i < size; i++) 
    {
        printf("%d", *(a + i));
        printf(" ");
    }
}

void arrCopy(){
    int *intPointer = arr;

    for (int i = 0; i < size; i++) 
    {
        if (*intPointer % 2 == 0) 
        {
            evenCount++;
        }
        else 
        {
            oddCount++;
        }
        intPointer++;
    }

    evenArray = (int*)malloc(evenCount * sizeof(int));
    oddArray = (int*)malloc(oddCount * sizeof(int));

    int evenInt = 0;
    int oddInt = 0;

    intPointer = arr;
    for (int i = 0; i < size; i++) 
    {
        if (*intPointer % 2 == 0) 
        {
            *(evenArray + evenInt) = *intPointer;
            evenInt++;
        } 
        else 
        {
            *(oddArray + oddInt) = *intPointer;
            oddInt++;
        }
        intPointer++;
    }

}

int main(){
    int i;
    printf("Enter the size of array you wish to create: ");
    scanf("%d", &size);

    arr = (int*)malloc(size * sizeof(int));
    int countInt = 1;
    int *intPointer = arr;
    for (int j = 0; j < size; j++) {
        printf("Enter array element #%d: ", countInt);
        scanf("%d", intPointer);
        countInt++;
        intPointer++;
    }

	
/*************** YOU MUST NOT MAKE CHANGES BEYOND THIS LINE! ***********/
	
	// Print original array
    printArr(arr, size, str1);

	/// Copy even elements of arr into evenArray and odd elements into oddArray
    arrCopy();

    // Print new array containing even elements from arr
    printArr(evenArray, evenCount, str2);

    // Print new array containing odd elements from arr
    printArr(oddArray, oddCount, str3);

    printf("\n");

    return 0;
}
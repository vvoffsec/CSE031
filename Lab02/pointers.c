#include <stdio.h>

int main()
{
    int x , y, *px, *py;
    x = 1;
    y = 2;
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};


    px = &x;
    py = &y;

    printf("Memory of x: %p\n", &x);
    printf("Memory of y: %p\n", &y);


    printf("Memory of x through pointer: %p\n", px);
    printf("Memory of y through pointer: %p\n", py);

    printf("Value of x through pointer: %d\n", *px);
    printf("Value of y through pointer: %d\n", *py);

    for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
    {
        printf("Array value at index %d: ", i);
        printf("%d\n", *(arr+i));
    }

    printf("Value of first element of array through pointer: %d\n", *arr);

    printf("Memory of arr[0]: %p\n", &arr[0]);
    printf("Memory of arr: %p\n", &arr);

    return 0;
}

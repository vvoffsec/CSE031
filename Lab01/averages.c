#include <stdio.h>
#include <stdlib.h>

void numberSuffix(int count)
{
    if (count % 10 == 1 && count != 11)
    {
        printf("Enter the %dst value: ", count);
    }
    else if (count % 10 == 2 && count != 12)
    {
        printf("Enter the %dnd value: ", count);
    }
    else if (count % 10 == 3 && count != 13)
    {
        printf("Enter the %drd value: ", count);
    }
    else
    {
        printf("Enter the %dth value: ", count);
    }
}

int main()
{
    int userNum = -19375027;
    int numOfValueEven = 0;
    int numOfValueOdd = 0;
    int TotalValueEven = 0;
    int TotalValueOdd = 0;
    int sumOfCurrent = 0;
    int count = 1;
    
    while(userNum != 0)
    {
        sumOfCurrent = 0;
        numberSuffix(count);
        scanf("%d", &userNum);
        count++;
        int currentNum = abs(userNum);
        while (currentNum != 0)
        {
            sumOfCurrent += currentNum % 10;
            currentNum /= 10;
        }

        if (sumOfCurrent % 2 == 0 && sumOfCurrent != 0)
        {
            TotalValueEven += userNum;
            numOfValueEven++;
        }
        if (sumOfCurrent % 2 == 1 && sumOfCurrent != 0)
        {
            TotalValueOdd += userNum;
            numOfValueOdd++;
        }
    }

    double EvenAvg = (double)TotalValueEven/(double)numOfValueEven;
    double OddAvg = (double)TotalValueOdd/(double)numOfValueOdd;


    if (numOfValueEven == 0 && numOfValueOdd == 0)
    {
        printf("\n");
        printf("There is no average to compute.");
    }
    if (numOfValueEven > 0)
    {
        printf("\n");
        printf("Average of input values whose digits sum up to an even number: %0.2f", EvenAvg);
    }
    
    if (numOfValueOdd > 0)
    {
        printf("\n");
        printf("Average of input values whose digits sum up to an odd number: %0.2f", OddAvg);
    }
    return 0;
}
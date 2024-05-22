#include <stdio.h>
int main()
{
    printf("Enter the repetition count for the punishment phrase: ");
    int count = 0;
    scanf("%d", &count);

    while (count < 1)
    {
        printf("You enetered an invalid value for the reptition count! Please re-enter: ");
        scanf("%d", &count);
    }
    printf("\n");
    
    printf("Enter the line where you want to insert the typo: ");
    int typoLine = 0;
    scanf("%d", &typoLine);

    while(typoLine < 1 || typoLine > count)
    {
        printf("You enetered an invalid value for the typo placement! Please re-enter: ");
        scanf("%d", &typoLine);
    }
    printf("\n");
    
    for (int i = 0; i < count; i++)
    {
        if(i != typoLine-1)
        {
            printf("Coding with C is awesome!\n");
        }
        else
        {
            printf("Cading wiht is C avesone!\n");
        }

    }
    return 0;
}
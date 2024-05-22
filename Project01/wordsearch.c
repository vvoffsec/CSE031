#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
void UpcaseWord(char* word);
void buildEmptyPath();
void firstLetter(char** arr, char* word, int x, int y);
void addLetterPath(int x, int y);
void resetPath();
void printPath();
void checkClockwise(char** arr, char* word, int x, int y);
void checkCounterClockwise(char** arr, char* word, int x, int y);
int bSize;
int** path;
int x = -1;
int y = -1;
int ix = 0;
int iy = 0;
int found = 0;
int counter = 0;

// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

void printPuzzle(char** arr) {
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...
    for (int i = 0; i < bSize; i++)
    {
		for (int j = 0; j < bSize; j++)
        {
			printf("%c ", *(*(arr + i) + j));
		}
		printf("\n");
	}
    printf("\n");

}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...
    UpcaseWord(word);

    buildEmptyPath(); // sets search path to zeros
    
    firstLetter(arr, word, x, y);
    
    if (found == 0){
        printf("Word not found!\n");
    }else {
        printf("Word found!\n");
        printPath();
    }

}

void UpcaseWord(char* word)
{
    for (int i = 0; *(word+i)!='\0'; i++)
    { 
        if(*(word+i) >= 'a' && *(word+i) <= 'z')
        {
            *(word+i) = *(word+i) -32;
        }
    }
}

void firstLetter(char** arr, char* word, int x, int y)
{
    if(x == -1 && y == -1)
    {
        for (int i = 0; i < bSize; i++)
        {
            for (int j = 0; j < bSize; j++)
            {
                if (*(word) == *(*(arr + i) + j))
                {
                    ix = j;
                    iy = i;
                    x = j;
                    y = i;
                    found++;
                    break;
                    
                }
                if(j == bSize - 1 && i == bSize - 1)
                {
                    found = 0;
                }
            }
            if(found > 0)
            {
                break;
            }
        }

        if (*(word) == *(*(arr + iy) + ix))
        {
            addLetterPath(x, y);
            checkClockwise(arr, word, x, y);
        }
    }
    else
    {
        int i = y;
        int j = x+1;
        //printf("%d, %d\n", x, y);
        
        while (i != bSize)
        {
            //printf("%d, %d\n", x, y);
            if (j == bSize)
            {
                j = 0;
                i++;
            }
            if (*(word) == *(*(arr + i) + j))
            {
                ix = j;
                iy = i;
                x = j;
                y = i;
                found++;
                break;
            }
            j++;
            
        }
        if (*(word) == *(*(arr + iy) + ix))
        {
            addLetterPath(x,y);
            checkClockwise(arr, word, x, y);
        }
        else
        {
            found = 0;
        }
    }
}

void buildEmptyPath()
{
    path = (int**)malloc(bSize * sizeof(int*));    
	for (int i = 0; i < bSize; i++)
    {
		*(path + i) = (int*)malloc(bSize * sizeof(int));
	}
    for (int i = 0; i < bSize; i++)
    {
		for (int j = 0; j < bSize; j++)
        {
			*(*(path + i) + j) = 0;
		}
	}
}

void resetPath()
{
    for (int i = 0; i < bSize; i++)
    {
		for (int j = 0; j < bSize; j++)
        {
			*(*(path + i) + j) = 0;
		}
	}
    found = 0;
    counter = 0;
    x = ix;
    y = iy;
}

void addLetterPath(int x, int y) // add to the path if found a valid letter
{ 
    int sum = *(*(path + y) + x);
    int temp = 1;
    counter++;
    for(int i = 0; i < 100; i++) // step 2 and step 4 turns to "42" in seach path
    {
        if (temp < sum)
        {
            temp = temp * 10;
        }else if ( temp > sum)
        {
            sum = temp * counter + sum;
            break;
        }
    }
    *(*(path + y) + x) = sum;
}

void printPath()
{ 
    printf("Printing the search path:\n");
    for (int i = 0; i < bSize; i++)
    { 
		for (int j = 0; j < bSize; j++)
        {
            if(*(*(path + i) + j) < 10)
            {
                printf("%d       ", *(*(path + i) + j));
            }
            else if(*(*(path + i) + j) >= 10 && *(*(path + i) + j) < 100)
            {
                printf("%d      ", *(*(path + i) + j));
            }
            else if(*(*(path + i) + j) >= 100 && *(*(path + i) + j) < 1000)
            {
                printf("%d     ", *(*(path + i) + j));
            }
            else if(*(*(path + i) + j) >= 1000 && *(*(path + i) + j) < 10000)
            {
                printf("%d    ", *(*(path + i) + j));
            }
            else if(*(*(path + i) + j) >= 10000 && *(*(path + i) + j) < 100000)
            {
                printf("%d   ", *(*(path + i) + j));
            }
            else if(*(*(path + i) + j) >= 100000 && *(*(path + i) + j) < 1000000)
            {
                printf("%d  ", *(*(path + i) + j));
            }
            else if(*(*(path + i) + j) >= 1000000 && *(*(path + i) + j) < 10000000)
            {
                printf("%d ", *(*(path + i) + j));
            }
            else
            {
                printf("%d", *(*(path + i) + j));
            }
		}
		printf("\n");
	}
    printf("\n");
}

void checkClockwise(char** arr, char* word, int x, int y) // checks letters in a clockwise pattern (starts from right and goes out in a spiral)
{
    if(y-1 >= 0 && x-1 >= 0 && *(word+counter)!='\0')
    {
        if (*(word + counter) == *(*(arr + (y-1)) + (x-1)))
        {
            x--;
            y--;
            addLetterPath(x,y);
            checkClockwise(arr, word, x, y);
        }
    }
    if(y-1 >= 0 && *(word+counter)!='\0')
    {
        if (*(word + counter) == *(*(arr + (y-1)) + x))
        {
            y--;
            addLetterPath(x,y);
            checkClockwise(arr, word, x, y);
        }
    }
    if(y-1 >= 0 && x+1 < bSize && *(word+counter)!='\0')
    {
        if (*(word + counter) == *(*(arr + (y-1)) + (x+1)))
        {
            x++;
            y--;
            addLetterPath(x,y);
            checkClockwise(arr, word, x, y);
        }
    }
    if(x+1 < bSize && *(word+counter)!='\0')
    {
        if (*(word + counter) == *(*(arr + y) + (x+1)))
        {
            x++;
            addLetterPath(x,y);
            checkClockwise(arr, word, x, y);
        }
    }
    if(y+1 < bSize && x+1 < bSize && *(word+counter)!='\0')
    {
        if (*(word + counter) == *(*(arr + (y+1)) + (x+1)))
        {
            x++;
            y++;
            addLetterPath(x,y);
            checkClockwise(arr, word, x, y);
        }
    }
    if(y+1 < bSize && *(word+counter)!='\0')
    {
        if (*(word + counter) == *(*(arr + (y+1)) + x))
        {
            y++;
            addLetterPath(x,y);
            checkClockwise(arr, word, x, y);
        }
    }
    if(y+1 < bSize && x-1 >= 0 && *(word+counter)!='\0')
    {
        if (*(word + counter) == *(*(arr + (y+1)) + (x-1)))
        {
            x--;
            y++;
            addLetterPath(x,y);
            checkClockwise(arr, word, x, y);
        }
    }
    if(x-1 >= 0 && *(word+counter)!='\0')
    {
        if (*(word + counter) == *(*(arr + y) + (x-1)))
        {
            x--;
            addLetterPath(x,y);
            checkClockwise(arr, word, x, y);
        }
    }
    if(*(word+counter) !='\0')
    {
        resetPath();
        x = ix;
        y = iy;
        addLetterPath(x,y);
        checkCounterClockwise(arr, word, x, y);
    }
    else
    {
        found = 1;
    }
}

void checkCounterClockwise(char** arr, char* word, int x, int y) // checks letters in a counterclockwise pattern (starts from left and goes out in a spiral)
{
    if(x-1 >= 0 && *(word+counter)!='\0')
    {
        if (*(word + counter) == *(*(arr + y) + (x-1)))
        {
            x--;
            addLetterPath(x,y);
            checkCounterClockwise(arr, word, x, y);
        }
    }
    if(y+1 < bSize && x-1 >= 0 && *(word+counter)!='\0')
    {
        if (*(word + counter) == *(*(arr + (y+1)) + (x-1)))
        {
            x--;
            y++;
            addLetterPath(x,y);
            checkCounterClockwise(arr, word, x, y);
        }
    }
    if(y+1 < bSize && *(word+counter)!='\0')
    {
        if (*(word + counter) == *(*(arr + (y+1)) + x))
        {
            y++;
            addLetterPath(x,y);
            checkCounterClockwise(arr, word, x, y);
        }
    }
    if(y+1 < bSize && x+1 < bSize && *(word+counter)!='\0')
    {
        if (*(word + counter) == *(*(arr + (y+1)) + (x+1)))
        {
            x++;
            y++;
            addLetterPath(x,y);
            checkCounterClockwise(arr, word,x,y);
        }
    }
    if(y-1 >= 0 && x+1 < bSize && *(word+counter)!='\0')
    {
        if (*(word + counter) == *(*(arr + (y-1)) + (x+1)))
        {
            x++;
            y--;
            addLetterPath(x,y);
            checkCounterClockwise(arr, word,x,y);
        }
    }
    if(y-1 >= 0 && *(word+counter)!='\0')
    {
        if (*(word + counter) == *(*(arr + (y-1)) + x))
        {
            y--;
            addLetterPath(x,y);
            checkCounterClockwise(arr, word,x,y);
        }
    }
    if(y-1 >= 0 && x-1 >= 0 && *(word+counter)!='\0')
    {
        if (*(word + counter) == *(*(arr + (y-1)) + (x-1)))
        {
            x--;
            y--;
            addLetterPath(x,y);
            checkCounterClockwise(arr, word,x,y);
        }
    }
    if(*(word+counter) !='\0')
    {
        resetPath();
        x = ix;
        y = iy;
        firstLetter(arr, word, x, y);
    }
    else
    {
        found = 1;
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "random.h"
#include<termios.h>
#include"terminal.h"

void initRandom()
{
    srand(time(NULL));
}

int random_UCP(int low, int high)
{
    int number = -1;

    if(low <= high)
    {
        number = (rand() % (high-low+1)) + low;
    }

    return number;
}

void disableBuffer()
{
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}

void enableBuffer()
{
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag |= (ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int rows, cols;
    int i, j;

    FILE *pf = fopen(argv[1], "r");

    if (pf == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    /* Read rows and cols from the file (assuming the first two numbers are rows and cols) */
    if (fscanf(pf, "%d %d", &rows, &cols) != 2) {
        printf("Error reading matrix dimensions.\n");
        fclose(pf);
        return 1;
    }

    /* Allocate memory for the 2D array */
    int **data = malloc(rows * sizeof(int *));
    for (i = 0; i < rows; i++) {
        data[i] = malloc(cols * sizeof(int));
    }

    /* Read the matrix data */
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (fscanf(pf, "%d", &data[i][j]) != 1) {
                printf("Error reading matrix data.\n");
                for (int k = 0; k <= i; k++) free(data[k]);
                free(data);
                fclose(pf);
                return 1;
            }
        }
    }

    fclose(pf);

    /* Print the map with borders */
    printf("*");
    for (j = 0; j < cols; j++) {
        printf("*");
    }
    printf("*\n");

    const char* enemy[] = {"^", "v", ">", "<"};


    for (i = 0; i < rows; i++) {
        printf("*");
        for (j = 0; j < cols; j++) {
            /* Map numbers to ASCII characters */
            char c;
            switch (data[i][j]) {
                case 0: c = ' '; break; /* Map 0 to space */
                case 1: c = 'P'; break; /* Map 1 to 'P' */
                case 2: c = 'G'; break; /* Map 2 to 'G' */
                case 3: c = 'O'; break; /* Map 3 to 'O' */
                case 4: {
                    int enemydirection = random_UCP(0, 3); /* Randomize direction for each enemy */
                    c = *enemy[enemydirection];
                    break;
                }
                default: c = '?'; break; /* Map unknown numbers to '?' */
            }
            printf("%c", c);
        }
        printf("*\n");
    }

    printf("*");
    for (j = 0; j < cols; j++) {
        printf("*");
    }
    printf("*\n");

    /* Free allocated memory */
    for (i = 0; i < rows; i++) {
        free(data[i]);
    }
    free(data);

    return 0;
}

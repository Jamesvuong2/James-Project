#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "random.h"
#include <termios.h>
#include "terminal.h"

/* Initialises the random functions */
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

char interface()
{
    char input;

    disableBuffer(); /* Disables terminal input buffering and echo */
    input = getchar(); /* Waits for a single key press */
    enableBuffer(); /* Re-enables terminal input buffering and echo */

    return input;
}

int movePlayer(int **data, int rows, int cols, char direction)
{
    int playerRow = -1, playerCol = -1;

    /* This finds the current position of the player (with P being 1) */
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (data[i][j] == 1) {
                playerRow = i;
                playerCol = j;
                break;
            }
        }
        if (playerRow != -1) break;
    }

    /* Determines the new position based on the input direction */
    int newRow = playerRow, newCol = playerCol;
    if (direction == 'w' && playerRow > 0) newRow--;       /* up */
    else if (direction == 's' && playerRow < rows - 1) newRow++; /* down */
    else if (direction == 'a' && playerCol > 0) newCol--;       /* left */
    else if (direction == 'd' && playerCol < cols - 1) newCol++; /* right */

    /* Checks if the new position is valid with the goal being 2, air being 0 and enemy being 4 */
    if (data[newRow][newCol] == 0) {
        data[playerRow][playerCol] = 0; /* Clears the old position */
        data[newRow][newCol] = 1;       /* Sets the new position */
    }
    else if (data[newRow][newCol] == 2) {
        data[playerRow][playerCol] = 0; /* Clears the old position */
        data[newRow][newCol] = 1;       /* Sets the new position */
        return 1; /* Player reached the goal */
    }
    else if (data[newRow][newCol] == 4) {
        data[playerRow][playerCol] = 0; /* Clears the old position */
        data[newRow][newCol] = 1;       /* Sets the new position */
        return 2; /* Player touched enemy */
    }
    return 0; /* Player did not move */
}

void game(char *filename)
{

    int rows, cols;
    int i, j;

    FILE *pf = fopen(filename, "r");

    if (pf == NULL) {
        printf("Error opening file.\n");
        return;
    }

    /* Reads the rows and columns from the file (assuming the first two numbers are rows and columns) */
    if (fscanf(pf, "%d %d", &rows, &cols) != 2) {
        printf("Error reading matrix dimensions.\n");
        fclose(pf);
        return;
    }

    /* Allocates memory for the 2D array */
    int **data = malloc(rows * sizeof(int *));
    if (data == NULL) {
        printf("Memory allocation failed for data array.\n");
        fclose(pf);
        return;
    }

    for (i = 0; i < rows; i++) {
        data[i] = malloc(cols * sizeof(int));
        if (data[i] == NULL) {
            printf("Memory allocation failed for row %d.\n", i);
            for (int k = 0; k < i; k++) free(data[k]); /* Free previously allocated rows */
            free(data);
            fclose(pf);
            return;
        }
    }


    /* Reads the matrix data */
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (fscanf(pf, "%d", &data[i][j]) != 1) {
                printf("Error reading matrix data.\n");
                for (int k = 0; k <= i; k++) free(data[k]);
                free(data);
                fclose(pf);
                return;
            }
        }
    }

    fclose(pf);

    while (1) {
        /* Prints the map */
        printf("*");
        for (j = 0; j < cols; j++) {
            printf("*");
        }
        printf("*\n");

        const char* enemy[] = {"^", "v", ">", "<"};
        int enemyFacingPlayer = 0; /* Flag to check if an enemy is facing the player */
        
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
                        int enemydirection = random_UCP(0, 3); /* Randomizes the direction for each enemy */
                        c = *enemy[enemydirection];

                        /* Check if the enemy is facing the player */
                        if (enemydirection == 0 && i > 1 && (data[i - 1][j] == 1 || data[i - 2][j] == 1)) {
                            data[i][j] = 0;
                            data[i - 1][j] = 4; /* Move enemy up */
                            enemyFacingPlayer = 1;
                        }
                        if (enemydirection == 1 && i < rows - 2 && (data[i + 1][j] == 1 || data[i + 2][j] == 1)) {
                            data[i][j] = 0;
                            data[i + 1][j] = 4; /* Move enemy down */
                            enemyFacingPlayer = 1;
                        }
                        if (enemydirection == 2 && j < cols - 2 && (data[i][j + 1] == 1 || data[i][j + 2] == 1)) {
                            data[i][j] = 0;
                            data[i][j + 1] = 4; /* Move enemy right */
                            enemyFacingPlayer = 1;
                        }
                        if (enemydirection == 3 && j > 1 && (data[i][j - 1] == 1 || data[i][j - 2] == 1)) {
                            data[i][j] = 0;
                            data[i][j - 1] = 4; /* Move enemy left */
                            enemyFacingPlayer = 1;
                        }
                        break;
                    }
                    default: c = '?'; break; /* Maps unknown numbers to '?', this is the default */
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

        /* Gets the input from the user */
        printf("w moves the player one block above.\n"
               "s moves the player one block below.\n"
               "a moves the player one block left.\n"
               "d moves the player one block right.\n");
        char input = interface();

        /* Moves the player based on the input */
        int result = movePlayer(data, rows, cols, input);
        /* Break the loop if an enemy is facing the player */
        if (enemyFacingPlayer) {
            result = 2;
        }
        if (result == 1) {
            printf("You win.\n");
            break;
        } else if (result == 2) {
            printf("You are ded.\n");
            break;
        }
    }

    /* Frees allocated memory */
    for (i = 0; i < rows; i++) {
        free(data[i]);
    }
    free(data);

    return;
}
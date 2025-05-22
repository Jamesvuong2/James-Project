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

int interface()
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

int main()
{
    game("map.txt");
    return 0;
}

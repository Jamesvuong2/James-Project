#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "newSleep.h"

#define EMPTY 0
#define PLAYER 1
#define GOAL 2
#define OBSTACLE 3
#define ENEMY 4

void disableBuffer();
void enableBuffer();
char interface();
int movePlayer(int **data, int rows, int cols, char direction);
void printMap(int **data, int rows, int cols);
void freeMap(int **data, int rows);
int checkEnemyFacingPlayer(int **data, int rows, int cols);
void game(char *filename);

#endif
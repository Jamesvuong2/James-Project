#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <termios.h>

void initRandom();
int random_UCP(int low, int high);
void disableBuffer();
void enableBuffer();
int interface();
void movePlayer(int **data, int rows, int cols, char direction);

#endif
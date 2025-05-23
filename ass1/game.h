#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "newSleep.h"

typedef struct GameState {
    int rows;
    int cols;
    int playerRow;
    int playerCol;
    int enemydirection;
    int **data;
} GameState;

typedef struct Node {
    GameState *state;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
    int count;
} LinkedList;

LinkedList *createLinkedList();
void insertLast(LinkedList *list, GameState *state);
GameState *removeLast(LinkedList *list);

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

#endif // LINKEDLIST_H
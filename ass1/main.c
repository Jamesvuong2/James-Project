#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "random.h"
#include <termios.h>
#include "terminal.h"
#include "game.h"
#include "newSleep.h"
#include "LinkedList.h"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    game(argv[1]);
    return 0;
}

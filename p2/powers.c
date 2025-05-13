#include <stdio.h>

int add() {

    static int num = 0;
    num = num + 2;

    return num;
}

int main () {
    int num = add();
    printf("%d", &num);
    return 0;
}
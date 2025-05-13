#include <stdio.h>
#include "math.c"
#ifdef MATH_H

#define MATH_H

int add();
typedef int UCP_int;

#endif

int add();
typedef int UCP_int;

#ifdef MATH_H
#define MATH_H

int main() {

    printf("%d\n", add());
    printf("%d\n", add());
    printf("%d\n", add());
    printf("%d\n", add());
    printf("%d\n", add());
    printf("%d\n", add());

    return 0;
}


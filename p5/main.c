#include <stdio.h>

typedef void (*FptrType)();

void sayHello() {
    printf("sayHello() is called with value: %d\n", x);
}

int sayHello3(int x) {
    printf("sayHello3(%d) is called: %d\n", x);
}

int sayHello4(int x) {
    printf("sayHello4() is called: %d\n", x);
    return 10;
}

int sayHello2(int x) {
    printf("sayHello2() is called with value: %d\n", x);
    return x;
}

int main() {
    int ret = 0;

    FptrType fptr = &sayHello;
    (*fptr)();

    ret = SayHello2(100);
    printf("Returned value is: %d\n", ret);

    /* void (*fpsayHello)(); Declaration of the function pointer*/
    /* fpSayHello = &sayHello;  Initialisation of the function pointer*/
    /* fpSayHello = &sayHello3; */
    /* fpSayHello = &sayHello4; */

    /* (*fpSayHello)();  Initialisation of the function pointer*/

    sayHello();
    return 0;
}
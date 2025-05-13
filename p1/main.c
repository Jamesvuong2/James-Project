#include <stdio.h>

int main(void) {
    int number1;
    int number2;
    printf("Enter 1 number\n");
    scanf("%d", &number1);
    if(number1 != 0)
        printf("Enter another number\n");
        scanf("%d", &number2);

        if(number1 != 0)
            if(number1 % number2)
                printf("divisible\n");
            else
                printf("undivisible\n");
    return 0;
 }
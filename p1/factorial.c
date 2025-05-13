#include <stdio.h>

int main(void){
    int ent;
    int number;
    printf("Please enter a number\n");
    scanf("%d", &number);
    if(number >= 0)
        ent = factorial(number);
        printf("%d", ent);

}

int factorial(int n){
    int i;
    int fact = 1;
    for (i = 1; i <= n; ++i) {
        fact *= i;
    }
    return fact;
}
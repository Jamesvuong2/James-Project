#include <stdio.h>


void swap(int* pNum1, int* pNum2)
{
    int temp = *pNum1;
    *pNum1 = *pNum2;
    *pNum2 = temp;
}

int main() {

    int num1 = 10, num2 = 20;

    printf("The numbers: %d %d\n", num1, num2);

    swap(&num1, &num2);

    printf("The numbers (after swap): %d, %d/n", num1, num2);


    return 0;
}
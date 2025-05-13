#include <stdio.h>

/*Static function that returns void*/
void ascending2(int* pNum1, int* pNum2) {

    int temp = *pNum1;
    *pNum1 = *pNum2;
    *pNum2 = temp;

}

void ascending3(int* pNum1, int* pNum2, int* pNum3) {

    int temp = *pNum1;
    *pNum1 = *pNum2;
    *pNum2 = *pNum3;
    *pNum3 = temp;
        
}

/*Main function*/
int main() {

    /*Defines the integers*/
    int num1, num2, num3;

    printf("The numbers: %d %d\n", num1, num2);

    /*Swaps the 2 values around*/
    ascending2(&num1, &num2);

    printf("The numbers (after swap): %d, %d/n", num1, num2);



    printf("The numbers: %d %d\n %d\n", num1, num2, num3);

    /*arranges them*/
    ascending3(&num1, &num2, &num3);

    printf("The numbers (after swap): %d, %d/n, %d/n", num1, num2, num3);

    return 0;
}
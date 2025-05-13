#include <stdio.h>

int sum(int iArr[], int len) {
/* int sum(int* iArr, int len) { */

    int total = 0;
    int i;
    for (i = 0 ; i < len ; i++) {
        total += iArr[i];
    }

    return total;
}

int max (int iArr[], int len) {
    int n;
    int highest;
    for (n=0; n<len; n++) {
        highest == iArr[len - 1];
    return highest;
    }
}

int main() {

    int arr[5] = {10, 20, 30, 40, 50};

    int total = sum(arr, 5);

    int highest = max(arr, 5);

    printf("The sum is: %d\n", total);

    printf ("The max is: %d\n ",highest);

    return 0;
}
#include<stdio.h>
#include"parity.h"

void parity(int number)
{
    if(number % 2 == 0)
    {
        printf("%d is even\n", number);
    }
    else
    {
        printf("%d is odd\n", number);
    }
}
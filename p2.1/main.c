#include"calculate.h"
#include"parity.h"

int main()
{
    parity( square(5) );

    #ifdef CUBE
        parity( cube(2) );
    #endif

    return 0;
}
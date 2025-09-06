/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>

// Gives 2^n
#define POWER_OF_TWO(n)    (1 << (n))

// Multiply number by 2^n
#define MUL_BY_POW2(num, n)   ((num) << (n))

// Divide number by 2^n
#define DIV_BY_POW2(num, n)   ((num) >> (n))

int main() {
    int num = 8;

    printf("2^3 = %d\n", POWER_OF_TWO(2));

    printf("%d * 2^2 = %d\n", num, MUL_BY_POW2(num, 2));
    printf("%d * 2^3 = %d\n", num, MUL_BY_POW2(num, 3));

    printf("%d / 2^1 = %d\n", num, DIV_BY_POW2(num, 1));
    printf("%d / 2^2 = %d\n", num, DIV_BY_POW2(num, 2));

    return 0;
}

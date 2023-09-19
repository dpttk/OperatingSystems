#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <float.h>

int main (){

int i  = INT_MAX;

unsigned short us = USHRT_MAX;

float f = FLT_MAX; 

double d = DBL_MAX;


printf("int: %lu, %d  \n", sizeof(int), i );

printf("short: %lu, %u  \n", sizeof(unsigned short), us);

printf("float: %lu, %f \n", sizeof(float), f);

printf("double: %lu, %f  \n", sizeof(double), d);



return EXIT_SUCCESS; 
}

#include <stdio.h>
#include <stdlib.h>

void* add(const void* a, const void* b) {
    double* result = malloc(sizeof(double));
    *result = *(double*)a + *(double*)b;
    return (void*)result;
}

void* multiply(const void* a, const void* b) {
    double* result = malloc(sizeof(double));
    *result = *(double*)a * *(double*)b;
    return (void*)result;
}

void* max(const void* a, const void* b) {
    if (*(double*)a >= *(double*)b) {
        return (void*)a;
    } else {
        return (void*)b;
    }
}

void* aggregate(void* base, size_t size, int n, void* initialValue, void* (*opr)(const void*, const void*)) {

    void* result = initialValue;

    for (int i = 0; i < n; i++) {
        result = opr(result, base + i * size);
    }
    return result;
}

int main() {
    double doubleArray[5] = {1.4, 5.45, 0.5, 13.51, 4.20};
    int intArray[5] = {14, 0, 34, 44, 54};

    double * initial = malloc(sizeof (double ));
    *initial = 0;
    double* dSum = (double*)aggregate(doubleArray, sizeof(double), 5, initial, add);
    printf("Sum of doubles: %.2lf\n", *dSum);

    *initial = 1;
    double* dMult = (double*)aggregate(doubleArray, sizeof(double), 5, initial, multiply);
    printf("Mult of doubles: %.2lf\n", *dMult);

    *initial = 0;
    double* dMax = (double*)aggregate(doubleArray, sizeof(double), 5, initial, max);
    printf("Max of doubles: %.2lf\n", *dMax);
    free(initial);


    int * intInitial = malloc(sizeof (int));

    *intInitial = 0;
    int* iSum = (int*) aggregate(intArray,sizeof (int),5,intInitial, add);
    printf("Sum of ints: %d\n",*iSum);


    *intInitial = 1;
    int* iMult = (int*) aggregate(intArray,sizeof (int),5,intInitial, multiply);
    printf("Mult of ints: %d\n",*iMult);

    *intInitial = 0;
    int* iMax = (int*) aggregate(intArray,sizeof (int),5,intInitial, max);
    printf("Max of ints: %d\n",*iMax);

    free(intInitial);

    return 0;
}

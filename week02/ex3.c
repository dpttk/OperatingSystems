#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

long long power(int base, int exponent) {
    long long result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

void convert(long long number, int s, int t) {
    if (s < 2 || s > 10 || t < 2 || t > 10) {
        printf("cannot convert!\n");
        return;
    }

    if (number < 0) {
        printf("cannot convert!\n");
        return;
    }

    long long result = 0;
    long long multiplier = 1;
    int digit;
    bool valid = true;

    while (number > 0) {
        digit = number % 10;
        if (digit >= s) {
            valid = false;
            break;
        }
        result += digit * multiplier;
        multiplier *= s;
        number /= 10;
    }

    if (!valid) {
        printf("cannot convert!\n");
        return;
    }

    char converted[64];
    int i = 0;

    while (result > 0) {
        digit = result % t;
        converted[i] = digit + '0';
        i++;
        result /= t;
    }

    if (i == 0) {
        converted[i] = '0';
        i++;
    }

    converted[i] = '\0';

    char final[64];
    int j = 0;

    for (int k = i - 1; k >= 0; k--) {
        final[j] = converted[k];
        j++;
    }

    final[j] = '\0';

    printf("%s\n", final);
}

int main() {
    long long number;
    int s, t;

    if (scanf("%lld %d %d", &number, &s, &t) != 3) {
        return 1;
    }

    convert(number, s, t);

    return 0;
}

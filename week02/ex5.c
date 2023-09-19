#include <stdio.h>

long long tribonacci(int n) {
    if (n == 0) return 0;
    if (n == 1 || n == 2) return 1;

    long long t0 = 0, t1 = 1, t2 = 1, tn;

    for (int i = 3; i <= n; i++) {
        tn = t0 + t1 + t2;
        t0 = t1;
        t1 = t2;
        t2 = tn;
    }

    return tn;
}

int main() {
    int n = 4;
    printf("Tribonacci(%d) = %lld\n", n, tribonacci(n));

    n = 36;
    printf("Tribonacci(%d) = %lld\n", n, tribonacci(n));

    return 0;
}

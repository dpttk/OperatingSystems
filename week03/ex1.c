#include <stdio.h>
#include <stdlib.h>

int const_tri(int* const p, int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 1;

    p[0] = 0;
    p[1] = 1;
    p[2] = 1;

    for (int i = 3; i <= n; i++) {
        int temp = p[0] + p[1] + p[2];
        p[0] = p[1];
        p[1] = p[2];
        p[2] = temp;
    }
    return p[2];
}

int main() {
    const int x = 1;
    const int* q = &x;

    int* const p = (int*)malloc(3 * sizeof(int));
    if (!p) {
        return 1;
    }

    p[0] = x;
    p[1] = x;
    p[2] = 2 * x;

    if (&p[1] - &p[0] == 1 && &p[2] - &p[1] == 1) {
        printf("contiguous\n");
    }

    printf("%d\n", const_tri(p, 6));

    free(p);

    return 0;
}


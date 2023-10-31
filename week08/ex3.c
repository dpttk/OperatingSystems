#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <unistd.h>

#define MEMORY_ALLOCATION_SIZE (10 * 1024 * 1024) // 10 MB

void printMemoryUsage() {
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        printf("Memory Usage: %ld KB\n", usage.ru_maxrss);
    }
}

int main() {
    int i;
    for (i = 0; i < 10; i++) {
        char *memory = (char *)malloc(MEMORY_ALLOCATION_SIZE);

        memset(memory, 0, MEMORY_ALLOCATION_SIZE);
        printMemoryUsage();
        sleep(1);
        free(memory);
    }

    return 0;
}

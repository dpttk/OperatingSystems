#include <time.h>
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
int main() {
    int id = fork();
    clock_t start_time = clock();

    if (id == 0 ){
        printf("Child 1 - Process ID: %d, Parent ID: %d\n", getpid(), getppid());
        clock_t end_time = clock();
        printf("Child 1 Execution Time: %.2f \n", (double)(end_time - start_time) * 1000.0 / CLOCKS_PER_SEC);
        exit(0);
    }

    id = fork();
    start_time = clock();
    if (id == 0) {
        printf("Child 2 - Process ID: %d, Parent ID: %d\n", getpid(), getppid());
        clock_t end_time = clock();
        printf("Child 2 Execution Time: %.2f \n", (double)(end_time - start_time) * 1000.0 / CLOCKS_PER_SEC);
        exit(0);
    }




    return 0;
}

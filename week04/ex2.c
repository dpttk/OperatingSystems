#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <malloc.h>

#define VECTOR_SIZE 120

int calculateDotProduct(int start, int end, int const *u, int const *v) {
    int result = 0;
    for (int i = start; i < end; i++) {
        result += u[i] * v[i];
    }
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    int step = VECTOR_SIZE / n;
    for(;;){
        if (n*step != VECTOR_SIZE){
            printf("write number of processes which is dividable by %d\n",VECTOR_SIZE);
            scanf("%d",&n);
            step = VECTOR_SIZE / n;
        } else{
            break;
        }
    }

    int u[VECTOR_SIZE];
    int v[VECTOR_SIZE];

    for (int i = 0; i < VECTOR_SIZE; i++) {
        u[i] = rand() % 100;
        v[i] = rand() % 100;
    }

    FILE *file = fopen("temp.txt", "w");

    int process_id;
    int result = 0;


    pid_t * processes_array =  (pid_t *)malloc(sizeof(pid_t));
    srand(12);
    for (int i = 0; i < n; i++) {
        process_id = fork();
	processes_array[i]=process_id;
        if (process_id == 0) {
            int start = i * step;
            int end = (i + 1) * step;
            int partialResult = calculateDotProduct(start, end, u, v);
            fprintf(file, "%d\n", partialResult);
            fclose(file);
            exit(0);
        }
    }

    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    fclose(file);

    file = fopen("temp.txt", "r");

    int partialResult;
    while (fscanf(file, "%d", &partialResult) != -1) {
        result += partialResult;
    }

    fclose(file);

    printf("%d\n", result);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_MESSAGE_SIZE 256

struct Thread {
    pthread_t id;
    int i;
    char message[MAX_MESSAGE_SIZE];
};

void* thread_function(void* arg) {
    struct Thread* thread_data = (struct Thread*)arg;

    printf("Thread %d is created\n", thread_data->i);

    snprintf(thread_data->message, MAX_MESSAGE_SIZE, "Hello from thread %d", thread_data->i);

    printf("%s\n", thread_data->message);

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    
    int n = atoi(argv[1]);

    struct Thread threads[n];

    for (int i = 0; i < n; i++) {
        threads[i].i = i + 1;
        pthread_create(&threads[i].id, NULL, thread_function, &threads[i]);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i].id, NULL);
    }

    return 0;
}

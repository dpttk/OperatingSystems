#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define MAX_MSG_LEN 1024

int main() {

    FILE *pf = fopen("/var/run/agent.pid", "w");
    fprintf(pf, "%d\n", getpid());
    fclose(pf);

    char msg[MAX_MSG_LEN];
    FILE *tf = fopen("text.txt", "r");
    fgets(msg, sizeof(msg), tf);
    fclose(tf);

    printf("%s\n", msg);

    for (;;) {
        sleep(1);
    }

    return 0;
}

void handleSignal(int sig) {
    switch (sig) {
        case SIGUSR1:
            char msg[MAX_MSG_LEN];
            FILE *tf = fopen("text.txt", "r");
            if (!tf) {
                perror("Failed to open text.txt");
                return;
            }
            fgets(msg, sizeof(msg), tf);
            fclose(tf);
            break;
        case SIGUSR2:
            printf("Process terminating...\n");
            exit(0);
            break;
    }
}

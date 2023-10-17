#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#define MAX_CMD_LEN 32

int main() {
    FILE *pf = fopen("/var/run/agent.pid", "r");

    int pid;
    fscanf(pf, "%d", &pid);
    fclose(pf);

    if (pid == 0) {
        printf("Error: No agent found.\n");
        return 1;
    }

    printf("Agent found. PID: %d\n", pid);

    while (1) {
        printf("Choose a command {`read`, `exit`, `stop`, `continue`} to send to the agent: ");
        char cmd[MAX_CMD_LEN];
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strcspn(cmd, "\n")] = 0;

        if (strcmp(cmd, "read") == 0) {
            kill(pid, SIGUSR1);
        } else if (strcmp(cmd, "exit") == 0) {
            kill(pid, SIGUSR2);
            exit(0);
        } else if (strcmp(cmd, "stop") == 0) {
            kill(pid, SIGSTOP);
        } else if (strcmp(cmd, "continue") == 0) {
            kill(pid, SIGCONT);
        }
    }

    return 0;
}

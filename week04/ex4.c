#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARG_COUNT 64

void parse_command(char *input, char *command, char *args[]) {
    char *token;
    int arg_count = 0;

    token = strtok(input, " \t\n");
    while (token != NULL) {
        if (arg_count < MAX_ARG_COUNT - 1) {
            args[arg_count++] = token;
        }
        token = strtok(NULL, " \t\n");
    }

    args[arg_count] = NULL;
    strcpy(command, args[0]);
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char command[MAX_INPUT_LENGTH];
    char *args[MAX_ARG_COUNT];

    for (;;) {
        printf("shell> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        parse_command(input, command, args);

        int pid = fork();

        if (pid == 0) {
            execvp(command, args);
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

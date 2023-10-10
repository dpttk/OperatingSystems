#include <complex.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PATH "./tmp/ex1/s"

int main(int argc, char** args) {
    int fd[argc][2];
    for (int i = 0; i < argc; i++) {
        pipe(fd[i]);
    }
    pid_t process[argc];
    FILE* pipes[argc];
 
    process[0] = fork();
    if (process[0]!=0)
        for (int i = 1; i < argc; i++) {
            if (process[i-1]!=0){
                process[i] = fork();
            }
        }

    for (int i = 0; i < argc; i++) {
        if (process[i] == 0) {
            char command[100]; 
            sprintf(command, "%s%c.txt", PATH, i + '0' + 1);
            pipes[i] = popen(command, "w");

            char message[100]; 
            for (int j = 0; j < argc; j++) {
                if (j != i)
                    close(fd[j][0]);
                close(fd[j][1]);
            }

            int n;
            read(fd[i][0], &n, sizeof(int));
            read(fd[i][0], message, sizeof(char) * n);
            fwrite(message, sizeof(char), n, pipes[i]);
            close(fd[i][0]);

            fclose(pipes[i]);

            return 0;
        }
    }

    for (int i = 0; i < argc; i++) {

        for (int j = 0; j < argc; j++) {
            close(fd[j][0]);
            if (j != i)
                close(fd[j][1]);
        }


        char message[100];
        scanf("%s", message);
        int n = sizeof(char) * strlen(message) + 1;
        write(fd[i][1], &n, sizeof(int));
        write(fd[i][1], message, sizeof(char) * n);
        close(fd[i][1]);
        waitpid(process[i], NULL, 0);
    }

    return 0;
}

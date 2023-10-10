#include "stdio.h"
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "string.h"



int main () {

    int publisher_id = fork();
    int fd[2];
    pipe(fd);
    
    int subscriber_id = fork();
    if (subscriber_id == 0) {
        close(fd[1]);
        char temp[1024];
        int n;
        read(fd[0],&n, sizeof(int));
        read(fd[0],temp,sizeof(char) * n  );
        close(fd[0]);
        puts(temp);
        exit(0);
    } else {
        close(fd[0]);  
        char temp[1024];
        fgets(temp, sizeof(temp), stdin);
        temp[strlen(temp)-1] = '\0';
        int n = strlen(temp) +1;
        write(fd[1],&n,sizeof(int));
        write(fd[1], temp, n* sizeof(char));
        close(fd[1]);   
    }

    return 0; 
}   
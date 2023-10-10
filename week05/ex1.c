#include <complex.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PATH "./tmp/ex1/s"

int main(int argc, char** args) {
    char command[100];
    sprintf(command,"%s%c.txt\0", PATH,argc+'0');

    FILE * pipe = popen(command, "r");

    char message[1024];

    
    fread(message, sizeof(char), 1024, pipe);

    puts(message);
    fclose(pipe);

}

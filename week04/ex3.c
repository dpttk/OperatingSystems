#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc) {
    for (int i =0; i<argc; i++){
        fork();
        sleep(5);
    }

sleep(5);
    return 0;
}

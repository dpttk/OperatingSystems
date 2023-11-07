#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

#define PASSWORD_LENGTH 8

int main() {
    FILE *pidFile = fopen("/tmp/ex1.pid", "w");

    fprintf(pidFile, "%d\n", getpid());
    fclose(pidFile);

    int randomFile = open("/dev/random", O_RDONLY);
    char password[PASSWORD_LENGTH + 1];  


    ssize_t bytes_read = read(randomFile, password, PASSWORD_LENGTH*sizeof(char));
    close(randomFile);


    password[PASSWORD_LENGTH] = '\0';
    strcpy(password, "pass:");

    size_t map_size = strlen(password);
    
    char *map_addr = mmap(NULL, sizeof(password), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1,0);
    strcpy(map_addr, password);
    printf("%s", password);

    while(1){}
}

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <ctype.h>

#define FILE_SIZE 500*1024*1024
#define MAX_LINE 1024
#define CHUNK_SIZE 1024*sysconf(_SC_PAGESIZE) 

int main() {

  int fd, devrandom, filesize = 0; 
  char c;
  long sz = sysconf(_SC_PAGESIZE);

  fd = open("text.txt", O_WRONLY | O_CREAT, 0644);
  close(fd);

  devrandom = open("/dev/random", O_RDONLY);

  fd = open("text.txt", O_WRONLY | O_APPEND);
  
  while (filesize < FILE_SIZE) {
    read(devrandom, &c, 1);
    if (isprint(c)) {
      write(fd, &c, 1);
      filesize++;
      if (filesize % MAX_LINE == 0) {
        write(fd, "\n", 1); 
      }
    }
  }

  close(devrandom);
  close(fd);

  fd = open("text.txt", O_RDWR);
  int capitals = 0;

  for (off_t i = 0; i < FILE_SIZE; i += CHUNK_SIZE) {
    char *map = mmap(NULL, CHUNK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, i);

    for (int j = 0; j < CHUNK_SIZE; j++) {
      if (map[j] >= 'A' && map[j] <= 'Z') {
        capitals++;
        map[j] = map[j] - 'A' + 'a'; 
      }
    }

    munmap(map, CHUNK_SIZE);
  }

  close(fd);

  return 0;
}
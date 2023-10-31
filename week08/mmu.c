#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/mman.h>
#include <fcntl.h>

struct PTE {
    bool valid;
    int frame;
    bool dirty;
    int referenced;
};


void handle_SIGUSR1(int sig) {}

int main(int argc, char *argv[]) {
    int num_pages = atoi(argv[1);
    char *reference_string = argv[2];
    int pager_pid = atoi(argv[3]);

    int fd = open("/tmp/ex2/pagetable", O_RDWR);

    size_t page_table_size = sizeof(struct PTE) * num_pages;

    struct PTE *page_table = mmap(NULL, page_table_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    signal(SIGUSR1, handle_SIGUSR1);

    char *RAM[num_pages];
    for (int i = 0; i < num_pages; i++) {
        RAM[i] = NULL;
    }

    char *disk[num_pages];
    for (int i = 0; i < num_pages; i++) {
        disk[i] = "Placeholder";
    }

    for (int i = 0; i < strlen(reference_string); i += 2) {
        char mode = reference_string[i];
        int page = reference_string[i + 1] - '0';

        if (page_table[page].valid) {
            if (mode == 'W') {
                page_table[page].dirty = true;
            }
        } else {
            page_table[page].referenced = getpid();
            kill(pager_pid, SIGUSR1);
            pause();
        }

        for (int i = 0; i < num_pages; i++) {
            printf("Page %d ---> valid=%d, frame=%d, dirty=%d, referenced=%d\n", i, page_table[i].valid,
                   page_table[i].frame, page_table[i].dirty, page_table[i].referenced);
        }
        printf("-----------------------")
    }

    close(fd);

    kill(pager_pid, SIGUSR1);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <fcntl>
#include <time.h>

struct PTE {
    bool valid;
    int frame;
    bool dirty;
    int referenced;
};

void handle_SIGUSR1(int sig) {}

int main(int argc, char *argv[]) {
    int num_pages = atoi(argv[1);
    int num_frames = atoi(argv[2);

    int fd = open("/tmp/ex2/pagetable", O_RDWR);

    size_t page_table_size = sizeof(struct PTE) * num_pages;

    struct PTE *page_table = mmap(NULL, page_table_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    signal(SIGUSR1, handle_SIGUSR1);
    char *RAM[num_frames];
    for (int i = 0; i < num_frames; i++) {
        RAM[i] = NULL;
    }

    char *disk[num_pages];
    for (int i = 0; i < num_pages; i++) {
        disk[i] = "Placeholder";
    }

    int disk_accesses = 0;
    int num_loaded_pages = 0;

    while (num_loaded_pages < num_pages) {
        pause();

        for (int i = 0; i < num_pages; i++) {
            if (page_table[i].referenced != 0) {
                if (num_loaded_pages < num_frames) {
                    for (int j = 0; j < num_frames; j++) {
                        if (RAM[j] == NULL) {
                            RAM[j] = strdup(disk[i]);
                            page_table[i].frame = j;
                            page_table[i].valid = true;
                            page_table[i].referenced = 0;
                            num_loaded_pages++;

                            printf("Copy data from the disk (page=%d) to RAM (frame=%d)\n", i, j);
                            printf("Page table\n");
                            for (int k = 0; k < num_pages; k++) {
                                printf("Page %d ---> valid=%d, frame=%d, dirty=%d, referenced=%d\n",
                                       k, page_table[k].valid, page_table[k].frame,
                                       page_table[k].dirty, page_table[k].referenced);
                            }
                            printf("-------------------------\n");

                            kill(page_table[i].referenced, SIGCONT);
                            break;
                        }
                    }
                } else {
                    srand(time(NULL));
                    int victim_page = rand() % num_frames;
                    if (page_table[victim_page].dirty) {
                        disk[victim_page] = strdup(RAM[victim_page]);
                        disk_accesses++;
                        printf("Copy data from RAM (frame=%d) to disk (page=%d)\n", victim_page, victim_page);
                    }

                    page_table[victim_page].valid = false;
                    page_table[victim_page].dirty = false;
                    page_table[victim_page].frame = -1;
                    page_table[victim_page].referenced = 0;

                    RAM[victim_page] = strdup(disk[i]);
                    page_table[i].frame = victim_page;
                    page_table[i].valid = true;
                    page_table[i].referenced = 0;
                    num_loaded_pages++;

                    printf("Copy data from the disk (page=%d) to RAM (frame=%d)\n", i, victim_page);
                    printf("Page table\n");
                    for (int k = 0; k < num_pages; k++) {
                        printf("Page %d ---> valid=%d, frame=%d, dirty=%d, referenced=%d\n",
                               k, page_table[k].valid, page_table[k].frame,
                               page_table[k].dirty, page_table[k].referenced);
                    }
                    printf("-------------------------\n");

                    kill(page_table[i].referenced, SIGCONT);
                }
            }
        }
    }
    printf("%d disk accesses in total\n", disk_accesses);

    munmap(page_table, page_table_size);

    return 0;
}

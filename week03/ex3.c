#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 63
#define MAX_PATH_LENGTH 2048
#define MAX_FILE_DATA_SIZE 1024

struct File {
    unsigned int id;
    char name[MAX_FILENAME_LENGTH + 1];
    unsigned int size;
    char data[MAX_FILE_DATA_SIZE];
    struct Directory* directory;
};

struct Directory {
    char name[MAX_FILENAME_LENGTH + 1];
    struct File* files;
    struct Directory* directories;
    unsigned char nf;
    unsigned char nd;
    char path[MAX_PATH_LENGTH];
};

void overwrite_to_file(struct File *file, const char *str) {
    if (strlen(str) < MAX_FILE_DATA_SIZE) {
        strcpy(file->data, str);
        file->size = strlen(str) + 1;
    }
}

void append_to_file(struct File* file, const char* str) {
    size_t current_size = strlen(file->data);
    if (current_size + strlen(str) < MAX_FILE_DATA_SIZE) {
        strcat(file->data, str);
        file->size += strlen(str);
    }
}

void printp_file(struct File* file) {
    printf("%s%s\n", file->directory->path, file->name);
}

void add_file(struct File* file, struct Directory* dir) {
    if (dir->nf < 255) {
        dir->files[dir->nf++] = *file;
        file->directory = dir;
    }
}

int main() {

    struct Directory root ;
    root.nf = 0;
    root.nd = 0;
    strcpy(root.name, "/");
    strcpy(root.path, "/");
    root.files = (struct File *)(malloc(sizeof(struct File) * 255));
    root.directories = (struct Directory *)(malloc(sizeof(struct Directory) * 255));

    struct Directory home;
    strcpy(home.name, "home");
    strcpy(home.path, "/home/");
    home.nf = 0;
    home.nd = 0;
    home.files = (struct File *)(malloc(sizeof(struct File) * 255));
    home.directories = (struct Directory *)(malloc(sizeof(struct Directory) * 255));

    struct Directory bin ;
    strcpy(bin.name, "bin");
    strcpy(bin.path, "/bin/");
    bin.nf = 0;
    bin.nd = 0;
    bin.files = (struct File *)(malloc(sizeof(struct File) * 255));
    bin.directories = (struct Directory *)malloc(sizeof(struct Directory) * 255);

    struct File bash ;
    bash.id = 1;
    strcpy(bash.name, "bash");
    bash.size = 0;
    bash.directory = &bin;
    overwrite_to_file(&bash, "Bourne Again Shell!!");

    struct File ex3_1 ;
    ex3_1.id = 2;
    strcpy(ex3_1.name, "ex3 1.c");
    ex3_1.size = 0;
    ex3_1.directory = &home;
    strcpy(ex3_1.data, "int printf(const char * format, ...);");

    struct File ex3_2;
    ex3_2.id = 3;
    strcpy(ex3_2.name, "ex3 2.c");
    ex3_2.size = 0;
    ex3_2.directory = &home;
    strcpy(ex3_2.data, "//This is a comment in C language");

    append_to_file(&ex3_1, "int main(){printf(\"Hello World!\");}");

    add_file(&bash, &bin);
    add_file(&ex3_1, &home);
    add_file(&ex3_2, &home);

    printp_file(&bash);
    printp_file(&ex3_1);
    printp_file(&ex3_2);

    free(root.files);
    free(root.directories);
    free(home.files);
    free(home.directories);
    free(bin.files);
    free(bin.directories);

    return 0;
}

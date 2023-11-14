#include "stdio.h"
#include <unistd.h>
#include "string.h"
#include <stdlib.h>
#include "limits.h"
#include <signal.h>

#define BUFFER_SIZE 256
#define MAX_HLINKS_NUM 15

char* path;

char** find_all_hlinks(const char* source){
    char real_path[BUFFER_SIZE];
    if (realpath(source, real_path) == NULL) {
        perror("realpath");
        exit(EXIT_FAILURE);
    }

    char command[BUFFER_SIZE];
    sprintf(command, "find %s -samefile %s", path, real_path);

    FILE * fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    char** all_hlinks = malloc(sizeof(char*) * MAX_HLINKS_NUM);

    for (int i = 0; i < MAX_HLINKS_NUM; i++) {
        all_hlinks[i] = malloc(BUFFER_SIZE);
    }

    int i = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strncpy(all_hlinks[i], buffer, BUFFER_SIZE - 1);
        all_hlinks[i][BUFFER_SIZE - 1] = '\0'; 
        i++;
    }
    
    pclose(fp);
    return all_hlinks;
}

void unlink_all(const char *source){
    char ** all_hlinks = find_all_hlinks(source);
    char buffer[BUFFER_SIZE];

    for(int i = 0; i < MAX_HLINKS_NUM && all_hlinks[i] != NULL; i++){
        sprintf(buffer, "rm -rf %s", all_hlinks[i]);
        system(buffer);   
        free(all_hlinks[i]);
    }

    free(all_hlinks);
}

void create_sym_link(const char * source, const char * link){
    char command[BUFFER_SIZE];
    sprintf(command, "ln -s %s %s", source, link);
    system(command);
}

int main(int argc, char * argv[]){
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    path = argv[1];
    chdir(path);

    system("echo \"Hello, world!\" > myfile1.txt");

    system("ln myfile1.txt myfile11.txt");
    system("ln myfile1.txt myfile12.txt");

    char ** all_hlinks = find_all_hlinks("myfile1.txt");
    for(int i = 0; i < MAX_HLINKS_NUM && all_hlinks[i] != NULL; i++){
        printf("%s", all_hlinks[i]);
        free(all_hlinks[i]);
    }

    free(all_hlinks);

    system("mv myfile1.txt /tmp/myfile1.txt");
    system("echo \"hi wrld))))\" >> /tmp/myfile1.txt");

    create_sym_link("/tmp/myfile1.txt", "myfile13.txt");

    system("echo \"wrld))))\" >> /tmp/myfile1.txt");

    unlink_all("/tmp/myfile1.txt");

    all_hlinks = find_all_hlinks("/tmp/myfile1.txt");
    for(int i = 0; i < MAX_HLINKS_NUM && all_hlinks[i] != NULL; i++){
        printf("%s", all_hlinks[i]);
        free(all_hlinks[i]);
    }

    free(all_hlinks);

    return 0;
}

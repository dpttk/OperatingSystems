#include "sys/inotify.h"
#include "stdio.h"
#include <unistd.h>
#include "string.h"
#include <stdlib.h>
#include <signal.h>



#define EVENT_SIZE  (sizeof (struct inotify_event))
#define BUF_LEN     (16 * (EVENT_SIZE + 16))

char buffer [BUF_LEN];
int fd;
int wd;
char * path;

void sigint_handler(int sig){
    printf("\n");
    int len = read(fd, buffer, BUF_LEN);
    if (len == -1) {
        perror("read");
        close(fd);
        exit(1);
    }
    int i = 0;
    while(i < len){
        struct inotify_event *event;
        event = (struct inotify_event *) &buffer[i];

        if(event->mask & IN_ACCESS){
            printf("file %s has been accessed\n",event->name);
        }
        if(event->mask & IN_OPEN){
            printf("%s has been opened\n",event->name);
        }
        if(event->mask & IN_ATTRIB){
            printf("%s methadata has been changed\n",event->name);
        }
        if(event->mask & IN_MODIFY){
            printf("file %s has been modified\n",event->name);
        }
        if(event->mask & IN_DELETE){
            printf("file %s has been modified\n",event->name);
        }
        if(event->mask & IN_CREATE){
            printf("file %s has been modified\n",event->name);
        }

        i += EVENT_SIZE + event->len;
    }

    char command[100];
    snprintf(command, sizeof(command), "ls %s", path);
    system(command);
    close(fd);
    exit(0);
}

int main(int argc, char *argv[]){
    signal(SIGINT, sigint_handler);
    path = argv[1];
    char command[100];
    snprintf(command, sizeof(command), "ls %s", path);
    system(command);

    
    fd = inotify_init();
    if (fd == -1) {
        perror("inotify_init");
        return 1;
    }

    wd = inotify_add_watch(fd, path,IN_ALL_EVENTS);
    if (wd == -1) {
        perror("inotify_add_watch");
        close(fd);
        return 1;
    }

    while(1){}

    return 0;
}
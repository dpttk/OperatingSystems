#include <stdio.h>
#include <dirent.h>

int main(void) 
{ 
    struct dirent *der;
    DIR *dr = opendir("/"); 

    while ((der = readdir(dr)) != NULL) 
            printf("%s\n", der->d_name); 

    closedir(dr);     
    return 0; 
}

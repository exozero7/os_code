#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include "shared_memory.h"

int main(){

    int status;

    create_shared_memory(64);

    char parent[] = "I'm parent";
    char child[] = "I'm child";

    char* shmem = create_shared_memory(64);

    memcpy(shmem, parent, sizeof(parent));
    
    pid_t pid = fork();
    if (pid == 0){
        // sleep(1);
        printf("Child read: %s\n", shmem);

        // Copies sizeof(child) bytes in shmem
        memcpy(shmem, child, sizeof(child));
        
        printf("Child wrote: %s\n", shmem);
    }
    else{
        printf("Parent read: %s\n", shmem);
        // sleep(1);
        printf("Parent read after 1 sec: %s\n", shmem);
        
        /* Make sure the child process doesn't become orphan
         * Uncomment sleep() function on line 24 and play around
         */
        if ((pid = wait(&status)) == -1) {
            perror("wait() failed");
            exit(EXIT_FAILURE);
        }
        if (WIFEXITED(status)) {
            printf("Child terminated normally\n");
        }
    }

    return 0;
}
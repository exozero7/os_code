#include <stdlib.h>
#include <sys/mman.h>

void* create_shared_memory(size_t size){
    
    /*
     * PROT_READ    Pages may be read
     * PROT_WRITE   Pages may be written
     */
    int protection = PROT_READ | PROT_WRITE;
    
    /*
     * MAP_SHARED
     * Updates to the mapping are visible to other
     * processes mapping the same region
     * MAP_ANONYMOUS
     * The  mapping  is not backed by any file;
     * its contents are initialized to zero
     */
    int visibility = MAP_SHARED | MAP_ANONYMOUS;

    // For details check manpage of mmap
    return mmap(NULL, size, protection, visibility, -1, 0);
}
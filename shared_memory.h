#include <stdbool.h>

#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

char *attach_memory_block(char* filename, int size);
bool detach_memory_block(char* block);
bool destroy_memory_block(char* filename);

#define BLOCK_SIZE          4096
#define FILENAME            "write_sh_mem.c"

// filenames for two semaphores
#define SEM_PRODUCER_NAME   "/myproducer"
#define SEM_CONSUMER_NAME   "/myconsumer"

#endif
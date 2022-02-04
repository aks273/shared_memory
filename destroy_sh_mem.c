#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>

#include "shared_memory.h"


int main(int argc, char *argv[]) {
    if (argc != 1) {
        printf("Usage!");
        return -1;
    }

    if (destroy_memory_block(FILENAME)) {
        printf("Destroyed memory block %s\n", FILENAME);
    } else {
        printf("Could not destroy memory block %s\n", FILENAME);
    }

    return 0;
}
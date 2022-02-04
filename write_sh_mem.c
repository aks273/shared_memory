#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#include "shared_memory.h"

#define NUM_ITERATIONS  10

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage!\n");
        return -1;
    }

    // final argument of 0 means that the semaphore starts with a value of 0
    // we don't create a new semaphore here so it is important that the reader
    // is running when the writer starts
    sem_t *sem_prod = sem_open(SEM_PRODUCER_NAME, 0);
    if (sem_prod == SEM_FAILED) {
        perror("sem_open/producer");
        exit(EXIT_FAILURE);
    }

    // final argument of 1 means that the semaphore starts with a value of 1
    sem_t *sem_cons = sem_open(SEM_CONSUMER_NAME, 1);
    if (sem_cons == SEM_FAILED) {
        perror("sem_open/consumer");
        exit(EXIT_FAILURE);
    }

    // grab shared memory block
    char *block = attach_memory_block(FILENAME, BLOCK_SIZE);
    if (block == NULL) {
        printf("Error attaching memory block!");
        return -1;
    }

    if (strcmp(argv[1], "quit")) {
        for (int i = 0; i < NUM_ITERATIONS; i++) {
            sem_wait(sem_cons);
            printf("Writing: \"%s\"\n", argv[1]);
            strncpy(block, argv[1], BLOCK_SIZE);
            sem_post(sem_prod);
        }
    } else {
        // we need a special case to handle the "quit" message, because otherwise
        // the consumer semaphore will be waiting forever on the second iteration
        // (because the reader will never post to it after quitting)
        printf("Writing: \"%s\"\n", argv[1]);
        strncpy(block, argv[1], BLOCK_SIZE);
        sem_post(sem_prod);
    }

    sem_close(sem_prod);
    sem_close(sem_cons);

    detach_memory_block(block);

    return 0;
}
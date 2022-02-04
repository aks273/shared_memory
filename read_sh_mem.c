#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#include "shared_memory.h"

int main(int argc, char *argv[]) {
    if (argc != 1) {
        printf("Usage!");
        return -1;
    }

    sem_unlink(SEM_CONSUMER_NAME);
    sem_unlink(SEM_PRODUCER_NAME);

    // final argument of 0 means that the semaphore starts with a value of 0
    sem_t *sem_prod = sem_open(SEM_PRODUCER_NAME, O_CREAT, 0660, 0);
    if (sem_prod == SEM_FAILED) {
        perror("sem_open/producer");
        exit(EXIT_FAILURE);
    }

    // final argument of 1 means that the semaphore starts with a value of 1
    sem_t *sem_cons = sem_open(SEM_CONSUMER_NAME, O_CREAT, 0660, 1);
    if (sem_cons == SEM_FAILED) {
        perror("sem_open/consumer");
        exit(EXIT_FAILURE);
    }

    char *block = attach_memory_block(FILENAME, BLOCK_SIZE);
    if (block == NULL) {
        printf("Error attaching memory block!");
        return -1;
    }

    while (true) {
        sem_wait(sem_prod);
        if (strlen(block) > 0) {
            printf("Reading \"%s\"\n", block);

            // check if the user wants to quit, and reset the memory each time
            bool done = (strcmp(block, "quit") == 0);
            block[0] = 0;

            if (done)
                break;
        }
        sem_post(sem_cons);
    }

    sem_close(sem_prod);
    sem_close(sem_cons);

    detach_memory_block(block);

    return 0;
}
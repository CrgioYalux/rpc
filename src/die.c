#include "die.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

void die(void *ptr, const char *message) {
    free(ptr);

    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}


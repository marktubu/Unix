#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef struct 
{
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;
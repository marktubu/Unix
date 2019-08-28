#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    char* line = NULL;
    size_t len = 0;
    ssize_t nread;

    while((nread = getline(&line, &len, stdin)) != -1)
    {
        if(nread > 0)
        {
            line[nread-1] = 0;
            nread--;
        }
        printf("retrieved line of length %zu %s:\n", nread, line);
    }

    free(line);
    exit(EXIT_SUCCESS);
}


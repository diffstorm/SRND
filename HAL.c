#include "HAL.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>

bool HAL_FileExist(const char *filename)
{
    struct stat st;
    return (stat(filename, &st) == 0);
}

int HAL_FileRead(const char *filename, char *buf, size_t size)
{
    size_t len = 0;
    FILE *fp = fopen(filename, "r");

    if(fp != NULL)
    {
        len = fread(buf, sizeof(char), size, fp);

        if(ferror(fp) != 0 || len != size)
        {
            fprintf(stderr, "Error reading file %s: %s\n",
                    filename, strerror(errno));
        }
        else
        {
            buf[len++] = '\0'; /* Just to be safe */
        }

        fclose(fp);
    }

    return (int)len;
}

int HAL_FileWrite(const char *filename, char *buf, size_t size)
{
    size_t len = 0;
    FILE *fp = fopen(filename, "w");

    if(fp != NULL)
    {
        len = fwrite(buf, sizeof(char), size, fp);

        if(ferror(fp) != 0 || len != size)
        {
            fprintf(stderr, "Error writing into file %s: %s\n",
                    filename, strerror(errno));
        }

        fclose(fp);
    }

    return (int)len;
}

bool HAL_TRNG(char *UN, size_t size)
{
    FILE *fDriver = fopen("/dev/urandom", "r");

    if(NULL != fDriver)
    {
        fread(UN, 1, size, fDriver);
        fclose(fDriver);
    }
    else
    {
        fprintf(stderr, "Random Driver file error\n");
        return false;
    }

    return true;
}

unsigned long HAL_Tick()
{
    struct timespec now;

    if(clock_gettime(CLOCK_MONOTONIC, &now))
    {
        return 0;
    }

    return (unsigned long)((now.tv_sec * 1000000) + (now.tv_nsec / 1000));
}

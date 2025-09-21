#include "z11lib.h"
#include <stdio.h>

int main(int ac, char **av)
{

    char **arr = split_11("hello-world-nigga", '-');

    int i = 0;
    while(i < 3)
    {
        putstr(arr[i]);
        write(1, "\n", 1);
        i++;
    }

    if (ac < 2)
    {
        putstr("No arguments.");
        return 1;
    }
    if (strncmp(av[1], "--", 2) == 0)
    {
        // GAVE AN ARGUMENT
        if (strcmp(av[1], "--help") == 0)
        {
            display_help();
            return 0;
        }

        if (strcmp(av[1], "--11") == 0)
        {
            if (ac < 3)
            {
                putstr("No Files to compress.");
                return 3;
            }
            compress_file(av[2]);
            return 0;
        }

        if (strcmp(av[1], "--12") == 0)
        {
            if (ac < 3)
            {
                putstr("No Files to decompress.");
                return 4;
            }
            decompress_file(av[2]);
            return 0;
        }

        display_help();
        return 0;
    }
    else 
    {
        putstr("No valid arguements.");
        return 2;
    }
}
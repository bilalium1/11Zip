#ifndef Z11_LIB
#define Z11_LIB

#include <stdio.h> //
#include <fcntl.h> // file flags
#include <unistd.h> //
#include <string.h> // this library is used to manipulate strings
#include <stdlib.h> // malloc()
#include <dirent.h> // this library is used to read directories
#include <sys/stat.h> // this library is used to get file metadata

typedef struct linked11
{
    char type;
    void *content;
    struct linked11 *next;
} link11;

void    display_help();
void    putstr(char *str);
void    display_list(link11 *head);
int     compress_file(const char* file_path);
int     decompress_file(const char* file_path);
int     parse(int ac, char **av, link11 **files);
char**  split_11(char* buffer, const char delim);


#endif
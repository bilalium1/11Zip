#ifndef Z11_LIB
#define Z11_LIB

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void    putstr(char *str);
void    display_help();
char**  split_11(char* buffer, const char delim);
int     compress_file(const char* file_path);
int     decompress_file(const char* file_path);


#endif
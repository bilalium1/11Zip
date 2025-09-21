#include "z11lib.h"
#include <stdio.h>

void putstr(char *str)
{
    int i = 0;
    while (str[i])
        write(1, &str[i++], 1);
}

void display_help()
{
    int help_fd = open("help.txt", O_RDONLY);

    char buffer[1025];
    ssize_t bytes_read = read(help_fd, buffer, sizeof(buffer));
    buffer[bytes_read] = '\0';
    write(1, "\n\n", 2);
    putstr(buffer);
    write(1, "\n\n", 2);

    close(help_fd);
}

int count_words(char* buffer, const char delim)
{
    int i = 0;
    int words = 0;
    int new_word = 0;

    while (buffer[i])
    {
        if (buffer[i] != delim && !new_word)
        {
            new_word = 1; words++;
        }

        if (buffer[i] == delim && new_word)
        {
            new_word = 0;
        }
        i++;
    }
    return words;
}

char * get_word(char* buffer,const char delim, int index)
{
    int i = 0;
    int j = 0;
    int in = 0;

    while (buffer[i])
    {
        if (buffer[i] == delim)
        {
            if (in == index)
            {
                char *res = (char* )malloc((i - j + 1) * sizeof(char));
                strncpy(res, &buffer[j], i - j);
                res[i - j] = '\0';

                return res;
            }
            else
            {
                j = i + 1;
                in++;
            }
        }
        i++;
    }

    if (in > 0)
    {
        char *res = (char* )malloc((i - j + 1) * sizeof(char));
        strncpy(res, &buffer[j], i - j);
        res[i - j] = '\0';

        return res;
    }
    else
        return buffer;
}

char**  split_11(char* buffer, const char delim)
{
    int words = count_words(buffer, delim);
    
    char **arr = (char**)malloc(words * sizeof(char*));

    int i = 0;
    while (i < words)
    {
        arr[i] = get_word(buffer, delim, i);
        i++;
    }

    return arr;

}

int compress_file(const char *file_path)
{
    int src_fd = open(file_path, O_RDONLY);
    int cmp_fd = open("comp.z11", O_WRONLY | O_CREAT, 0644);

    char buffer[1025];
    ssize_t bytes = read(src_fd, buffer, sizeof(buffer));
    buffer[bytes] = '\0';

    write(cmp_fd, file_path, strlen(file_path));
    write(cmp_fd, "\x01", 1);
    write(cmp_fd, buffer, bytes);

    close(src_fd);
    close(cmp_fd);

    unlink(file_path);
}

int decompress_file(const char *file_path)
{
    int cmp_fd = open(file_path, O_RDONLY);

    char buffer[1025];
    ssize_t bytes = read(cmp_fd, buffer, sizeof(buffer));
    buffer[bytes] = '\0';

    char **s = split_11(buffer, 1);
    char *file_name = s[0];
    char *data = s[1];
    int dst_fd = open(file_name, O_WRONLY | O_CREAT, 0644);
    write(dst_fd, data, strlen(data));

    close(dst_fd);
    close(cmp_fd);

    unlink(file_path);
}

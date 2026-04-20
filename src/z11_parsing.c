// B11
#include "z11lib.h"

void add_to_end(link11 **head, link11 *new)
{
    if (!head || !new)
        return ;
    else if (!*head)
        *head = new;
    else
    {
        link11 *tmp = *head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

void free_list(link11 *head)
{
    link11 *tmp;
    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void add_directory(link11 **head, char *dir_path)
{
    DIR *dir = opendir(dir_path);
    struct dirent *entry;
    link11 *new_dir = malloc(sizeof(link11));
    new_dir->next = NULL;
    new_dir->type = 'd';
    while ((entry = readdir(dir)) != NULL)
    {
        // skip current and parrent 
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        continue;
        
        // make full path of file
        char *entry_path = malloc(strlen(dir_path) + strlen(entry->d_name) + 2);
        sprintf(entry_path, "%s/%s", dir_path, entry->d_name);
        
        struct stat st;
        
        if(stat(entry_path, &st) == -1)
        {
            perror("stat");
            return;
        }
        
        if (S_ISDIR(st.st_mode))
        add_directory(&new_dir, entry_path);
        else if (S_ISREG(st.st_mode))
        // add file to the list
        link11 *new_file = malloc(sizeof(link11));
        new_file->next = NULL;
        new_file->content = entry_path;
        new_file->type = 'f';
        add_to_end(&new_dir, new_file);
    }
    new_dir->content = ;
    closedir(dir);
    add_to_end(head, new_dir);
}

int parse(int ac, char **av, link11 **head_files)
{
    // assuming av starts after the "--11" argument
    // ac is (ac - 2) : excluding the program and argument
    int i = 0;

    struct stat st;

    while(i < ac)
    {
        char *file_path = av[i];

        if(stat(file_path, &st) == -1)
        {
            perror("stat");
            return 1;
        }

        if (S_ISREG(st.st_mode))
        {
            // regular file
            link11 *new_file = malloc(sizeof(link11));
            new_file->next = NULL;
            new_file->type = 'f';
            new_file->content = file_path;
            add_to_end(head_files, new_file);
        }
        else if (S_ISDIR(st.st_mode))
        {
            // directory
            // we can use opendir and readdir to read the directory contents
            add_directory(head_files, file_path);
        }
        i++;
    }
}

void display_list(link11 *head)
{
    char *buffer = malloc(1024);
    buffer[0] = '\0';
    link11 *current = head;
    while (current)
    {
        strcat(buffer, current->content);
        strcat(buffer, "\n");
        current = current->next;
    }
    putstr(buffer);
    free(buffer);
}
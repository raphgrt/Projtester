/*
** EPITECH PROJECT, 2024
** Projtester
** File description:
** btf.c
*/

#include "../../include/projtester.h"

static char *get_path_line(char **env)
{
    char *path = NULL;

    for (int i = 0; env[i]; i++) {
        if (strncmp(env[i], "PATH=", 5) == 0) {
            path = strdup(env[i] + 5);
            break;
        }
    }
    if (!path) {
        perror("No path env !\n");
        exit(84);
    }
    return (path);
}

static char *find_in_current_dir(char *command)
{
    char *pathname;

    if (access(command, X_OK) == 0) {
        pathname = strdup(command);
        return (pathname);
    }
    return (NULL);
}

char *find_command(char *command, char **env)
{
    char *str_path;
    char **cmd_array;
    char *pathname;

    if (find_in_current_dir(command))
        return (strdup(command));
    if (!command || !env)
        return (NULL);
    str_path = get_path_line(env);
    cmd_array = my_str_to_word_array(str_path);
    for (int i = 0; cmd_array[i]; i++) {
        pathname = strcat(strcat(strdup(cmd_array[i]), "/"), command);
        if (access(pathname, X_OK) == 0) {
            free(str_path);
            return (pathname);
        }
        free(pathname);
    }
    return (NULL);
}

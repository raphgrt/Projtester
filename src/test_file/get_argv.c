/*
** EPITECH PROJECT, 2024
** Projtester
** File description:
** get_argv.c
*/

#include "../../include/projtester.h"

static int count_space(char *str)
{
    int count = 0;

    if (!str)
        return (0);
    for (int i = 0; str[i]; i++)
        if (str[i] == ' ')
            count++;
    return (count);
}

char **gen_argv(char *bin_name, char *args)
{
    char **argv;
    int nb_args = count_space(args) + 2;

    if (!bin_name || !args)
        return (NULL);
    argv = malloc(sizeof(char *) * (nb_args + 2));
    if (!argv)
        return (NULL);
    argv[0] = strdup(bin_name);
    argv[nb_args] = NULL;
    if (nb_args == 2)
        return (argv);
    for (int i = 1; i < nb_args; i++) {
        if (i == 1) {
            argv[i] = strdup(strtok(args, " "));
            continue;
        }
        argv[i] = strdup(strtok(NULL, " "));
    }
    return (argv);
}

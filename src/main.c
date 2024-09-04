/*
** EPITECH PROJECT, 2024
** Projtester
** File description:
** main.c
*/

#include "../include/projtester.h"

static void get_flags(option_t *opts, int ac, char **av)
{
    opts->trd = av[1];
    opts->bft = NULL;
    opts->outputfile = NULL;
    if (ac >= 3)
        opts->bft = av[2];
    if (ac == 4)
        opts->outputfile = av[3];
}

static char *get_filename(char *pathname)
{
    int i = strlen(pathname) - 1;

    while (i >= 0 && pathname[i] != '/')
        i--;
    return (&pathname[i + 1]);
}

static void helper(void)
{
    FILE *fd = fopen(HELPER_PATH, "r");
    char file[HELPER_LEN];

    if (!fd)
        exit(84);
    fread(file, HELPER_LEN, 1, fd);
    printf("%s", file);
    fclose(fd);
}

static void my_tree(projtester_t *projtester, int ac)
{
    char *filename;

    if (access(projtester->opts.trd, F_OK) == -1)
        exit(84);
    filename = get_filename(projtester->opts.trd);
    projtester->tree = get_tree(projtester->opts.trd, filename);
    sort_tree(&projtester->tree);
    if (ac == 2)
        print_tree(projtester->tree);
}

int main(int argc, char **argv, char **envp)
{
    projtester_t projtester;
    char *filename;

    if (argc == 1) {
        helper();
        return (84);
    }
    if (argc < 2 || argc > 4)
        return (84);
    get_flags(&projtester.opts, argc, argv);
    my_tree(&projtester, argc);
    if (argc >= 3)
        return (exec_test(projtester.tree, &projtester.opts, envp));
    return (0);
}

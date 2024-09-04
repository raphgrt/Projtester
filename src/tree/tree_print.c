/*
** EPITECH PROJECT, 2024
** Projtester
** File description:
** print_tree.c
*/

#include "../../include/projtester.h"

static void print_indentation(int depth)
{
    for (int i = 0; i < depth; i++)
        printf("-----");
}

static void print_file(char *file, int depth)
{
    print_indentation(depth + 1);
    printf("%s\n", file);
}

static int count_depth(char *pathname)
{
    int depth = 0;

    for (int i = 0; pathname[i]; i++)
        if (pathname[i] == '/')
            depth++;
    return (depth - 2);
}

static void print_folder(tree_t *tree)
{
    tree_t *tmp = tree;
    int depth = 0;

    for (; tmp; tmp = tmp->next) {
        depth = count_depth(tmp->pathname);
        print_file(tmp->name, depth);
    }
}

void print_tree(tree_t *tree)
{
    print_folder(tree);
}

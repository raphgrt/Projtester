/*
** EPITECH PROJECT, 2024
** Projtester
** File description:
** tree.c
*/

#include "../../include/projtester.h"

char *get_new_pathlink(char *str1, char *str2)
{
    char *new_str = malloc(sizeof(char) * (strlen(str1) + strlen(str2) + 2));

    if (new_str == NULL)
        return (NULL);
    strcpy(new_str, str1);
    strcat(new_str, "/");
    strcat(new_str, str2);
    return (new_str);
}

static tree_t *create_node(char *pathname, char *name, int is_folder)
{
    tree_t *new_node = malloc(sizeof(tree_t));

    if (new_node == NULL)
        return (NULL);
    new_node->name = strdup(name);
    new_node->pathname = strdup(pathname);
    new_node->is_folder = is_folder;
    new_node->next = NULL;
    return (new_node);
}

void add_node(tree_t **root, char *pathname, char *name, int is_folder)
{
    tree_t *tmp = *root;
    tree_t *new_node = create_node(pathname, name, is_folder);

    if (!new_node)
        return;
    if (!tmp) {
        *root = new_node;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
}

static void tree_handler(tree_t **node, char *pathname, char *name)
{
    DIR *dp = opendir(pathname);
    char *new_path = NULL;

    if (!dp || !pathname || !name)
        return;
    for (struct dirent *dir = readdir(dp); dir; dir = readdir(dp)) {
        if (dir->d_name[0] == '.')
            continue;
        new_path = get_new_pathlink(pathname, dir->d_name);
        if (dir->d_type != DT_DIR) {
            add_node(node, new_path, dir->d_name, 0);
        }
        if (dir->d_type == DT_DIR) {
            add_node(node, new_path, dir->d_name, 1);
            tree_handler(node, new_path, dir->d_name);
        }
    }
}

tree_t *get_tree(char *pathname, char *name)
{
    tree_t *new_tree = NULL;

    add_node(&new_tree, pathname, name, 1);
    tree_handler(&new_tree, pathname, name);
    return (new_tree);
}

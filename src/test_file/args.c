/*
** EPITECH PROJECT, 2024
** Projtester
** File description:
** args.c
*/

#include "../../include/projtester.h"

static char *read_file(char *pathname)
{
    struct stat st;
    char *content;
    int fd;

    if (stat(pathname, &st) == -1)
        return (NULL);
    content = malloc(sizeof(char) * (st.st_size + 1));
    if (!content)
        return (NULL);
    fd = open(pathname, O_RDONLY);
    if (fd == -1)
        return (NULL);
    read(fd, content, st.st_size);
    content[st.st_size] = '\0';
    close(fd);
    return (content);
}

static void get_args(file_t *current, char *content)
{
    char **tab = my_str_to_word_array_sep(content, '\n');
    size_t str_len = 0;

    if (!tab)
        return;
    for (int x = 0; tab[x]; x++) {
        str_len = strlen(tab[x]);
        if (str_len >= 5 && strncmp(ARGUMENTS, tab[x], 5) == 0) {
            current->args = &tab[x][5];
            continue;
        }
        if (str_len >= 6 && strncmp(INPUT, tab[x], 6) == 0) {
            current->input = &tab[x][6];
            continue;
        }
        if (str_len >= 3 && strncmp(RES, tab[x], 3) == 0)
            current->res = &tab[x][4];
    }
}

static file_t *create_file(char *name, char *pathname)
{
    file_t *file = malloc(sizeof(file_t));

    if (!file)
        return (NULL);
    file->name = name;
    file->pathname = pathname;
    file->content = read_file(pathname);
    file->args = NULL;
    file->input = NULL;
    file->res = NULL;
    file->output = NULL;
    file->next = NULL;
    if (file->content)
        get_args(file, file->content);
    return (file);
}

void add_file(file_t **file, char *name, char *pathname)
{
    file_t *new_file = create_file(name, pathname);
    file_t *tmp = *file;

    if (!new_file)
        return;
    if (*file == NULL) {
        *file = new_file;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_file;
}

static int is_tdf_file(char *filename)
{
    int len;

    if (!filename)
        return (0);
    len = strlen(filename);
    if (len < 4)
        return (0);
    if (strncmp(&filename[len - 4], ".tdf\0", 4) == 0)
        return (1);
    return (0);
}

void fill_content(tree_t *tree, file_t **file)
{
    for (tree_t *tmp = tree; tmp; tmp = tmp->next) {
        if (tmp->is_folder == 0 && is_tdf_file(tmp->name))
            add_file(file, tmp->name, tmp->pathname);
    }
}

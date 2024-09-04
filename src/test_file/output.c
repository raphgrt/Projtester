/*
** EPITECH PROJECT, 2024
** Projtester
** File description:
** output.c
*/

#include "../../include/projtester.h"

static int create_file(char *filepath)
{
    int fd;

    if (access(filepath, F_OK) == -1)
        fd = open(filepath, O_CREAT | O_WRONLY, 0644);
    else
        fd = open(filepath, O_WRONLY | O_APPEND);
    return (fd);
}

void printer(file_t *tmp, int fd)
{
    write(fd, tmp->name, strlen(tmp->name) - 4);
    write(fd, ":", 1);
    if (tmp->output == NULL || tmp->output[0] == 10)
        write(fd, "\n", 1);
    else {
        write(fd, " ", 1);
        write(fd, tmp->output, strlen(tmp->output));
    }
}

int output(file_t *file, char *outputfile)
{
    int fd = create_file(outputfile);

    if (fd == -1)
        return (84);
    for (file_t *tmp = file; tmp; tmp = tmp->next) {
        if (tmp->output == NULL)
            continue;
        print_path(tmp->pathname, fd);
        if (tmp->res) {
            print_ok_ko(tmp->output, tmp->res, tmp->name, fd);
            continue;
        }
        printer(tmp, fd);
    }
    close(fd);
    return (0);
}

/*
** EPITECH PROJECT, 2024
** Projtester
** File description:
** print_test.c
*/

#include "../../include/projtester.h"

static void split_list(file_t *head, file_t **first_half, file_t **second_half)
{
    file_t *fast;
    file_t *slow;

    slow = head;
    fast = head->next;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *first_half = head;
    *second_half = slow->next;
    slow->next = NULL;
}

static file_t *merge_lists(file_t *first_half, file_t *second_half)
{
    file_t *result = NULL;

    if (first_half == NULL)
        return (second_half);
    else if (second_half == NULL)
        return (first_half);
    if (strcmp(first_half->pathname, second_half->pathname) <= 0) {
        result = first_half;
        result->next = merge_lists(first_half->next, second_half);
    } else {
        result = second_half;
        result->next = merge_lists(first_half, second_half->next);
    }
    return (result);
}

void merge_sort(file_t **head_ref)
{
    file_t *head = *head_ref;
    file_t *first_half;
    file_t *second_half;

    if ((head == NULL) || (head->next == NULL))
        return;
    split_list(head, &first_half, &second_half);
    merge_sort(&first_half);
    merge_sort(&second_half);
    *head_ref = merge_lists(first_half, second_half);
}

void print_path(char *path, int fd)
{
    char **tab = my_str_to_word_array_sep(path, '/');

    for (int i = 2; tab[i + 1]; i++) {
        write(fd, "[", 1);
        write(fd, tab[i], strlen(tab[i]));
        write(fd, "] ", 2);
    }
}

void print_ok_ko(char *returned, char *needed, char *name, int fd)
{
    if (strncmp(returned, needed, strlen(needed)) == 0) {
        write(fd, name, strlen(name) - 4);
        write(fd, ": OK\n", 5);
        return;
    }
    write(fd, name, strlen(name) - 4);
    write(fd, ": KO\n", 5);
}

int print_path_result(file_t **node)
{
    for (file_t *tmp = *node; tmp; tmp = tmp->next) {
        print_path(tmp->pathname, 1);
        if (tmp->res) {
            print_ok_ko(tmp->output, tmp->res, tmp->name, 1);
            continue;
        }
        printer(tmp, 1);
    }
    return (0);
}

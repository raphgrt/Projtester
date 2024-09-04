/*
** EPITECH PROJECT, 2024
** Projtester
** File description:
** tree_sort.c
*/

#include "../../include/projtester.h"

static void split_list(tree_t *head, tree_t **first_half, tree_t **second_half)
{
    tree_t *fast;
    tree_t *slow;

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

static tree_t *merge_lists(tree_t *first_half, tree_t *second_half)
{
    tree_t *result = NULL;

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

void sort_tree(tree_t **head_ref)
{
    tree_t *head = *head_ref;
    tree_t *first_half;
    tree_t *second_half;

    if ((head == NULL) || (head->next == NULL))
        return;
    split_list(head, &first_half, &second_half);
    sort_tree(&first_half);
    sort_tree(&second_half);
    *head_ref = merge_lists(first_half, second_half);
}

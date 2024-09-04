/*
** EPITECH PROJECT, 2024
** Projtester
** File description:
** my_puterr.c
*/

#include "../include/projtester.h"

void my_puterr(const char *str)
{
    write(2, str, strlen(str));
}

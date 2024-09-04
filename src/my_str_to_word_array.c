/*
** EPITECH PROJECT, 2024
** Projtester
** File description:
** my_str_to_word_array.c
*/

#include "../include/projtester.h"


static int my_char_issep(char c)
{
    if (c == ':' || c == '\t' || c == '\n')
        return (1);
    return (0);
}

int str_count_words_char(char const *str, const char sep)
{
    int res = 0;
    int x;

    for (x = 0; str[x] && str[x + 1]; x++)
        if (str[x] == sep && (str[x + 1]) != sep)
            res++;
    if (str[x] != sep)
        res++;
    return (res);
}

static int str_count_words_fn(char const *str, int (*is_separator)(char))
{
    int res = 0;
    int x;

    for (x = 0; str[x] && str[x + 1]; x++)
        if (is_separator(str[x]) && !is_separator(str[x + 1]))
            res++;
    if (!is_separator(str[x]))
        res++;
    return (res);
}

char **my_str_to_word_array(char const *str)
{
    int j = 0;
    int len = 0;
    int nb_words = str_count_words_fn(str, &my_char_issep);
    char **tmp = malloc(sizeof(char *) * nb_words + 1);

    for (int i = 0; str[i]; i++) {
        if (!my_char_issep(str[i]))
            len++;
        if (my_char_issep(str[i]) == 0 && my_char_issep(str[i + 1]) == 1) {
            tmp[j] = malloc(len + 2);
            tmp[j] = strncpy(tmp[j], &str[(i + 1) - len], len);
            tmp[j][len] = '\0';
            len = 0;
            j++;
        }
    }
    tmp[nb_words] = NULL;
    return (tmp);
}

char **my_str_to_word_array_sep(const char *str, const char sep)
{
    int j = 0;
    int len = 0;
    int nb_words = str_count_words_char(str, sep);
    char **tmp = malloc(sizeof(char *) * nb_words + 1);

    for (int i = 0; str[i]; i++) {
        if (str[i] != sep)
            len++;
        if (str[i] != sep && (str[i + 1] == sep || !str[i + 1])) {
            tmp[j] = malloc(len + 2);
            strncpy(tmp[j], &str[(i + 1) - len], len);
            tmp[j][len] = '\0';
            len = 0;
            j++;
        }
    }
    tmp[nb_words] = NULL;
    return (tmp);
}

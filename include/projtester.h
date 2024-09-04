/*
** EPITECH PROJECT, 2024
** Projtester
** File description:
** projtester.h
*/

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef PROJTESTER_H_
    #define PROJTESTER_H_
    #define HELPER_PATH "./helper.txt"
    #define HELPER_LEN 215
    #define ARGUMENTS "ARGS:"
    #define INPUT "INPUT:"
    #define RES "RES:"

typedef struct type_counter_s {
    int files;
    int folders;
} type_counter_t;

typedef struct file_s {
    char *name;
    char *pathname;
    char *content;
    char *args;
    char *input;
    char *res;
    char *output;
    struct file_s *next;
} file_t;

typedef struct tree_s {
    char *name;
    char *pathname;
    int is_folder;
    struct tree_s *next;
} tree_t;

typedef struct option_s {
    char *trd;
    char *bft;
    char *outputfile;
} option_t;

typedef struct projtester_s {
    option_t opts;
    tree_t *tree;
} projtester_t;

void free_tree(tree_t *tree);
tree_t *get_tree(char *pathname, char *name);
int exec_test(tree_t *tree, option_t *opts, char **envp);

char *find_command(char *command, char **env);
void print_tree(tree_t *tree);
void sort_tree(tree_t **root);
char **my_str_to_word_array_sep(const char *str, const char sep);
char **my_str_to_word_array(char const *str);
void my_puterr(const char *str);
void fill_content(tree_t *tree, file_t **file);
char **gen_argv(char *bin_name, char *args);
int print_path_result(file_t **node);
void merge_sort(file_t **head_ref);
int output(file_t *file, char *outputfile);
void print_path(char *path, int fd);
void print_ok_ko(char *returned, char *needed, char *name, int fd);
void printer(file_t *tmp, int fd);
#endif /* !PROJTESTER_H_ */

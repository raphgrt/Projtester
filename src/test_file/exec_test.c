/*
** EPITECH PROJECT, 2024
** Projtester
** File description:
** exec_test.c
*/

#include "../../include/projtester.h"

static void create_pipe(int pipefd[2])
{
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
}

static pid_t create_child_process(void)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    return (pid);
}

static void redirect_stdout(int pipefd[2])
{
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
}

static void redirect_stdin(int pipefd[2], char *input)
{
    write(pipefd[1], input, strlen(input));
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
}

static void execute_command(char *path, char **argv)
{
    execv(path, argv);
    _exit(EXIT_FAILURE);
}

static char *read_from_pipe(int pipefd[2])
{
    char buf;
    char *output = malloc(256);
    int index = 0;

    close(pipefd[1]);
    while (read(pipefd[0], &buf, 1) > 0) {
        output[index] = buf;
        index++;
    }
    output[index] = '\0';
    close(pipefd[0]);
    wait(NULL);
    return (output);
}

char *exec_cmd_and_get_output(char *path, char **argv, char *input)
{
    int pipefd[2];
    pid_t pid;
    int input_pipe[2];

    create_pipe(pipefd);
    pid = create_child_process();
    if (pid == 0) {
        redirect_stdout(pipefd);
        if (input) {
            create_pipe(input_pipe);
            redirect_stdin(input_pipe, input);
        }
        execute_command(path, argv);
    } else {
        return (read_from_pipe(pipefd));
    }
    return (NULL);
}

int exec_test(tree_t *tree, option_t *opts, char **envp)
{
    char *cmd_path = find_command(opts->bft, envp);
    file_t *file = NULL;
    char **argv = NULL;

    if (!cmd_path) {
        my_puterr("Command not found\n");
        return (84);
    }
    fill_content(tree, &file);
    for (file_t *tmp = file; tmp; tmp = tmp->next) {
        argv = gen_argv(cmd_path, tmp->args);
        tmp->output = exec_cmd_and_get_output(cmd_path, argv, tmp->input);
    }
    merge_sort(&file);
    if (opts->outputfile == NULL) {
        return (print_path_result(&file));
    }
    return (output(file, opts->outputfile));
}

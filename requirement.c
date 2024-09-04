/*
** EPITECH PROJECT, 2024
** Projtester
** File description:
** requirement.c
*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

void my_ps_synthesis(void)
{
    pid_t pid;
    int exit_status;
    char *args[] = {"ps", "aux", NULL};

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(84);
    }
    if (pid == 0) {
        exit_status = execv("/bin/ps", args);
        if (exit_status < 0) {
            perror("execv");
            exit(84);
        }
    } else {
        waitpid(pid, &exit_status, 0);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define ARGUMENTS_SIZE 64

char *get_command_path(char *command)
{
    char *path = getenv("PATH");
    char *token = strtok(path, ":");

    while (token != NULL)
    {
        char *command_path = malloc(strlen(token) + strlen(command) + 2);
        snprintf(command_path, strlen(token) + strlen(command) + 2, "%s/%s", token, command);

        if (access(command_path, F_OK) == 0)
        {
            return command_path;
        }

        free(command_path);

        token = strtok(NULL, ":");
    }

    return NULL;
}

int project3_main(void)
{
    char buffer[BUFFER_SIZE];
    int status;
    pid_t pid;
    char *command;
    char *arguments[ARGUMENTS_SIZE];
    int argument_count;
    char *command_path;

    while (1)
    {
        printf("$ ");
        fflush(stdout);

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
        {
            printf("\n");
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        command = strtok(buffer, " ");

        argument_count = 0;

        while (command != NULL)
        {
            arguments[argument_count] = command;
            argument_count++;
            command = strtok(NULL, " ");
        }

        arguments[argument_count] = NULL;

        if (argument_count == 0)
        {
            continue;
        }

        command_path = get_command_path(arguments[0]);

        if (command_path == NULL)
        {
            printf("Command not found: %s\n", arguments[0]);
            continue;
        }

        pid = fork();

        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            /* Child process */
            if (execv(command_path, arguments) == -1)
            {
                perror("execv");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            /* Parent process */
            waitpid(pid, &status, 0);
        }

        free(command_path);
    }

    return 0;
}

int my_main(void)
{
    return project3_main();
}

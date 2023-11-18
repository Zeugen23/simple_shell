#define _POSIX_SOURCE

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PATH "/bin:/usr/bin"

/**
 * Executes the specified command with the given arguments.
 * @param filename The path to the command executable.
 * @param args The arguments for the command.
 */
void execute_command(const char *filename, char *args[])
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0)
    {
        execv(filename, args);
        perror("execv failed");
        exit(127);
    }
    else
    {
        wait(NULL);
    }
}

/**
 * Prints the current environment.
 */
void print_environment(void)
{
    extern char **environ;
    char **env = environ;

    while (*env != NULL)
    {
        printf("%s\n", *env);
        env++;
    }
}

int my_program(void) /* Renamed the main function to my_program */
{
    char *path = PATH;
    char *command;
    char *args[100];
    char buffer[1024];

    int arg_index = 0; /* Move the declaration here */
    char filename[1024]; /* Declare filename outside if-else block */

    while (1)
    {
        printf("shell> ");

        fgets(buffer, 1024, stdin);

        command = strtok(buffer, " ");
        arg_index = 0; /* Reset arg_index for each iteration */

        while ((args[arg_index] = strtok(NULL, " ")) != NULL)
        {
            arg_index++;
        }
        args[arg_index] = NULL;

        if (strcmp(command, "env\n") == 0)
        {
            print_environment();
        }
        else
        {
            int found = 0;
            char *next_dir;
            next_dir = strtok(path, ":");

            while (next_dir != NULL)
            {
                strcpy(filename, next_dir);
                strcat(filename, "/");
                strcat(filename, command);

                if (access(filename, X_OK) != -1)
                {
                    found = 1;
                    break;
                }

                next_dir = strtok(NULL, ":");
            }

            if (found == 0)
            {
                printf("Command not found\n");
            }
            else
            {
                execute_command(filename, args);
            }
        }
    }

    return 0;
}

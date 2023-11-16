#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

void display_prompt(void)
{
    printf("Enter a command: ");
    fflush(stdout);
}

void execute_command(const char *command)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Error occurred during forking");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        /* Child process */
        if (execlp(command, command, NULL) == -1)
        {
            perror("Error executing command");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        /* Parent process */
        int status;
        waitpid(pid, &status, 0);
    }
}

int main(void)
{
    char command[MAX_COMMAND_LENGTH];

    while (true)
    {
        display_prompt();

        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            /* Check for end of file (Ctrl+D) or error */
            break;
        }

        /* Remove the newline character at the end of the command */
        command[strcspn(command, "\n")] = '\0';

        execute_command(command);
    }

    return 0;
}

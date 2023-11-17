#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(void)
{
    char command[BUFFER_SIZE];

    while (1)
    {
        printf("$ "); /* Display the prompt */
        fflush(stdout); /* Ensure the prompt is displayed */

        if (fgets(command, BUFFER_SIZE, stdin) == NULL)
        {
            /* Handle end of file (Ctrl+D) */
            printf("\n");
            break;
        }

        /* Remove the newline character from the input */
        command[strcspn(command, "\n")] = '\0';

        pid_t pid = fork();

        if (pid < 0)
        {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            /* Child process */

            /* Execute the command */
            int status = execlp(command, command, NULL);

            if (status == -1)
            {
                fprintf(stderr, "Command not found\n");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            /* Parent process */
            int child_status;
            waitpid(pid, &child_status, 0);
        }
    }

    return 0;
}

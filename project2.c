#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define ARGUMENTS_SIZE 64

int main2(void) {
    char buffer[BUFFER_SIZE];
    int status;
    pid_t pid;
    char* command;
    char* arguments[ARGUMENTS_SIZE];
    int argument_count;

    while (1) {
        printf("$ ");
        fflush(stdout);

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            printf("\n");
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0'; /* Remove trailing newline character */

        command = strtok(buffer, " "); /* Split command line by space delimiter */

        argument_count = 0;

        while (command != NULL) {
            arguments[argument_count] = command;
            argument_count++;
            command = strtok(NULL, " ");
        }

        arguments[argument_count] = NULL; /* Set the last element to NULL as required by exec family functions */

        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            /* Child process */
            if (execvp(arguments[0], arguments) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        } else {
            /* Parent process */
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}

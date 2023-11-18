#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

int project1_main(void) {
    char buffer[BUFFER_SIZE];
    int status;
    pid_t pid;

    while (1) {
        printf("$ ");
        fflush(stdout);

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            printf("\n");
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0'; /* Remove trailing newline character */

        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            /* Child process */
            if (execlp(buffer, buffer, NULL) == -1) {
                perror("execlp");
                exit(EXIT_FAILURE);
            }
        } else {
            /* Parent process */
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}

int main(void) {
    return project1_main();
}

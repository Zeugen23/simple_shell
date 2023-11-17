#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(void) {
    char command[BUFFER_SIZE];
    int exit_flag = 0;

    while (!exit_flag) {
        printf("$ "); // Display the prompt
        fflush(stdout); // Ensure the prompt is displayed

        if (fgets(command, BUFFER_SIZE, stdin) == NULL) {
            // Handle end of file (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove the newline character from the input
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0) {
            // Exit the shell if the user inputs "exit"
            exit_flag = 1;
        } else {
            // Execute the command
            int status = system(command);

            if (status == -1) {
                printf("Error executing command\n");
            }
        }
    }

    return 0;
}

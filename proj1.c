#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

/**
 * main - The main function of the program.
 *        It implements a simple shell that takes user commands and executes them.
 *
 * Return: Always 0.
 */
int main(void)
{
	int exit_flag = 0;
	char command[BUFFER_SIZE];

	while (!exit_flag)
	{
		printf("$\n"); /* Display the prompt */
		fflush(stdout); /* Ensure the prompt is displayed */

		if (fgets(command, BUFFER_SIZE, stdin) == NULL)
		{
			/* Handle end of file (Ctrl+D) */
			printf("\n");
			break;
		}

		/* Remove the newline character from the input */
		command[strcspn(command, "\n")] = '\0';

		if (strcmp(command, "exit") == 0)
		{
			/* Exit the shell if the user inputs "exit" */
			exit_flag = 1;
		}
		else
		{
			/* Execute the command */
			int status = system(command);

			if (status == -1)
			{
				printf("Error executing command\n");
			}
		}
	}

	return (0);
}

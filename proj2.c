#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define MAX_ARGS 64

/**
 * tokenize_command - Tokenizes the command line to extract arguments.
 *
 * @command: The command line input.
 * @args: The array to store the extracted arguments.
 *
 * Return: The number of arguments extracted.
 */
int tokenize_command(char *command, char *args[])
{
	char *token;
	int arg_count = 0;

	token = strtok(command, " ");
	while (token != NULL && arg_count < MAX_ARGS - 1)
	{
		args[arg_count] = token;
		arg_count++;
		token = strtok(NULL, " ");
	}
	args[arg_count] = NULL;

	return (arg_count);
}

/**
 * execute_command - Executes the command passed as arguments.
 *
 * @args: The array of command and arguments.
 */
void execute_command(char *args[])
{
	int status = execvp(args[0], args);

	if (status == -1)
	{
		perror("execvp failed");
		exit(EXIT_FAILURE);
	}
}

/**
 * display_prompt - Displays the shell prompt.
 */
void display_prompt(void)
{
	printf("$ ");
	fflush(stdout);
}

/**
 * read_command_line - Reads the command line input from the user.
 *
 * @command: The buffer to store the command line.
 *
 * Return: 1 if successful, 0 if end of file (Ctrl+D).
 */
int read_command_line(char *command)
{
	if (fgets(command, BUFFER_SIZE, stdin) == NULL)
	{
		/* Handle end of file (Ctrl+D) */
		printf("\n");
		return (0);
	}

	/* Remove the newline character from the input */
	command[strcspn(command, "\n")] = '\0';

	return (1);
}

/**
 * main - The main function of the program.
 *        It implements a simple shell that takes user commands and executes them.
 *
 * Return: Always 0.
 */
int main(void)
{
	char command[BUFFER_SIZE];
	char *args[MAX_ARGS];

	while (1)
	{
		display_prompt();

		if (!read_command_line(command))
			break;

		int arg_count = tokenize_command(command, args);

		pid_t pid = fork();

		if (pid < 0)
		{
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			/* Child process */
			execute_command(args);
		}
		else
		{
			/* Parent process */
			int child_status;

			waitpid(pid, &child_status, 0);
		}
	}

	return (0);
}

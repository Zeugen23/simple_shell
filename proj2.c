#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define MAX_ARGS 64

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

	return arg_count;
}

void execute_command(char *args[])
{
	execvp(args[0], args);
	perror("execvp failed");
	exit(EXIT_FAILURE);
}

void display_prompt(void)
{
	printf("$ ");
	fflush(stdout);
}

int read_command_line(char *command)
{
	if (fgets(command, BUFFER_SIZE, stdin) == NULL)
	{
		printf("\n");
		return 0;
	}
	command[strcspn(command, "\n")] = '\0';

	return 1;
}

int main(void)
{
	char command[BUFFER_SIZE];
	char *args[MAX_ARGS];
	pid_t pid;

	while (1)
	{
		display_prompt();

		if (!read_command_line(command))
			break;

		pid = fork();

		if (pid < 0)
		{
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execute_command(args);
		}
		else
		{
			int child_status;
			waitpid(pid, &child_status, 0);
		}
	}

	return 0;
}

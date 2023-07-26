#include "shell.h"

BuiltIn built_ins[] = {
{"exit", exit_shell},
{NULL, NULL}};

/**
 * exit_shell - Exit the shell
 * @args: Arguments passed to exit
 * @session: Pointer to the current shell session
 *
 * Return: Status of the exit command
 */
int exit_shell(char **args, Session *session)
{
	char *p_name = session->program_name;
	int status = session->last_status;

	if (args[1])
	{
		status = _atoi(args[1]);

		if ((status == 0 && _strcmp(args[1], "0")) != 0 || status < 0)
			status = handle_illegal_code(p_name, args[1]);
	}

	close_source(2, session);
	free_resources(session);
	free(session);

	exit(status);
}

/**
 * handle_illegal_code - Handle illegal exit status code error
 * @program_name: Name of the program
 * @arg: Argument passed to exit
 *
 * Return: Error status
 */
int handle_illegal_code(char *program_name, char *arg)
{
	write(STDERR_FILENO, program_name, _strlen(program_name));
	write(STDERR_FILENO, ": 1: exit: Illegal number: ", 27);
	write(STDERR_FILENO, arg, _strlen(arg));
	write(STDERR_FILENO, "\n", 1);

	return (2);
}

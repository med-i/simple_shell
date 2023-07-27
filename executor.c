#include "shell.h"

/**
 * execute_commands - Execute commands in a shell session
 * @session: Pointer to the current shell session
 *
 * Return: Status of the last executed command
 */
int execute_commands(Session *session)
{
	Command **commands = session->commands;
	char *path = NULL, *last_separator = NULL;
	int status = 0;
	size_t i, j;
	BuiltIn *built_ins = get_builtins();

	for (i = 0; commands[i]; i++)
	{
		process_separators(session, last_separator, status, &i);
		if (!commands[i])
			break;

		for (j = 0; built_ins[j].command; j++)
		{
			if (_strcmp(commands[i]->argv[0], built_ins[j].command) == 0)
			{
				status = built_ins[j].func(commands[i]->argv, session);
				goto next_command;
			}
		}

		if (access(commands[i]->path, X_OK))
			path = get_filepath(commands[i]->path);
		else
			path = _strdup(commands[i]->path);

		if (path)
			status = execute_single_command(commands[i], path);
		else
			status = handle_not_found(session->program_name, commands[i]->path);

next_command:
		last_separator = commands[i]->separator;
	}

	return (status);
}

/**
 * process_separators - Processes logical operators
 * @session: The current shell session.
 * @sep: The separator of the last executed command.
 * @status: The exit status of the last executed command.
 * @i: Pointer to the index of the current
 */
void process_separators(Session *session, char *sep, int status, size_t *i)
{
	Command **commands = session->commands;

	while (sep)
	{
		if ((!_strcmp(sep, "&&") && status != 0) ||
		    (!_strcmp(sep, "||") && status == 0))
		{
			sep = commands[*i]->separator;
			(*i)++;
		}
		else
			break;
	}
}

/**
 * execute_single_command - Execute a single command
 * @command: Pointer to the command
 * @path: Path of the command
 *
 * Return: Status of the executed command
 */
int execute_single_command(Command *command, char *path)
{
	pid_t pid;
	int status = EXIT_FAILURE;

	pid = fork();
	if (pid == -1)
	{
		perror("Failed to fork");
		free(path);
		return (1);
	}

	if (pid == 0)
	{
		if (execve(path, command->argv, command->envp) == -1)
		{
			perror("Failed to execute command");
			free(path);
			exit(1);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else
			status = EXIT_FAILURE;

		free(path);
	}

	return (status);
}

/**
 * get_filepath - Get file path of a command
 * @command: Pointer to the command string
 *
 * Return: Pointer to the file path string
 */
char *get_filepath(char *command)
{
	char *path, *dir, *file_path = NULL, *path_copy;
	char tmp_path[PATH_MAX + 1];

	path = _getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = _strdup(path);
	if (!path_copy)
	{
		free(path);
		return (NULL);
	}

	dir = _strtok(path_copy, ":");
	while (dir)
	{
		_strcpy(tmp_path, dir);
		_strcat(tmp_path, "/");
		_strcat(tmp_path, command);

		if (access(tmp_path, X_OK) == 0)
		{
			file_path = _strdup(tmp_path);
			break;
		}

		dir = _strtok(NULL, ":");
	}

	free(path_copy);
	free(path);
	return (file_path);
}

/**
 * handle_not_found - Handle command not found error
 * @program_name: Name of the program
 * @path: Path of the command
 *
 * Return: Error status
 */
int handle_not_found(char *program_name, char *path)
{
	write(STDERR_FILENO, program_name, _strlen(program_name));
	write(STDERR_FILENO, ": 1: ", 5);
	write(STDERR_FILENO, path, _strlen(path));
	write(STDERR_FILENO, ": not found\n", 12);

	return (127);
}

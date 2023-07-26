#include "shell.h"

/**
 * parse_commands - Parse commands in a shell session
 * @session: Pointer to the current shell session
 *
 * Return: Pointer to the array of commands
 */
Command **parse_commands(Session *session)
{
	Token **tokens = session->tokens;
	Command **commands = NULL, *command;
	size_t i;

	for (i = 0; tokens[i]; i++)
	{
		command = parse_single_command(tokens[i]);
		if (!command)
		{
			perror("Failed to parse command");
			free_resources(session);
			return (NULL);
		}

		commands = realloc(commands, (i + 2) * sizeof(Command *));
		if (!commands)
		{
			perror("Failed to allocate memory");
			free_resources(session);
			return (NULL);
		}

		commands[i] = command;
	}

	commands[i] = NULL;

	return (commands);
}

/**
 * parse_single_command - Parse a single command
 * @token: Pointer to the first token
 *
 * Return: Pointer to the parsed command
 */
Command *parse_single_command(Token *token)
{
	Command *command;
	size_t i, argv_index = 0;

	command = malloc(sizeof(Command));
	if (!command)
	{
		perror("Failed to allocate memory");
		return (NULL);
	}
	command->argv = NULL;
	command->separator = NULL;

	for (i = 0; token[i]; i++)
	{
		if (!strcmp(token[i], "#"))
			break;
		else if (!strcmp(token[i], ";") ||
			 !strcmp(token[i], "&&") || !strcmp(token[i], "||"))
			command->separator = token[i];
		else
		{
			if (argv_index == 0)
				command->path = token[i];

			command->argv = realloc(command->argv, (argv_index + 2) * sizeof(char *));
			if (!command->argv)
			{
				perror("Failed to allocate memory");
				free(command);
				return (NULL);
			}
			command->argv[argv_index++] = token[i];
		}
	}

	command->argv[argv_index] = NULL;
	command->envp = environ;

	return (command);
}

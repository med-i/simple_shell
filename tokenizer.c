#include "shell.h"

/**
 * separate_commands - Separate commands in a shell session
 * @session: Pointer to the current shell session
 *
 * Return: Pointer to the first token
 */
Token *separate_commands(Session *session)
{
	char *line = session->line;
	Token *commands = NULL, command;
	char *start = line, *end = line;
	size_t i = 0, len;

	while (*end != '\0')
	{
		if (*end == ';' ||
		    (_strncmp(end, "&&", 2) == 0) || (_strncmp(end, "||", 2) == 0))
		{
			end += *end == ';' ? 1 : 2;
			len = end - start;
			command = malloc(len + 1);
			_strncpy(command, start, len);
			command[len] = '\0';

			commands = realloc(commands, (i + 2) * sizeof(Token));
			commands[i++] = command;

			start = end;
		}
		else
			end++;
	}

	if (start != end)
	{
		command = _strdup(start);
		commands = realloc(commands, (i + 2) * sizeof(char *));

		commands[i++] = command;
	}

	commands[i] = NULL;

	return (commands);
}

/**
 * tokenize_commands - Tokenize commands in a shell session
 * @session: Pointer to the current shell session
 *
 * Return: Pointer to the array of tokens
 */
Token **tokenize_commands(Session *session)
{
	Token *commands = session->cmd_strs;
	Token **tokens_array = NULL, *tokens = NULL;
	size_t i;

	add_space_to_commands(commands);

	for (i = 0; commands[i]; i++)
	{
		tokens = tokenize_single_command(commands[i]);
		tokens_array = realloc(tokens_array, (i + 2) * sizeof(Token *));
		tokens_array[i] = tokens;
	}

	tokens_array[i] = NULL;

	return (tokens_array);
}

/**
 * tokenize_single_command - Tokenize a single command
 * @command: Pointer to the command string
 *
 * Return: Pointer to the first token
 */
Token *tokenize_single_command(char *command)
{
	Token *tokens = NULL;
	char *token = NULL;
	size_t i = 0;

	token = _strtok(command, DELIMITERS);
	while (token)
	{
		tokens = realloc(tokens, (i + 2) * sizeof(Token));
		tokens[i++] = token;
		token = _strtok(NULL, DELIMITERS);
	}
	tokens[i] = NULL;

	return (tokens);
}

/**
 * add_space_to_commands - Add spaces to commands
 * @commands: Pointer to the first token
 *
 * Return: Nothing
 */
void add_space_to_commands(Token *commands)
{
	size_t i;

	for (i = 0; commands[i]; i++)
		add_space(&commands[i]);
}

/**
 * add_space - Add spaces to a command
 * @command: Double pointer to the command string
 *
 * Return: Nothing
 */
void add_space(char **command)
{
	char *separators[] = {";", "&&", "||", NULL};
	char *separator = NULL, *sep_pos = NULL, *new_command = NULL;
	size_t i, cmd_len;

	for (i = 0; separators[i]; i++)
	{
		sep_pos = _strstr(*command, separators[i]);
		if (sep_pos)
		{
			separator = separators[i];
			break;
		}
	}

	if (!separator)
		return;

	cmd_len = sep_pos - *command;

	if (cmd_len > 0 && (*command)[cmd_len - 1] != ' ')
	{
		new_command = malloc((_strlen(*command) + 2) * sizeof(char));
		if (!new_command)
		{
			perror("Failed to allocate memory");
			exit(1);
		}

		_strncpy(new_command, *command, cmd_len);
		new_command[cmd_len] = '\0';
		_strcat(new_command, " ");
		_strcat(new_command, separator);
		free(*command);
		*command = new_command;
	}
}

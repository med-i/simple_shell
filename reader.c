#include "shell.h"

/**
 * get_source - Get the source of shell commands
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: Pointer to a Source struct
 */
Source *get_source(int argc, char **argv)
{
	Source *source = malloc(sizeof(Source));

	if (!source)
	{
		perror("Failed to allocate memory for Source");
		return (NULL);
	}

	if (argc > 1)
	{
		source->fd = open(argv[1], O_RDONLY);
		if (source->fd == -1)
		{
			perror("Failed to open file");
			free(source);
			return (NULL);
		}
		source->is_interactive = false;
	}
	else
	{
		source->fd = 0;
		source->is_interactive = isatty(STDIN_FILENO);
	}

	source->stream = fdopen(source->fd, "r");
	if (!source->stream)
	{
		close(source->fd);
		free(source);
		perror("fdopen");
		return (NULL);
	}

	return (source);
}

/**
 * read_input - Read input from a shell session
 * @session: Double pointer to the current shell session
 *
 * Return: Pointer to the input string
 */
char *read_input(Session **session)
{
	size_t len = 0;
	ssize_t read;

	if ((*session)->source->is_interactive)
		write(STDOUT_FILENO, PROMPT, 2);

	read = getline(&((*session)->line), &len, (*session)->source->stream);
	if (read <= 0)
		return (NULL);

	return ((*session)->line);
}

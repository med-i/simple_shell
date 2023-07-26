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

	read = _getline(&((*session)->line), &len, (*session)->source->fd);
	if (read <= 0)
		return (NULL);

	return ((*session)->line);
}

/**
 * _getline - Get a line from a file
 * @lineptr: Pointer to the line buffer
 * @n: Size of the line buffer
 * @fd: File descriptor
 *
 * Return: The number of characters read
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	static char buffer[BUFFER_SIZE];
	static ssize_t position, nread;
	ssize_t i;

	if (!lineptr || !n || fd < 0)
		return (-1);

	if (position >= nread)
	{
		nread = read(fd, buffer, BUFFER_SIZE);
		if (nread <= 0)
			return (nread);
		position = 0;
	}

	*lineptr = buffer + position;

	for (i = position; i < nread; ++i)
	{
		if (buffer[i] == '\n' || i == nread - 1)
		{
			position = (buffer[i] == '\n') ? i + 1 : 0;
			buffer[i] = '\0';
			break;
		}
	}

	return (nread - 1);
}

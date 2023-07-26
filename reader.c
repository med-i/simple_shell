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
 * read_from_fd - Read from file descriptor into buffer
 * @buffer: Buffer to read into
 * @fd: File descriptor to read from
 *
 * Return: Number of bytes read, or -1 on error
 */
static ssize_t read_from_fd(char *buffer, int fd)
{
	ssize_t nread;

	nread = read(fd, buffer, BUFFER_SIZE);
	return (nread);
}
/**
 * allocate_and_copy - Allocate memory and copy line into it
 * @lineptr: Pointer to the line buffer
 * @start: Pointer to the start of the line
 * @length: Length of the line
 *
 * Return: Length of the line, or -1 on error
 */
static ssize_t allocate_and_copy(char **lineptr, char *start, ssize_t length)
{
	*lineptr = malloc(length + 1);

	if (!*lineptr)
		return (-1);
	_strncpy(*lineptr, start, length);
	(*lineptr)[length] = '\0';
	return (length);
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
	static ssize_t position;
	static ssize_t nread;
	char *start;
	ssize_t length, i;

	if (!lineptr || !n || fd < 0)
		return (-1);

	while (true)
	{
		if (position >= nread)
		{
			position = 0;
			nread = read_from_fd(buffer, fd);
			if (nread <= 0)
				return (nread);
		}

		start = buffer + position;
		for (i = position; i < nread; i++)
		{
			if (buffer[i] == '\n' || i == nread - 1)
			{
				length = i - position;
				if (buffer[i] == '\n')
				{
					buffer[i] = '\0';
					position = i + 1;
					length++;
				}
				else if (i == nread - 1)
					position = 0;

				return (allocate_and_copy(lineptr, start, length));
			}
		}
	}
}

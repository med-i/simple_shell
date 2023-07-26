#include "shell.h"

/**
 * _strtok - Breaks a string into a sequence of
 * zero or more nonempty tokens
 * @str: The string to tokenize
 * @delim: The string of the delimiter characters
 *
 * Return: A pointer to the next token,
 * or NULL if there are no more tokens
 */
char *_strtok(char *str, const char *delim)
{
	static char *ptr;
	char *token;

	if (str)
		ptr = str;

	else if (!ptr || !delim || !*delim)
		return (NULL);

	while (*ptr && strchr(delim, *ptr))
		ptr++;

	if (!*ptr)
		return (NULL);

	token = ptr;
	while (*ptr && !strchr(delim, *ptr))
		ptr++;

	if (*ptr)
		*ptr++ = '\0';
	else
		ptr = NULL;

	return (token);
}

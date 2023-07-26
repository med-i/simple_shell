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
char *_strtok(char *str, char *delim)
{
	static char *ptr;
	char *token;

	if (str)
		ptr = str;

	else if (!ptr || !delim || !*delim)
		return (NULL);

	while (*ptr && _strchr(delim, *ptr))
		ptr++;

	if (!*ptr)
		return (NULL);

	token = ptr;
	while (*ptr && !_strchr(delim, *ptr))
		ptr++;

	if (*ptr)
		*ptr++ = '\0';
	else
		ptr = NULL;

	return (token);
}

/**
 * _atoi - Converts a string to an integer.
 * @s: The string to convert.
 *
 * Return: The converted integer. Otherwise 0;
 */
int _atoi(char *s)
{
	int sign = 1;
	int got_number = 0;
	unsigned int number = 0;

	while (*s != '\0')
	{
		char c = *s;

		if (!got_number && c == '-')
			sign *= -1;

		if (c >= 48 && c <= 57)
		{
			int digit = c - '0';

			number = number * 10 + digit;
			got_number = 1;
		}
		else if (got_number)
			break;

		s++;
	}

	return (number * sign);
}

/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter.
 * @str: the string to copy.
 *
 * Return: pointer to the duplicate of str, otherwise NULL.
 */
char *_strdup(char *str)
{
	char *dupstr;
	int i;

	if (!str)
		return (NULL);

	dupstr = malloc(_strlen(str) + 1);
	if (!dupstr)
	{
		free(dupstr);
		return (NULL);
	}

	for (i = 0; str[i]; i++)
		dupstr[i] = str[i];

	dupstr[i] = '\0';

	return (dupstr);
}

/**
 * _strcmp - Compares two strings.
 * @s1: First string.
 * @s2: Second string.
 *
 * Return: A negative value if s1 is less than s2.
 * A positive value if s1 is greater than s2.
 * 0, if the s1 and s2 are equal.
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);

		i++;
	}

	return (0);
}

/**
 * _strlen - Returns the length of a string.
 * @s: The string to be checked.
 * Return: The length of s.
 */
int _strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;

	return (i);
}

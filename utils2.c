#include "shell.h"

/**
 * *_strcpy - Copies string.
 * @dest: Destination string.
 * @src: Source string.
 *
 * Return: The pointer to dest.
 */
char *_strcpy(char *dest, char *src)
{
	int n = _strlen(src);
	int i;

	for (i = 0; i <= n; i++)
		dest[i] = src[i];

	return (dest);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: Pointer to the resulting string dest.
 */
char *_strcat(char *dest, char *src)
{
	int len = 0;
	int i = 0;

	while (dest[len] != '\0')
		len++;

	while (src[i] != '\0')
	{
		dest[len + i] = src[i];
		i++;
	}

	dest[len + i] = src[i];

	return (dest);
}

/**
 * _strncpy - Copies a string.
 * @dest: The destination string.
 * @src: The source string.
 * @n: The number of bytes to copy.
 *
 * Return: Pointer to the string dest.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];

	for (; i < n; i++)
		dest[i] = '\0';

	return (dest);
}

/**
 * _strchr - Locates a character in a string.
 * @s: The string to search.
 * @c: The character to look up.
 *
 * Return: Pointer to the first occurrence of the character c in the string s.
 * Or NULL if the character is not found.
 */
char *_strchr(char *s, char c)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
		if (s[i] == c)
			return (s + i);

	return (NULL);
}

#include "shell.h"

/**
 * _isspace - checks if a character is a whitespace
 * @c: The character to check
 *
 * Return: 1 if c is a whitespace, otherwise 0
 */
int _isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' ||
		c == '\v' || c == '\f' || c == '\r');
}

/**
 * _strstr -Locates a substring.
 * @haystack: The string to check.
 * @needle: The substring to find.
 *
 * Return: Pointer to the beginning of the located substring.
 * Or NULL if the substring is not found.
 */
char *_strstr(char *haystack, char *needle)
{
	int i, j;
	int start = 0;
	int has_str = 0;
	int sub_len = _strlen(needle);

	if (*needle == '\0')
		return (haystack);

	for (i = 0; haystack[i]; i++)
		if (haystack[i] == needle[0])
		{
			start = i;
			has_str = 1;

			for (j = 1; j < sub_len; j++)
			{
				if (haystack[++i] != needle[j])
				{
					has_str = 0;
					break;
				}
			}

			if (has_str)
				return (haystack + start);
		}

	return (NULL);
}

/**
 * _strncmp - compares two strings
 *
 * @s1: first string to be compared
 * @s2: second string to be compared
 * @n : number of characteres to compare
 * Return: 0 if s1 and s2 are equal and -1 if they are not
 */
int _strncmp(char *s1, char *s2, int n)
{
	int i = 0;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
			return (-1);
	}
	return (0);
}

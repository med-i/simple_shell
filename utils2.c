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
 * _realloc - Reallocates a memory block using malloc and free.
 * @ptr: A pointer to the memory previously allocated.
 * @size: The size of the new memory to be allocated.
 *
 * Return: A pointer to the reallocated memory.
 */
void *_realloc(void *ptr, size_t size)
{
	void *new_ptr;
	char *old_ptr, *new_ptr_char;
	size_t i;

	if (size == 0)
	{
		free(ptr);
		ptr = NULL;
		return (NULL);
	}

	new_ptr = malloc(size);
	if (new_ptr == NULL)
		return (NULL);

	if (ptr)
	{
		old_ptr = (char *)ptr;
		new_ptr_char = (char *)new_ptr;

		for (i = 0; i < size; i++)
			new_ptr_char[i] = old_ptr[i];
		free(ptr);
		ptr = NULL;
	}

	return (new_ptr);
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

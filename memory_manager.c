#include "shell.h"

/**
 * free_resources - Free resources of a shell session
 * @session: Pointer to the current shell session
 *
 * Return: Nothing
 */
void free_resources(Session *session)
{
	size_t i, j;

	if (session->cmd_strs)
	{
		for (i = 0; session->cmd_strs[i]; ++i)
			free(session->cmd_strs[i]);
		free(session->cmd_strs);
	}

	if (session->tokens)
	{
		for (i = 0; session->tokens[i]; ++i)
			free(session->tokens[i]);
		free(session->tokens);
	}

	if (session->commands)
	{
		for (j = 0; session->commands[j]; j++)
		{
			if (session->commands[j] != NULL)
			{
				free(session->commands[j]->argv);
				free(session->commands[j]);
			}
		}
		free(session->commands);
	}
}

/**
 * close_source - Close the source of shell commands
 * @argc: Argument count
 * @session: Pointer to the current shell session
 *
 * Return: Nothing
 */
void close_source(int argc, Session *session)
{
	if (argc > 1 && close(session->source->fd) == -1)
		perror("Failed to close file descriptor");

	free(session->source);
}

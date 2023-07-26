#include "shell.h"

/**
 * is_empty_line - Check if the current line is empty
 * @session: Pointer to the current shell session
 *
 * Return: true if the line is empty, false otherwise
 */
bool is_empty_line(Session *session)
{
	char *line = session->line;
	size_t i;

	for (i = 0; line[i]; i++)
	{
		if (!_isspace(line[i]))
			return (false);
	}

	return (true);
}

/**
 * initialize_session - Initialize the session object
 * @session: Double pointer to the session object
 *
 * This function initializes the session object by allocating memory
 * for it and setting its initial state.
 */
void initialize_session(Session **session)
{
	(*session) = malloc(sizeof(Session));
	if (!session)
	{
		perror("malloc");
	}

	(*session)->program_name = NULL;
	(*session)->source = NULL;
	(*session)->line = NULL;
	(*session)->cmd_strs = NULL;
	(*session)->tokens = NULL;
	(*session)->commands = NULL;
	(*session)->last_status = 0;
}

/**
 * main - Entry point
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success, or the status of the last executed command
 */
int main(int argc, char **argv)
{
	int last_status = 0;
	Session *session;

	initialize_session(&session);
	session->program_name = argv[0];
	session->source = get_source(argc, argv);
	if (!session->source)
		exit(127);

	while (read_input(&session) != NULL)
	{
		if (is_empty_line(session))
			continue;

		session->cmd_strs = separate_commands(session);
		session->tokens = tokenize_commands(session);
		session->commands = parse_commands(session);

		session->last_status = execute_commands(session);

		free_resources(session);
	}

	if (session->source->is_interactive)
		write(STDOUT_FILENO, "\n", 1);

	last_status = session->last_status;
	close_source(argc, session);
	free(session);

	return (last_status);
}

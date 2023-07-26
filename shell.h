#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PROMPT "$ "
#define BUFFER_SIZE 10000
#define DELIMITERS " \t\n\v\f\r"

/**
 * struct Source - Describes the source of shell commands
 * @fd: File descriptor of the source
 * @is_interactive: Boolean flag indicating if the session is interactive
 */
typedef struct Source
{
	int fd;
	bool is_interactive;
} Source;

/**
 * Token - Type definition for a shell token
 */
typedef char *Token;

/**
 * struct Command - Describes a shell command
 * @path: Path to the command executable
 * @argv: Arguments to the command
 * @envp: Environment variables for the command
 * @separator: Separator used before the command
 */
typedef struct Command
{
	char *path;
	char **argv;
	char **envp;
	char *separator;
} Command;

/**
 * struct Session - Describes a shell session
 * @program_name: Name of the shell program
 * @source: Source of the shell commands
 * @line: Current input line
 * @cmd_strs: Commands as strings
 * @tokens: Tokens of the commands
 * @commands: Parsed commands
 * @last_status: Status of the last command
 */
typedef struct Session
{
	char *program_name;
	Source *source;
	char *line;
	Token *cmd_strs;
	Token **tokens;
	Command **commands;
	int last_status;
} Session;

/**
 * struct BuiltIn - Describes a built-in shell command
 * @command: Name of the built-in command
 * @func: Function to execute the built-in command
 */
typedef struct BuiltIn
{
	char *command;
	int (*func)(char **, Session *);
} BuiltIn;

extern char **environ;
extern BuiltIn built_ins[];

/* reader */
Source *get_source(int argc, char **argv);
char *read_input(Session **session);
ssize_t _getline(char **lineptr, size_t *n, int fd);

/* tokenizer */
Token *separate_commands(Session *session);
Token **tokenize_commands(Session *session);
Token *tokenize_single_command(char *command);
void add_space_to_commands(Token *commands);
void add_space(char **command);

/* parser */
Command **parse_commands(Session *session);
Command *parse_single_command(Token *token);

/* executor */
int execute_commands(Session *session);
int execute_single_command(Command *command, char *path);
char *get_filepath(char *command);
int handle_not_found(char *program_name, char *path);

/* builtins */
int exit_shell(char **args, Session *session);
int handle_illegal_code(char *program_name, char *arg);

/* memory manager */
void free_resources(Session *session);
void close_source(int argc, Session *session);

/* utils */
char *_strtok(char *str, char *delim);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strncpy(char *dest, char *src, int n);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, int n);
char *_strstr(char *haystack, char *needle);
char *_strchr(char *s, char c);
char *_strcat(char *dest, char *src);
int _isspace(char c);
int _atoi(char *s);
void *_realloc(void *ptr, size_t size);
char *_getenv(char *name);

#endif

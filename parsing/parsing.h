#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../minishell.h"

typedef enum
{
	NONE,		// 0
	PIPE,		// 1
	REDIR_IN,	// 2
	REDIR_OUT,	// 3
	APPEND,		// 4
	HEREDOC,	// 5
	EXPORT,		// 6
	ARG,		// 7
	CMD			// 8
}	t_token;

typedef struct s_token
{
	char 			**str;
	char			**env;
	t_token			type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_line;

void	lexer(char **arg, t_line **head);
void	tokenize_cmd(char *str, t_line *tmp);
void	tokenize(char *arg, t_line *tmp);
void	tokenize_arg(char **arg, int *i, t_line *tmp);
void	tokenize_quotarg(char **arg, int *i, t_line *tmp, char c);
void	parse(char *line, t_line **head, char **env);
int		check_token(int c);
int		special_char(char *str, int i);
int		checkquotes(char *line);
int		checkspaces(char *line);
t_token	get_token(char *str);

#endif

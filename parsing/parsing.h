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
	NONE,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	EXPORT,
	ARG,
	CMD
}	t_token;

typedef struct s_token
{
	char 			**str;
	char			**env;
	t_token			type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_line;

void	lexer(char **arg, t_line *head);
int		special_char(char *str, int i);
void	add_back(t_line **head, t_line *new);
void	tokenize_cmd(char *str, t_line *tmp);
void	tokenize(char *arg, t_line *tmp);
int		tokenize_arg(char **arg, int i, t_line *tmp);
int		tokenize_quotarg(char **arg, int i, t_line *tmp, char c);
int		checkquotes(char *line);
int		checkspaces(char *line);
t_token	get_token(char *str);
void	*parse(char *line, t_line *head, char **env);

#endif

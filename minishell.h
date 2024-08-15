/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:50:28 by prizmo            #+#    #+#             */
/*   Updated: 2024/08/15 10:49:49 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <sys/wait.h>
# include <readline/readline.h>
# include <fcntl.h>
# include <readline/history.h>
# include "parsing/parsing.h"

# define RESET	"\x1b[0m"
# define BOLD	"\x1b[1m"
# define RED	"\x1b[31m"
# define GREEN	"\x1b[32m"
# define YELLOW	"\x1b[93m"
# define CYAN	"\x1b[36m"

typedef struct s_token t_line;

typedef	struct s_command
{
	char				*symbol;
	char				*command;
	struct s_command	*left;
	struct s_command	*rigth;
}						t_command;

typedef struct s_tree
{
    struct s_tree	*left;
    struct s_tree	*right;
    char			*data;
}					t_tree;

typedef struct s_data
{
	t_command	*command;
	t_list		*env;
	t_tree		*tree;
	t_line		*head;
	int			status;
}				t_data;

void	ft_execute(char *str, t_data *data);
// int		ft_env(t_env *lst);
int		handle_command(char *str, t_data *data);
// t_list	*get_env(char **env);
int		exec_command(char **av, char **env);
// void	check_arguments(char **av);
void	error_exit(char *str);
// void	parent(char **av, char **env, int fds[2]);
// void	child(char **av, char **env, int fds[2]);
int		execution(char **args, t_data *data);
// int		ft_cd(char **cmd, t_env *env);
int		ft_echo(char **cmd);
int		ft_pwd(void);
// int		ft_export(char **cmd, t_env *env);
// int		ft_unset(char **cmd, t_env *env);
int		ft_exit(void);

#endif

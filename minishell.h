/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:50:28 by prizmo            #+#    #+#             */
/*   Updated: 2024/07/27 12:22:40 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <sys/wait.h>
# include <readline/readline.h>
# include <fcntl.h>
# include <readline/history.h>

typedef struct s_list
{
	struct s_list	*next;
	char			*data;
}					t_list;

int		ft_env(t_list *lst);
int		handle_command(char *str, t_list *env);
t_list	*get_env(char **env);
void	exec_command(char *av, char **env);
void	check_arguments(char **av);
void	error_exit(char *str);
void	parent(char **av, char **env, int fds[2]);
void	child(char **av, char **env, int fds[2]);
int		execution(char **args, t_list *env);
int		ft_cd(char **cmd, t_list *env);
int		ft_echo(char **cmd);
int		ft_pwd(void);
int		ft_export(char **cmd, t_list *env);
int		ft_unset(char **cmd, t_list *env);
int		ft_exit(void);

#endif
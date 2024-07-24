/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:35:10 by prizmo            #+#    #+#             */
/*   Updated: 2024/07/24 11:37:07 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_command(char *str, t_list *env)
{
	char	**cmd;

	cmd = ft_split(str, ' ');
	if (ft_strncmp(cmd[0], "env", 3) == 0)
		ft_env(env);
	return (0);
}

void	error_exit(char *str)
{
	ft_putstr_fd("error with: ", 1);
	ft_putstr_fd(str, 1);
	write(1, "\n", 1);
	exit(1);
}

void	child(char **av, char **env, int fds[2])
{
	int	file_fd;

	file_fd = open(av[1], O_RDONLY, 0777);
	if (file_fd == -1)
		error_exit("file error");
	dup2(fds[1], 1);
	dup2(file_fd, 0);
	// nullify_fd(fds[0]);
	close(fds[0]);
	exec_pipe(av[2], env);
}

void	parent(char **av, char **env, int fds[2])
{
	int	file_fd;

	file_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_fd == -1)
		error_exit("file error");
	dup2(fds[0], 0);
	dup2(file_fd, 1);
	// nullify_fd(fds[1]);
	close(fds[1]);
	exec_pipe(av[3], env);
}

int	execution(char **args, char **env)
{
	pid_t	id;
	int		fds[2];

	if (pipe(fds) == -1)
		error_exit("pipe");
	check_arguments(args);
	id = fork();
	if (id < 0)
		error_exit("fork error");
	if (id == 0)
		child(args, env, fds);
	waitpid(0, NULL, 0);
	parent(args, env, fds);
}
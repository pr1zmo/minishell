/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:35:10 by prizmo            #+#    #+#             */
/*   Updated: 2024/08/08 11:44:22 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize(t_list *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	handle_command(char *str, t_list *env)
{
	t_tree	*tree;
	tree = ft_parse(str, env);

	return (1);
}

void	ft_execute(char *str, t_list *env)
{
	char	**cmd;

	cmd = ft_split(str, ' ');
	if (ft_strncmp(cmd[0], "env", 3) == 0)
		ft_env(env);
	if (ft_strncmp(cmd[0], "echo", 4) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(cmd[0], "cd", 2) == 0)
		ft_cd(cmd, env);
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
		ft_export(cmd, env);
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
		ft_unset(cmd, env);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
		ft_exit();
	else
		execution(cmd, env);
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
	close(fds[0]);
	exec_command(av[2], env);
}

void	parent(char **av, char **env, int fds[2])
{
	int	file_fd;

	file_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_fd == -1)
		error_exit("file error");
	dup2(fds[0], 0);
	dup2(file_fd, 1);
	close(fds[1]);
	exec_command(av[3], env);
}

int	execution(char **args, t_list *env)
{
	pid_t	id;
	int		fds[2];
	char	**env_data;
	int		i;

	i = 0;
	env_data = (char **)malloc(sizeof(char *) * ft_lstsize(env) + 1);
	while (env)
	{
		env_data[i] = env->data;
		env = env->next;
		i++;
	}
	if (pipe(fds) == -1)
		error_exit("pipe");
	check_arguments(args);
	id = fork();
	if (id < 0)
		error_exit("fork error");
	if (id == 0)
		child(args, env_data, fds);
	waitpid(0, NULL, 0);
	parent(args, env_data, fds);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:35:10 by prizmo            #+#    #+#             */
/*   Updated: 2024/08/18 13:01:46 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_exit(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

static void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	*get_full_cmd(char *av, char **env)
{
	int		i;
	char	*result;
	char	*full_cmd;
	char	**path;

	i = 0;
	path = ft_split(getenv("PATH"), ':');
	if (!path)
		error_exit("Path error");
	while (path[i])
	{
		result = ft_strjoin(path[i], "/");
		full_cmd = ft_strjoin(result, av);
		free(result);
		if (access(full_cmd, X_OK | F_OK) == 0)
			return (full_cmd);
		free(full_cmd);
		i++;
	}
	free_arr(path);
	return (NULL);
}

void	ft_execve(t_data *data)
{
	int		pid;
	char	*cmd;

	if (access(data->head->str[0], X_OK | F_OK) == 0)
	{
		pid = fork();
		if (pid == 0)
			execve(getenv("PATH"), data->head->str, data->head->env);
	}
	else
		error_exit("data->head->str");
}

void	ft_execute(t_data *data)
{
	int	i;

	i = 0;
	ft_execve(data);
}

int	single_cmd(t_data *data)
{
	while (data->head)
	{
		if (data->head->type == 8)
			ft_execute(data);
	}
}

int	handle_command(t_data *data)
{
	printf("str: %s\n", data->head->str[0]);
	if (single_cmd(data->head))
		exec_single_cmd(data);
	ft_execute(data);
	return (1);
}

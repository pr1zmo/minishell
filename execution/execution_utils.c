/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:46:19 by prizmo            #+#    #+#             */
/*   Updated: 2024/07/26 15:46:19 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static	char	**check_path(char **env)
{
	int	i;
	char	**path;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
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

void	process_command(char *path, char **av, char **env)
{
	int	i;

	i = 0;
}

// char	*special_char(char *cmd)
// {
// 	if (ft_strncmp(cmd, "|", 1))
// 		return (NULL);
// }

void	exec_command_list(char *path, char **cmd, char **av)
{
	int		i;
	char	*special_cmd;

	i = 0;
	// while (cmd[i])
	// {
	// 	if (special_cmd = special_char(cmd[i]))
	// 		return;
	// }
}

int	exec_command(char **av, char **env)
{
	char	**cmd;
	char	*path;

	if (av[0][0] == '/')
		path = ft_strdup(av[0]);
	else
		path = get_full_cmd(av[0], env);
	if (!path)
	{
		perror(av[0]);
		exit(1);
	}
	process_command(path, av, env);
	return (1);
}

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
	// path = check_path(env);
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
	if (execve(path, av, env) == -1)
	{
		free_arr(cmd);
		perror("execve");
		exit(1);
	}
	return (1);
}

void	check_arguments(char **av)
{
	if (av[2][0] == '\0' || av[3][0] == '\0')
		error_exit("Bad arguments");
}
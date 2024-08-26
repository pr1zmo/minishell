/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:18:31 by prizmo            #+#    #+#             */
/*   Updated: 2024/08/25 20:54:46 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i]);
	free(arr);
}

char	**set_env(char **envp)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 1);
	if (!rtn)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		rtn[i] = ft_strdup(envp[i]);
		if (rtn[i] == NULL)
		{
			free_arr(rtn);
			return (rtn);
		}
		i++;
	}
	return (rtn);
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	char	*str;
	t_data	*program;

	if (ac != 1)
		return (printf("minishell doesn't take any arguments\n"), 1);
	printf("S1\n");
	program->envp = set_env(env);
	printf("S\n");
	program = malloc(sizeof(t_data));
	program->status = 1;
	minishell(program);
	free(program);
	return (0);
}

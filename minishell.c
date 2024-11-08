/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:18:31 by prizmo            #+#    #+#             */
/*   Updated: 2024/11/08 17:09:26 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_exit_status;

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

t_list	*set_env(char **envp)
{
	t_list	*env;
	t_list	*new;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		new = malloc(sizeof(t_list));
		if (!new)
			return (NULL);
		new->content = ft_strdup(envp[i]);
		new->next = env;
		env = new;
		i++;
	}
	return (env);
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	t_data	program;

	if (ac != 1)
		return (printf("minishell doesn't take any arguments\n"), 1);
	program.envp = set_env(env);
	program.status = 0;
	minishell(&program);
	return (0);
}

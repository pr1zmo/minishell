/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:18:31 by prizmo            #+#    #+#             */
/*   Updated: 2024/10/08 16:04:30 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i]);
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
	program.status = 1;
	minishell(&program);
	return (0);
}

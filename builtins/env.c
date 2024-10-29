/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:45:30 by prizmo            #+#    #+#             */
/*   Updated: 2024/10/29 23:15:52 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_env(t_list *envp)
{
	if (envp == NULL)
		return;
	while (envp)
	{
		printf("%s\n", (char *)envp->content);
		envp = envp->next;
	}
}

int	ft_env(t_data *data, char **args)
{
	int		i;
	t_list	*env_temp = data->envp;

	if (args && args[1])
		return (perror("env"), EXIT_FAILURE);
	i = 0;
	if (!data->envp)
		return (EXIT_FAILURE);
	print_env(env_temp);
	return (EXIT_SUCCESS);
}
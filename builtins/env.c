/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:45:30 by prizmo            #+#    #+#             */
/*   Updated: 2024/10/22 10:26:10 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_reverse(t_list *envp)
{
	if (envp == NULL)
		return;
	if (envp->next)
		print_reverse(envp->next);
	printf("%s\n", (char *)envp->content);
}

int	ft_env(t_data *data, char **args)
{
	int		i;
	t_list	*env_temp = data->envp;

	if (args && args[1])
		return (perror(args[1]), EXIT_FAILURE);
	i = 0;
	if (!data->envp)
		return (EXIT_FAILURE);
	print_reverse(env_temp);
	return (EXIT_SUCCESS);
}
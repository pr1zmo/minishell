/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:45:30 by prizmo            #+#    #+#             */
/*   Updated: 2024/10/01 20:19:52 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_error_env(char **cmd, char *str)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(cmd[1], 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(RESET, 2);
}

void	print_reverse(t_list *envp)
{
	if (envp == NULL)
		return;
	print_reverse(envp->next);
	printf("%s\n", (char *)envp->content);
}

int	ft_env(t_data *data, char **args)
{
	int		i;
	t_list	*env_temp = data->envp;

	if (args && args[1])
		return (print_error_env(args, ": No such file or directory\n"), EXIT_FAILURE);
	i = 0;
	if (!data->envp)
		return (EXIT_FAILURE);
	print_reverse(env_temp);
	return (EXIT_SUCCESS);
}
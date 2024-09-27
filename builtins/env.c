/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:45:30 by prizmo            #+#    #+#             */
/*   Updated: 2024/09/26 22:17:44 by zelbassa         ###   ########.fr       */
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

int	ft_env(t_data *data, char **args)
{
	int	i;

	if (args && args[1])
		return (print_error_env(args, ": No such file or directory\n"), EXIT_FAILURE);
	i = 0;
	if (!data->envp)
		return (EXIT_FAILURE);
	while (data->envp[i])
		ft_putendl_fd(data->envp[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
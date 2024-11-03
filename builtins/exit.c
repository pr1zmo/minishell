/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:48:20 by prizmo            #+#    #+#             */
/*   Updated: 2024/11/03 20:52:49 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_exit(t_data *data, char **cmd)
{
	exit_status = 1;
	ft_putstr_fd("exit ", STDERR_FILENO);
	cmd[1] ? ft_putendl_fd("❤️", STDERR_FILENO) : ft_putendl_fd("💚", STDERR_FILENO);
	if (cmd[1] && cmd[2])
	{
		exit_status = 1;
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	}
	else if (cmd[1] && isalnum(cmd[1]) == 0)
	{
		exit_status = 255;
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	}
	else if (cmd[1])
		exit_status = ft_atoi(cmd[1]);
	else
		exit_status = 0;
	return (0);
}
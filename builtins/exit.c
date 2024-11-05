/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:48:20 by prizmo            #+#    #+#             */
/*   Updated: 2024/11/05 00:50:22 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_data(t_data *data, int code)
{
	exit(code);
}

static int	get_code()
{
	//
	return (0);
}

int	check_arguemnts(char **cmd)
{
	
}

int ft_exit(t_data *data, char **cmd)
{
	int	exit_code;

	exit_code = 0;
	
	free_data(data, exit_code);
}
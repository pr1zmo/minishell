/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:43:22 by zelbassa          #+#    #+#             */
/*   Updated: 2024/09/27 01:43:17 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(t_data *data, char **arg)
{
	if (!arg[1])
		return (printf("cd: too few arguments"));
	if (!is_valid_path(arg[1]))
		return (printf("cd: no such file or directory: %s\n", arg[1]));
	return (0);
}

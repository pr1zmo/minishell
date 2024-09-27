/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:29:00 by prizmo            #+#    #+#             */
/*   Updated: 2024/09/27 00:08:02 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	has_flag(char *av)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	i = 0;
	if (av[i] != '-')
		return (n_flag);
	i++;
	while (av[i] && av[i] == 'n')
		i++;
	if (av[i] == '\0')
		n_flag = true;
	return (n_flag);
}

int ft_echo(t_data *data, char **av)
{
	int	n_flag;
	int	i;

	i = 1;
	(void)data;
	n_flag = has_flag(av[1]);
	while (av[i])
	{
		while (has_flag(av[i]))
			i++;
		printf("%s", av[i]);
		if (av[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (EXIT_SUCCESS);
}
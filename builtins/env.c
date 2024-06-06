/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:45:30 by prizmo            #+#    #+#             */
/*   Updated: 2024/06/06 15:45:10 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_list	*env)
{
	t_list	*tmp;
	
	tmp = env;
	while (tmp != NULL)
	{
		ft_putendl_fd(tmp->data, 1);
		tmp = tmp->next;
	}
	return (1);
}
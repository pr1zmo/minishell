/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:12:07 by mel-bouh          #+#    #+#             */
/*   Updated: 2024/08/14 14:54:24 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_env **lst, void (*del)(void *))
{
	t_env	*node;
	t_env	*save;

	if (!lst || !del || !(*lst))
		return ;
	node = *lst;
	while (node)
	{
		del(node->content);
		save = node->next;
		free(node);
		node = save;
	}
	*lst = NULL;
}

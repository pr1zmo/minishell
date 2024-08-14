/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:12:07 by mel-bouh          #+#    #+#             */
/*   Updated: 2023/11/06 17:23:01 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*save;

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

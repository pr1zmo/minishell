/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:24:33 by mel-bouh          #+#    #+#             */
/*   Updated: 2024/08/14 15:03:07 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_env	*ft_lstmap(t_env *lst, void *(*f)(void *), void (*del)(void *))
{
	t_env	*newlist;
	t_env	*new;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	newlist = NULL;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (new == NULL)
		{
			del(new->content);
			ft_lstclear(&newlist, del);
			return (newlist);
		}
		ft_lstadd_back(&newlist, new);
		lst = lst->next;
	}
	return (newlist);
}

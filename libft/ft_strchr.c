/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:21:36 by zelbassa          #+#    #+#             */
/*   Updated: 2023/11/13 17:57:31 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	to_find;
	int		i;

	i = 0;
	to_find = (char)c;
	while (s[i] != '\0')
	{
		if (s[i] == to_find)
			return ((char *)s + i);
		i ++;
	}
	if (to_find == '\0')
		return ((char *)s + i);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:22:05 by zelbassa          #+#    #+#             */
/*   Updated: 2023/11/16 00:17:55 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_ndl;

	len_ndl = 0;
	if (!*needle)
		return ((char *)haystack);
	len_ndl = ft_strlen(needle);
	while (*haystack && len >= len_ndl)
	{
		if (!ft_strncmp(haystack, needle, len_ndl))
			return ((char *)haystack);
		haystack ++;
		len --;
	}
	return (NULL);
}

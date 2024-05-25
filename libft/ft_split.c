/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 23:13:56 by zelbassa          #+#    #+#             */
/*   Updated: 2023/11/16 14:36:11 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_count(const char *s, char c)
{
	size_t	ret;

	ret = 0;
	while (*s)
	{
		if (*s != c)
		{
			++ret;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (ret);
}

static void	*free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i]);
	free(arr);
	return (NULL);
}

static int	ft_check(size_t len, char ***rest)
{
	*rest = malloc(sizeof(char *) * (len + 1));
	if (!*rest)
		return (0);
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**res;
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	i = 0;
	if (!ft_check(word_count(s, c), &res))
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				s++;
			res[i++] = ft_substr(s - len, 0, len);
			if (res[i - 1] == NULL)
				return (free_arr(res));
		}
		else
			++s;
	}
	res[i] = 0;
	return (res);
}

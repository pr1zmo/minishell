/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:40:33 by mel-bouh          #+#    #+#             */
/*   Updated: 2024/09/29 22:04:41 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *line, char *buf)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!line || !buf)
		return (NULL);
	str = (char *)malloc(ft_strlen(line) + ft_strlen(buf) + 1);
	if (!str)
		return (NULL);
	while (line[i])
	{
		str[i] = line[i];
		i++;
	}
	while (buf[j])
	{
		str[i] = buf[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

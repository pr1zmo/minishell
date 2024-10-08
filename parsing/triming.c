/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triming.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:18:29 by mel-bouh          #+#    #+#             */
/*   Updated: 2024/10/07 14:35:20 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_trim(char *str, int i)
{
	if (str[i] == '\"' && (quotes_open(str, i) != 1))
		return (1);
	if (str[i] == '\'' && (quotes_open(str, i) != 2))
		return (1);
	return (0);
}

static int	size_to_alloc(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (check_trim(str, i))
			size--;
		size++;
		i++;
	}
	return (size);
}

static char	*trim(char *str)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(size_to_alloc(str) + 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (check_trim(str, i))
			i++;
		if (!str[i])
			break ;
		new[j++] = str[i++];
	}
	new[j] = '\0';
	free(str);
	return (new);
}

void	triming_quotes(t_line *head)
{
	int	i;

	while (head)
	{
		i = 0;
		while (head->str[i])
		{
			if (ft_strchr(head->str[i], '\'') || ft_strchr(head->str[i], '\"'))
				head->str[i] = trim(head->str[i]);
			i++;
		}
		head = head->next;
	}
}

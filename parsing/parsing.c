/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouad <mouad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:58:54 by prizmo            #+#    #+#             */
/*   Updated: 2024/09/27 03:22:19 by mouad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// int	search_for_var(char *str, char **env)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = 0;
// 	while (str[len] && !(str[len] >= 9 && str[len] <= 13) && str[len] != ' ')
// 		len++;
// 	while (env[i])
// 	{
// 		if (!ft_strncmp(env, str, len))
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

// void	find_and_replace(char **str, char **env)
// {
// 	char	*p;
// 	int		index;
// 	int		i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		p = str[i];
// 		while (*p)
// 		{
// 			if (*p == '$' && *(p + 1))
// 			{
// 				p++;
// 				index = search_for_var(p, env);
// 				if (index != -1)
// 					expand_variable(str, env, index);
// 			}
// 			p++;
// 		}
// 		i++;
// 	}
// }

// void	expand(t_line **head)
// {
// 	t_line	*node;
// 	int		i;

// 	node = *head;
// 	while (node)
// 	{
// 		find_and_replace(node->str, node->env);
// 	}
// }

void	parse(char *str, t_line **head, char **env)
{
	char	**arg;
	char	*line;

	if (!checkspaces(str))
		return ;
	if (!checkquotes(str))
		return ;
	line = spacing(str);
	arg = ft_split(line, ' ');
	if (!arg)
		return ;
	lexer(arg, head);
	get_env(head, env);
	// expand(head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouad <mouad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:58:54 by prizmo            #+#    #+#             */
/*   Updated: 2024/09/26 03:42:34 by mouad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	get_env(t_line **head, char **env)
{
	int		i;
	char	**tmp;
	t_line	*line;

	i = 0;
	line = *head;
	while (env[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		tmp[i] = ft_strdup(env[i]);
		i++;
	}
	tmp[i] = NULL;
	while (line)
	{
		line->env = tmp;
		line = line->next;
	}
}

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

void	spacing(char *line)
{

}

void	parse(char *line, t_line **head, char **env)
{
	char	**arg;

	if (!checkspaces(line))
		return ;
	if (!checkquotes(line))
		return ;
	arg = ft_split(line, ' ');
	if (!arg)
		return ;
	spacing(line);
	lexer(arg, head);
	get_env(head, env);
	// expand(head);
}

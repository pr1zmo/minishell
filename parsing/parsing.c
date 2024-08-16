/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:58:54 by prizmo            #+#    #+#             */
/*   Updated: 2024/08/16 12:13:24 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	special_char(char *str, int i)
{
	if (str[i] == '&' || str[i] == ';')
		return (1);
	if (str[i] == '|' && str[i + 1] == '|')
		return (1);
	return (0);
}

int	checkquotes(char *line)
{
	int	i;
	int	quotes[2];

	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !(quotes[1] % 2))
			quotes[0]++;
		else if (line[i] == '\"' && !(quotes[0] % 2))
			quotes[1]++;
		else if (special_char(line, i) && !(quotes[0] % 2) && !(quotes[1] % 2))
		{
			write (2, "Parsing error near '", 20);
			write (2, &line[i], 1);
			write (2, "'\n", 2);
			return (0);
		}
		i++;
	}
	if ((quotes[0] % 2) || (quotes [1] % 2))
		return (ft_putstr_fd("Parsing error: missing closing quotation\n", 2),0);
	return (1);
}

int	checkspaces(char *line)
{
	int	i;

	i = 0;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
		i++;
	if (!line[i])
		return (0);
	return (1);
}

// void	get_env(t_line **line, char **env)
// {
// 	int		i;
// 	char	**tmp;

// 	i = 0;
// 	while (env[i])
// 		i++;
// 	tmp = malloc(sizeof(char *) * (i + 1));
// 	i = 0;
// 	while (env[i])
// 	{
// 		tmp[i] = ft_strdup(env[i]);
// 		i++;
// 	}
// 	tmp[i] = NULL;
// 	while (line)
// 	{
// 		line->env = tmp;
// 		line = line->next;
// 	}
// }

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
	lexer(arg, head);
	// get_env(head, env);
}

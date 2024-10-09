/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:58:54 by prizmo            #+#    #+#             */
/*   Updated: 2024/10/09 18:03:24 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse(char *str, t_line **head, char **env, t_parse *data)
{
	char	**arg;
	char	*line;

	if (!checkspaces(str))
		return ;
	if (!checkquotes(str))
		return ;
	line = spacing(str);
	data->env = NULL;
	init(&data->env, env);
	line = find_and_replace(line, data->env);
	arg = ft_split(line, ' ');
	if (!arg)
		return ;
	lexer(arg, head, data);
	triming_quotes(*head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:58:54 by prizmo            #+#    #+#             */
/*   Updated: 2024/10/04 15:08:36 by mel-bouh         ###   ########.fr       */
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
	if (!line)
		return ;
	init(data, env);
	line = find_and_replace(line, data->env);
	arg = ft_split(line, ' ');
	if (!arg)
		return ;
	lexer(arg, head, data);
	triming_quotes(*head);
}

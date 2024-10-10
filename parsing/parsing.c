/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:58:54 by prizmo            #+#    #+#             */
/*   Updated: 2024/10/10 17:47:20 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// int	parse_error(t_line *head)
// {

// }

int	parse(char *str, t_line **head, char **env, t_parse *data)
{
	char	**arg;
	char	*line;

	if (!checkspaces(str))
		return (0);
	if (!checkquotes(str))
		return (2);
	line = spacing(str);
	line = find_and_replace(line, data);
	arg = ft_split(line, ' ');
	if (!arg)
		return (139);
	free(line);
	lexer(arg, head, data);
	triming_quotes(*head);
	return (parse_error(*head));
}

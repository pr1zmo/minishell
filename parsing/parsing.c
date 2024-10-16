/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:58:54 by prizmo            #+#    #+#             */
/*   Updated: 2024/10/16 15:34:26 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	print_error(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd("\n", 2);
	return (2);
}

int	redir_error(t_line *head)
{
	while (head)
	{
		if (check_token(head->str[0][0]) == 2 && \
		(!head->next || head->next->type == PIPE))
			return (print_error("newline"));
		if (check_token(head->str[0][0]) == 2 && check_token(head->next->str[0][0]) == 2)
			return (print_error(head->next->str[0]));
		head = head->next;
	}
	return (0);
}

int	pipe_error(t_line *head)
{
	if (head->type == PIPE)
		return (1);
	while (head)
	{
		if (head->type == PIPE && !head->next)
			return (1);
		if (head->type == PIPE && head->next->type == PIPE)
			return (1);
		head = head->next;
	}
	return (0);
}

int	parse_error(t_line *head)
{
	if (pipe_error(head))
		return (print_error("|"));
	if (redir_error(head))
		return (2);
	return (0);
}

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
	free(line);
	if (!arg)
		return (139);
	for (int i = 0; arg[i]; i++)
		printf("str = %s\n", arg[i]);
	lexer(arg, head, data);
	triming_quotes(*head);
	return (parse_error(*head));
}

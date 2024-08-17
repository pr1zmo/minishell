/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:58:49 by prizmo            #+#    #+#             */
/*   Updated: 2024/08/17 12:16:03 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	lstadd_back(t_line **head, t_line *new)
{
	t_line	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token	get_token(char *str)
{
	if (!str)
		return (NONE);
	if (!ft_strncmp(str, "|", 1))
		return (PIPE);
	else if (!ft_strncmp(str, ">>", 2))
		return (APPEND);
	else if (!ft_strncmp(str, "<<", 2))
		return (HEREDOC);
	else if (!ft_strncmp(str, "<", 1))
		return (REDIR_IN);
	else if (!ft_strncmp(str, ">", 1))
		return (REDIR_OUT);
	else
		return (NONE);
}

int	is_command(char **arg, int i)
{
	if (i == 0)
		return (1);
	else if (get_token(arg[i - 1]) == PIPE)
		return (1);
	else
		return (0);
}

void	lexer(char **arg, t_line **head)
{
	t_line	*tmp;
	int		i;

	i = 0;
	while (arg[i])
	{
		tmp = malloc(sizeof(t_line));
		if (!tmp)
			return ;
		if (is_command(arg, i))
			tokenize_cmd(arg[i++], tmp);
		else if (ft_strchr(arg[i], '\"'))
			tokenize_quotarg(arg, &i, tmp, '\"');
		else if (ft_strchr(arg[i], '\''))
			tokenize_quotarg(arg, &i, tmp, '\'');
		else if (get_token(arg[i]) != NONE)
			tokenize(arg[i++], tmp);
		else
			tokenize_arg(arg, &i, tmp);
		lstadd_back(head, tmp);
	}
	// i = 0;
	// while (*head)
	// {
	// 	i = 0;
	// 	while ((*head)->str[i] && (*head))
	// 	{
	// 		printf("This is a node: \n");
	// 		printf("----------------------\n");
	// 		printf("args[%d]: %s\n", i, (*head)->str[i]);
	// 		printf("type: %d\n", (*head)->type);
	// 		printf("----------------------\n");
	// 		i++;
	// 	}
	// 	(*head) = (*head)->next;
	// }
}

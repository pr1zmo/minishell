/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouad <mouad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:11:36 by prizmo            #+#    #+#             */
/*   Updated: 2024/08/14 18:13:49 by mouad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

void	lexer(char **arg, t_line *head)
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
		ft_lstadd_back(&head, tmp);
	}
	while (head)
	{
		printf("this is a node\n");
		printf("--------------\n");
		for (int j = 0; head->str[j]; j++)
			printf("str: %s\n", head->str[j]);
		printf("type: %d\n", head->type);
		head = head->next;
	}
}

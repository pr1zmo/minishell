/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:58:58 by prizmo            #+#    #+#             */
/*   Updated: 2024/08/25 13:36:11 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_args(char **arg, int i, char c)
{
	int	count;

	count = 1;
	i++;
	while (arg[i] && !ft_strchr(arg[i], c))
	{
		count++;
		i++;
	}
	if (arg[i])
		count++;
	return (count);
}

void	tokenize_quotarg(char **arg, int *i, t_line *tmp, char c)
{
	int		count;
	int		j;

	count = count_args(arg, *i, c);
	j = 0;
	tmp->str = malloc(sizeof(char *) * (count + 1));
	tmp->str[j] = ft_strdup(arg[*i]);
	j++;
	*i += 1;
	while (arg[*i] && !ft_strchr(arg[*i], c))
	{
		tmp->str[j] = ft_strdup(arg[*i]);
		j++;
		*i += 1;
	}
	if (arg[*i])
	{
		tmp->str[j] = ft_strdup(arg[*i]);
		j++;
		*i += 1;
	}
	tmp->str[j] = NULL;
	tmp->type = ARG;
	tmp->next = NULL;
}

void	tokenize_arg(char **arg, int *i, t_line *tmp)
{
	int	count;
	int	j;

	count = 0;
	j = *i;
	while (arg[j] && get_token(arg[j]) == NONE)
	{
		count++;
		j += 1;
	}
	j = 0;
	tmp->str = malloc(sizeof(char *) * (count + 1));
	while (arg[*i] && get_token(arg[*i]) == NONE)
	{
		tmp->str[j] = ft_strdup(arg[*i]);
		j++;
		*i += 1;
	}
	tmp->str[j] = NULL;
	tmp->type = ARG;
	tmp->next = NULL;
}

void	tokenize(char *arg, t_line *tmp)
{
	tmp->str = malloc(sizeof(char *) * 2);
	tmp->str[0] = ft_strdup(arg);
	tmp->str[1] = NULL;
	tmp->type = get_token(arg);
	tmp->next = NULL;
}

void	tokenize_cmd(char *str, t_line *tmp)
{
	tmp->str = malloc(sizeof(char *) * 2);
	tmp->str[0] = ft_strdup(str);
	tmp->str[1] = NULL;
	tmp->type = CMD;
	tmp->next = NULL;
}

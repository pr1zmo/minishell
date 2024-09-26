/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouad <mouad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:58:58 by prizmo            #+#    #+#             */
/*   Updated: 2024/09/26 03:38:26 by mouad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	count_args(char **arg, int i, char c)
{
	int	count;
	int	found[2];
	int	j;

	count = 0;
	found[0] = 0;
	found[1] = 0;
	while (arg[i])
	{
		j = 0;
		while (arg[i][j])
		{
			if (arg[i][j] == '\'' && found[0] % 2 == 0)
				found[1]++;
			if (arg[i][j] == '\"' && found[1] % 2 == 0)
				found[0]++;
			count++;
			j++;
		}
		if (found[0] % 2 == 0 && found[1] % 2 == 0)
			break ;
		count++;
		i++;
	}
	return (count);
}

void	tokenize_quotarg(char **arg, int *i, t_line *tmp, char c)
{
	char	*argument;
	int		found[2];
	int		k;
	int		j;

	tmp->str = malloc(sizeof(char *) * 2);
	argument = malloc(sizeof(char) * (count_args(arg, *i, c) + 1));
	found[0] = 0;
	found[1] = 0;
	k = 0;
	while (arg[*i])
	{
		j = 0;
		while (arg[*i][j])
		{
			if (arg[*i][j] == '\'' && found[0] % 2 == 0)
				found[1]++;
			if (arg[*i][j] == '\"' && found[1] % 2 == 0)
				found[0]++;
			argument[k++] = arg[*i][j++];
		}
		*i += 1;
		if (found[0] % 2 == 0 && found[1] % 2 == 0)
			break ;
		argument[k++] = ' ';
	}
	argument[k] = '\0';
	tmp->str[0] = argument;
	tmp->str[1] = NULL;
	tmp->type = ARG;
	tmp->next = NULL;
}
// void	tokenize_quotarg(char **arg, int *i, t_line *tmp, char c)
// {
// 	int		count;
// 	int		j;

// 	count = count_args(arg, *i, c);
// 	j = 0;
// 	tmp->str = malloc(sizeof(char *) * (count + 1));
// 	tmp->str[j] = ft_strdup(arg[*i]);
// 	j++;
// 	*i += 1;
// 	while (arg[*i] && !ft_strchr(arg[*i], c))
// 	{
// 		tmp->str[j] = ft_strdup(arg[*i]);
// 		j++;
// 		*i += 1;
// 	}
// 	if (arg[*i])
// 	{
// 		tmp->str[j] = ft_strdup(arg[*i]);
// 		j++;
// 		*i += 1;
// 	}
// 	tmp->str[j] = NULL;
// 	tmp->type = ARG;
// 	tmp->next = NULL;
// }

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
	int	i;
	int	size;
	int	j;

	i = 0;
	size = 0;
	j = 0;
	while (str[size] && check_token(str[size]))
		size++;
	tmp->str = malloc(sizeof(char *) * 2);
	tmp->str[0] = malloc(size + 1);
	while (str[i] && check_token(str[i]))
		tmp->str[0][j++] = str[i++];
	tmp->str[0][j] = '\0';
	tmp->str[1] = NULL;
	tmp->type = CMD;
	tmp->next = NULL;
}

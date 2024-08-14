/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouad <mouad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:11:32 by prizmo            #+#    #+#             */
/*   Updated: 2024/08/14 18:14:38 by mouad            ###   ########.fr       */
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

void	generate_env(t_line *head, char **env)
{
	t_line	*tmp;
	char	**envir;
	int		i;

	tmp = head;
	i = 0;
	while (env[i])
		i++;
	envir = malloc(sizeof(char *) * (i + 1));
	if (!envir)
		return ;
	i = 0;
	while (env[i])
	{
		envir[i] = ft_strdup(env[i]);
		i++;
	}
	envir[i] = NULL;
	while (tmp)
	{
		tmp->env = envir;
		tmp = tmp->next;
	}
}

void	ft_free(char **arg, char *line)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
	free(line);
}

void	*parse(char *line, t_line *head, char **env)
{
	char	**arg;

	if (!checkspaces(line))
		return (NULL);
	if (!checkquotes(line))
		return (NULL);
	head = NULL;
	arg = ft_split(line, ' ');
	if (!arg)
		return (NULL);
	lexer(arg, head);
	generate_env(head, env);
	ft_free(arg, line);
}

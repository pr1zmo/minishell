/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:18:31 by prizmo            #+#    #+#             */
/*   Updated: 2024/08/11 20:53:06 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_list	*get_env(char	**env)
{
	int		i;
	t_list	*env_list;
	t_list	*tmp;

	i = 0;
	env_list = NULL;
	while (env[i])
	{
		tmp = malloc(sizeof(t_list));
		if (!tmp)
			error_exit("Malloc error");
		tmp->data = ft_strdup(env[i]);
		tmp->next = NULL;
		ft_lstadd_back(&env_list, tmp);
		i++;
	}
	return (env_list);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	int		is_up;
	char	*str;
	t_list	*env_list;

	is_up = 1;
	while (is_up)
	{
		env_list = get_env(env);
		str = readline("minishell> ");
		if (ft_strlen(str) > 0)
		{
			add_history(str);
			is_up = handle_command(str, env_list);
			free(str);
		}
		wait(0);
	}
	return (0);
}
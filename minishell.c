/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:18:31 by prizmo            #+#    #+#             */
/*   Updated: 2024/10/09 18:26:56 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i]);
	free(arr);
}

t_list	*set_env(char **envp)
{
	t_list	*env;
	t_list	*new;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		new = malloc(sizeof(t_list));
		if (!new)
			return (NULL);
		new->content = ft_strdup(envp[i]);
		new->next = env;
		env = new;
		i++;
	}
	return (env);
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	char	*str;
	t_parse	data;
	t_line	*head;

	if (ac != 1)
		return (printf("minishell doesn't take any arguments\n"), 1);
	head = NULL;
	while (1)
	{
		str = readline("\x1b[36mminishell->\x1b[0m ");
		if (ft_strlen(str) > 0)
		{
			add_history(str);
			parse(str, &head, env, &data);
			while (head)
			{
				printf("  this is a node\n");
				printf("------------------\n");
				for (int i = 0;head->str[i];i++)
					printf("str: %s\n", head->str[i]);
				printf("type: %i\n", head->type);
				head = head->next;
			}
		}
	}
	return (0);
}

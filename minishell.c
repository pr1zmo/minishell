/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:50:09 by prizmo            #+#    #+#             */
/*   Updated: 2024/06/06 15:43:04 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_env(char	**env)
{
    int		i;
    t_list	*env_list;
    t_list	*tmp;

    i = 0;
    env_list = NULL;
    while (env[i])
    {
        tmp = (t_list*)malloc(sizeof(t_list));
        if (!tmp)
			return (NULL);
        tmp->data = env[i];
        tmp->next = env_list;
        env_list = tmp;
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
    t_list	*tmp;

    is_up = 1;
    while (is_up >= 0)
    {
        env_list = get_env(env);
        str = readline("minishell> ");
        add_history(str);
        is_up = handle_command(str, env_list);
        wait(0);
    }
    return (0);
}
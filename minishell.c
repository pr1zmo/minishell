/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouad <mouad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:18:31 by prizmo            #+#    #+#             */
/*   Updated: 2024/08/14 17:56:06 by mouad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	int		is_up;
	char	*str;
	t_data	*data;
	t_line	*head;

	is_up = 1;
	ft_strjoin("PWD=", getcwd(NULL, 0));
	while (is_up)
	{
		str = readline("minishell> ");
		if (ft_strlen(str) > 0)
		{
			add_history(str);
			parse(str, head, env);
			// is_up = handle_command(str, data);
			free(str);
		}
		wait(0);
	}
	return (0);
}

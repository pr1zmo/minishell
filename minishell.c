/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:18:31 by prizmo            #+#    #+#             */
/*   Updated: 2024/08/16 12:14:06 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

int	main(int ac, char **av, char **env)
{
	(void)av;
	char	*str;
	t_data	*program;
	t_line	*head;

	if (ac != 1)
		return (printf("minishell doesn't take any arguments\n"), 1);
	program = malloc(sizeof(t_data));
	program->status = 1;
	
	while (1)
	{
		str = readline("\x1b[36mminishell->\x1b[0m ");
		if (ft_strlen(str) > 0)
		{
			add_history(str);
			parse(str, &head, env);
			printf("str: %s\n", head->str[0]);
			// for (int i = 0; head->str[i]; i++)
			// 	printf("STR: %s\n", head->str[i]);
			// program->status = handle_command(program);
		}
		wait(0);
	}
	free(program);
	return (0);
}

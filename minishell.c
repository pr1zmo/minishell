/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:18:31 by prizmo            #+#    #+#             */
/*   Updated: 2024/08/15 14:00:41 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			program->head = head;
			parse(str, head, env);
			program->status = handle_command(str, program);
		}
		wait(0);
	}
	free(program);
	return (0);
}

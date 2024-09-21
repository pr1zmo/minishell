/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:18:31 by prizmo            #+#    #+#             */
/*   Updated: 2024/09/21 14:09:29 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

int	main(int ac, char **av, char **env)
{
	(void)av;
	char	*str;
	// t_data	*program;
	t_line	*head;

	if (ac != 1)
		return (printf("minishell doesn't take any arguments\n"), 1);
	// program = malloc(sizeof(t_data));
	// program->status = 1;
	head = NULL;
	while (1)
	{
		str = readline("\x1b[36mminishell->\x1b[0m ");
		if (ft_strlen(str) > 0)
		{
			add_history(str);
			parse(str, &head, env);
			printf("%s\n", head->env[0]);
		}
	}
	return (0);
}

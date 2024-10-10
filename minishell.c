/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:18:31 by prizmo            #+#    #+#             */
/*   Updated: 2024/10/10 16:20:47 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)av;
	char	*str;
	t_parse	data;
	t_line	*head;
	t_cmd	*cmd;

	if (ac != 1)
		return (printf("minishell doesn't take any arguments\n"), 1);
	head = NULL;
	cmd = NULL;
	data.exit = 0;
	data.env = NULL;
	init(&data.env, env);
	while (1)
	{
		str = readline("\x1b[36mminishell->\x1b[0m ");
		if (ft_strlen(str) > 0)
		{
			add_history(str);
			data.exit = parse(str, &head, env, &data);
			if (!data.exit && head)
				get_final_list(&head, &cmd);
			while (cmd)
			{
				printf("  this is a node\n");
				printf("------------------\n");
				for (int i = 0;cmd->argv[i];i++)
					printf("str: %s\n", cmd->argv[i]);
				printf("type: %i\n", cmd->type);
				cmd = cmd->next;
			}
			free_line(&head);
			// while (head)
			// {
			// 	printf("  this is a node\n");
			// 	printf("------------------\n");
			// 	for (int i = 0;head->str[i];i++)
			// 		printf("str: %s\n", head->str[i]);
			// 	printf("type: %i\n", head->type);
			// 	head = head->next;
			// }
		}
	}
	return (0);
}

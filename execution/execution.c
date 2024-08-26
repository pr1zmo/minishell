/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:35:10 by prizmo            #+#    #+#             */
/*   Updated: 2024/08/25 20:44:29 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	reset_shell(t_data *data)
{
	// t_data	*data;

	// ft_simple_cmdsclear(&tools->simple_cmds);
	// free(tools->args);
	// if (tools->pid)
	// 	free(tools->pid);
	// free_arr(tools->paths);
	// implement_tools(tools);
	// tools->reset = true;
	minishell(data);
	return (1);
}

/* int	ft_error(int error, t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (error == 0)
		ft_putstr_fd("syntax error: cannot find a closing quote\n",
			STDERR_FILENO);
	reset_shell(data);
	return (EXIT_FAILURE);
}
*/

/* int	check_quotes(char *arg)
{
	int	i;
	int	k;
	int	l;

	i = 0;
	k = 0;
	l = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
			k++;
		else if (arg[i] == '\"')
			l++;
		i++;
	}
	if (k % 2 != 0)
		return (0);
	if (l % 2 != 0)
		return (0);
	return (1);
} */

int	minishell(t_data *data)
{
	char	*tmp;
	char	*str;

	data->line = readline(READLINE_MSG);
	if (data->line[0] == '\0')
		return (reset_shell(data));
	add_history(data->line);
	// if (!check_quotes(data->line))
	// 	return (ft_error(0, data));
	// if (!token_reader(data))
	// 	return (ft_error(1, data));
	parse(data->line, data->head, data->envp);
	// prepare_executor(data);
	reset_shell(data);
	return (1);
}

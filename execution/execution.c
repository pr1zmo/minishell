/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:35:10 by prizmo            #+#    #+#             */
/*   Updated: 2024/08/24 20:14:59 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	minishell(t_data *data)
{
	char	*tmp;

	data->args = readline(READLINE_MSG);
	tmp = ft_strtrim(data->args, " ");
	free(data->args);
	data->args = tmp;
	if (!data->args)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (data->args[0] == '\0')
		return (reset_tools(data));
	add_history(data->args);
	if (!count_quotes(data->args))
		return (ft_error(2, data));
	if (!token_reader(data))
		return (ft_error(1, data));
	parser(data);
	prepare_executor(data);
	reset_tools(data);
	return (1);
}

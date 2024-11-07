/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:35:10 by prizmo            #+#    #+#             */
/*   Updated: 2024/11/07 15:59:42 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_input(t_data *data)
{
	t_line	*temp;
	char	*cmd;
	int		i;

	temp = data->head;
	i = count_symbols(data);
	if (i == 0)
	{
		if (data->cmd)
			cmd = to_str(data->cmd->argv);
		if (!cmd)
			return (1);
		data->status = single_command(data, cmd);
	}
	else
	{
		set_cmd_strings(data->cmd);
		complex_command(data);
	}
	return (0);
}

int	minishell(t_data *data)
{
	t_line	*head;
	t_parse	p_data;
	t_cmd	*cmd;
	int		new_fd;

	while (1)
	{
		head = NULL;
		cmd = NULL;
		data->arg = readline(READLINE_MSG);
		data->envp_arr = set_list_arra(data->envp);
		// if (data->arg == NULL || data->arg[0] == '\0')
		// 	reset_shell(data);
		if (data->arg)
			add_history(data->arg);
		parse(data->arg, &head, data->envp_arr, &p_data);
		data->head = head;
		data->pid = -1;
		get_final_list(&head, &cmd);
		data->cmd = cmd;
		data->status = handle_input(data);
		g_exit_status = data->status;
		free_line(&head);
	}
	return (data->status);
}

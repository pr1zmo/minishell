/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:28:55 by zelbassa          #+#    #+#             */
/*   Updated: 2024/10/30 16:09:37 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_values(t_data *data)
{
	if (!data || !data->cmd)
		return (EXIT_SUCCESS);
	if (!data->cmd->cmd)
	{
		if (data->cmd->io_fds
			&& !check_infile_outfile(data->cmd->io_fds))
		{
			ft_putstr_fd("Error in the fds\n", 2);
			return (EXIT_FAILURE);
		}
		ft_putstr_fd("No cd\n",2 );
		return (EXIT_SUCCESS);
	}
	if (!create_pipes(data))
	{
		ft_putstr_fd("Failed to create pipes\n", 2);
		return (EXIT_FAILURE);
	}
	return (127);
}

int execute_cmds(t_cmd *cmd_list, char **envp, t_data *data)
{
	int		ret;

	ret = set_values(data);
	// if (ret != 127)
	// 	return (ret);
	if (!data->cmd->pipe_fd && !data->cmd->prev
		&& check_infile_outfile(cmd_list->io_fds))
	{
		redirect_io(data->cmd->io_fds);
		ret = exec_builtin(data, &cmd_list->cmd);
		restore_io(data->cmd->io_fds);
	}
	if (ret != 127)
		return (ret);
	return (handle_execute(data));
}

/* int	execute_command(t_data *data, t_cmd *cmd)
{
	int	ret;

	if (cmd->type != CMD)
	{
		return (1);
	}
	if (!check_infile_outfile(cmd->io_fds))
		exit(1);
	set_pipe_fds(data->cmd, cmd);
	redirect_io(cmd->io_fds);
	close_fds(data->cmd, false);
	// ret = exec_builtin(data, &cmd->cmd);
	if (ret != 127)
		return (ret);
	ret = exec_cmd(cmd->cmd, data->envp_arr, data);
	return (ret);
} */

int	execute_command(t_data *data, t_cmd *cmd)
{
	int	ret;

	if (cmd->type != CMD)
		return (1);
	if (!check_infile_outfile(cmd->io_fds))
		exit(1);
	set_pipe_fds(data->cmd, cmd);
	redirect_io(cmd->io_fds);
	close_fds(data->cmd, false);
/* 	if (ft_strchr(cmd->cmd, '/') == NULL)
	{
		ret = exec_builtin(data, &cmd->cmd);
		if (ret != 127)
			exit(1);
		ret = exec_cmd(cmd->cmd, data->envp_arr, data);
		if (ret != 127)
			exit(1);
	}
	else */
	return (exec_cmd(cmd->cmd, data->envp_arr, data));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:19:52 by zelbassa          #+#    #+#             */
/*   Updated: 2024/10/22 18:16:47 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_files(t_cmd *cmd, t_data *data)
{
	while (cmd)
	{
		if (cmd->type == CMD)
			init_command(cmd, data);
		else if (cmd->type == REDIR_OUT)
			init_write_to(cmd, data);
		else if (cmd->type == REDIR_IN)
			init_read_from(cmd, data);
		else if (cmd->type == APPEND)
			init_append(cmd, data);
		else if (cmd->type == HEREDOC)
			init_heredoc(cmd, data);
		cmd = cmd->next;
	}
}

bool	check_infile_outfile(t_io_fds *io)
{
	if (!io || (!io->infile && !io->outfile))
		return (true);
	else if ((io->infile && io->in_fd == -1)
		|| (io->outfile && io->out_fd == -1))
			return (false);
	return (true);
}

int	close_file(t_data *data)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	close_fds(data->cmd, false);
	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == data->pid)
			save_status = status;
		continue ;
	}
	return (status);
}

bool	remove_old_file_ref(t_io_fds *io, bool infile)
{
	if (infile == true && io->infile)
	{
		if (io->in_fd == -1 || (io->outfile && io->out_fd == -1))
			return (false);
		if (io->heredoc_name != NULL)
		{
			free(io->heredoc_name);
			io->heredoc_name = NULL;
			unlink(io->infile);
		}
		free(io->infile);
		close(io->in_fd);
	}
	else if (infile == false && (io && io->outfile))
	{
		if (io->out_fd == -1 || (io->infile && io->in_fd == -1))
			return (false);
		free(io->outfile);
		close(io->out_fd);
	}
	return (true);
}

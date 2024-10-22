
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ios.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:17:09 by zelbassa          #+#    #+#             */
/*   Updated: 2024/10/22 12:25:19 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_fds(t_cmd *cmds, bool close_backups)
{
	if (cmds->io_fds)
	{
		if (cmds->io_fds->in_fd != -1)
			close(cmds->io_fds->in_fd);
		if (cmds->io_fds->out_fd != -1)
			close(cmds->io_fds->out_fd);
	}
	close_pipe_fds(cmds, NULL);
}

bool	redirect_io(t_io_fds *io)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	if (io->in_fd != -1)
	{
		// ft_putstr_fd("in_fd is not yet set\n", 2);
		if (dup2(io->in_fd, STDIN_FILENO) == -1)
			ft_putstr_fd("dup2 error\n", 2);
	}
	if (io->out_fd != -1)
	{
		// ft_putstr_fd("out_fd is not yet set\n", 2);
		if (dup2(io->out_fd, STDOUT_FILENO) == -1)
			ft_putstr_fd("dup2 error\n", 2);
	}
	return (ret);
}

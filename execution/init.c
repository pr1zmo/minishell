/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:24:39 by zelbassa          #+#    #+#             */
/*   Updated: 2024/10/22 12:27:14 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_cmd(t_cmd *cmd)
{
	cmd->argv = NULL;
	cmd->cmd = NULL;
	cmd->pipe_fd = NULL;
	cmd->io_fds = NULL;
	cmd->type = 0;
	cmd->next = NULL;
	cmd->prev = NULL;
}

void	init_io(t_io_fds **io_fds)
{
	*io_fds = (t_io_fds *)malloc(sizeof(t_io_fds));
	if (!(*io_fds))
	{
		ft_putstr_fd("Failed to allocate memory\n", 2);
		return ;
	}
	(*io_fds)->in_fd = -1;
	(*io_fds)->out_fd = -1;
	(*io_fds)->infile = NULL;
	(*io_fds)->outfile = NULL;
	(*io_fds)->heredoc_name = NULL;
}

void	init_write_to(t_cmd *cmd, t_data *data)
{
	init_io(&cmd->io_fds);
	if (!remove_old_file_ref(cmd->io_fds, false))
		return ;
	cmd->io_fds->outfile = ft_strdup(cmd->argv[1]);
	cmd->io_fds->out_fd = open(cmd->io_fds->outfile, O_RDONLY | O_TRUNC | O_CREAT, 0644);
}

void	init_read_from(t_cmd *cmd, t_data *data)
{
	init_io(&cmd->io_fds);
	if (!remove_old_file_ref(cmd->io_fds, true))
		return ;
	cmd->io_fds->infile = ft_strdup(cmd->argv[1]);
	cmd->io_fds->in_fd = open(cmd->io_fds->infile, O_RDONLY);
	if (cmd->io_fds->in_fd == -1)
		ft_putstr_fd("infile error\n", 2);
}

void	init_append(t_cmd *cmd, t_data *data)
{
	init_io(&cmd->io_fds);
	cmd->io_fds->outfile = ft_strdup(cmd->argv[1]);
	cmd->io_fds->out_fd = open(cmd->io_fds->outfile, O_RDONLY | O_APPEND | O_CREAT, 0644);
}
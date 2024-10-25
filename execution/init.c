/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:24:39 by zelbassa          #+#    #+#             */
/*   Updated: 2024/10/25 20:52:23 by zelbassa         ###   ########.fr       */
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
	(*io_fds)->stdin_backup = -1;
	(*io_fds)->stdout_backup = -1;
}

// void	init_write_to(t_cmd *cmd, t_data *data)
// {
// 	init_io(&cmd->io_fds);
// 	if (!remove_old_file_ref(cmd->io_fds, false))
// 		return ;
// 	cmd->io_fds->outfile = ft_strdup(cmd->argv[1]);
// 	if (cmd->io_fds->outfile && cmd->io_fds->outfile[0] == '\0')
// 	{
// 		ft_error(3, data);
// 		return ;
// 	}
// 	cmd->io_fds->out_fd = open(cmd->io_fds->outfile, O_RDWR | O_TRUNC | O_CREAT, 0644);
// 	if (cmd->io_fds->out_fd == -1)
// 	{
// 		perror("file");
// 		return ;
// 	}
// 	// if (cmd->next && cmd->next->type != REDIR_OUT)
// 	// {
// 	// 	cmd->prev->io_fds->outfile = cmd->io_fds->outfile;
// 	// 	cmd->prev->io_fds->out_fd = cmd->io_fds->out_fd;
// 	// }
// }

void	init_write_to(t_cmd *cmd, t_data *data)
{
	char	*outfile;
	int		out_fd;

	init_io(&cmd->io_fds);
	if (!remove_old_file_ref(cmd->io_fds, false))
		return ;

	while (cmd)
	{
		// Check if command is an output redirection (>)
		if (cmd->type == REDIR_OUT)
		{
			init_io(&cmd->io_fds);
			// Close the previous out_fd if it is valid
			if (cmd->io_fds->out_fd != -1)
			{
				close(cmd->io_fds->out_fd);
				cmd->io_fds->out_fd = -1; // Reset the file descriptor
			}

			// Assign outfile to the current redirection target
			outfile = cmd->argv[1];
			cmd->io_fds->outfile = ft_strdup(outfile);

			// Open the new outfile and set out_fd
			out_fd = open(outfile, O_RDWR | O_TRUNC | O_CREAT, 0644);
			if (out_fd == -1)
			{
				perror("file");
				return;
			}

			cmd->io_fds->out_fd = out_fd;
		}

		// Move to the next command
		cmd = cmd->next;
	}
}


void	init_append(t_cmd *cmd, t_data *data)
{
	init_io(&cmd->io_fds);
	if (!remove_old_file_ref(cmd->io_fds, false))
		return ;
	cmd->io_fds->outfile = ft_strdup(cmd->argv[1]);
	cmd->io_fds->out_fd = open(cmd->io_fds->outfile, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (cmd->io_fds->out_fd == -1)
	{
		perror("open");
		return ;	
	}
	// cmd->prev->io_fds->outfile = cmd->io_fds->outfile;
	// cmd->prev->io_fds->out_fd = cmd->io_fds->out_fd;
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
	// cmd->prev->io_fds->infile = cmd->io_fds->infile;
	// cmd->prev->io_fds->in_fd = cmd->io_fds->in_fd;
}

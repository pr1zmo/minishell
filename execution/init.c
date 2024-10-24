/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:24:39 by zelbassa          #+#    #+#             */
/*   Updated: 2024/10/24 23:04:41 by zelbassa         ###   ########.fr       */
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
	cmd->io_fds->out_fd = open(cmd->io_fds->outfile, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (cmd->io_fds->out_fd == -1)
	{
		perror("file");
		return ;
	}
	// cmd->prev->io_fds->outfile = cmd->io_fds->outfile;
	// cmd->prev->io_fds->out_fd = cmd->io_fds->out_fd;
}

/* void	init_write_to(t_cmd *cmd, t_data *data)
{
	init_io(&cmd->io_fds);
	if (!remove_old_file_ref(cmd->io_fds, false))
		return ;

	// Open the output file
	cmd->io_fds->outfile = ft_strdup(cmd->argv[1]);
	cmd->io_fds->out_fd = open(cmd->io_fds->outfile, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (cmd->io_fds->out_fd == -1)
	{
		perror("file");
		return ;
	}

	// Handle the case where there is a next command
	if (cmd->next)
	{
		init_io(&cmd->next->io_fds);
		// If the next command is not a redirection, propagate the file descriptor
		if (cmd->next->type != REDIR_OUT)
		{
			cmd->prev->io_fds->outfile = cmd->io_fds->outfile;
			cmd->prev->io_fds->out_fd = cmd->io_fds->out_fd;
		}
		else
		{
			cmd->next->io_fds->outfile = ft_strdup(cmd->next->argv[1]);
			cmd->next->io_fds->out_fd = open(cmd->next->io_fds->outfile, O_RDWR | O_TRUNC | O_CREAT, 0644);
			if (cmd->next->io_fds->out_fd == -1)
			{
				perror("file");
				return ;
			}
			cmd->prev->io_fds->outfile = cmd->next->io_fds->outfile;
			cmd->prev->io_fds->out_fd = cmd->next->io_fds->out_fd;
		}
	}
	else
	{
		// If there is no next command, propagate the file descriptor to the previous command
		cmd->prev->io_fds->outfile = cmd->io_fds->outfile;
		cmd->prev->io_fds->out_fd = cmd->io_fds->out_fd;
	}
} */

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

/* void	init_read_from(t_cmd *cmd, t_data *data)
{
    init_io(&cmd->io_fds);
    if (!remove_old_file_ref(cmd->io_fds, true))
        return ;

    // Open the input file
    cmd->io_fds->infile = ft_strdup(cmd->argv[1]);
    cmd->io_fds->in_fd = open(cmd->io_fds->infile, O_RDONLY);
    if (cmd->io_fds->in_fd == -1)
    {
        ft_putstr_fd("infile error\n", 2);
        return ;
    }
    // Handle the case where there is a next command
    if (cmd->next)
    {
		init_io(&cmd->next->io_fds);
        // If the next command is not a redirection, propagate the file descriptor
        if (cmd->next->type != REDIR_IN)
        {
            cmd->prev->io_fds->infile = cmd->io_fds->infile;
            cmd->prev->io_fds->in_fd = cmd->io_fds->in_fd;
        }
        else
        {
            // If the next command is a redirection, open the next input file
            cmd->next->io_fds->infile = ft_strdup(cmd->next->argv[1]);
            cmd->next->io_fds->in_fd = open(cmd->next->io_fds->infile, O_RDONLY);
            if (cmd->next->io_fds->in_fd == -1)
            {
                ft_putstr_fd("infile error\n", 2);
                return ;
            }
            cmd->prev->io_fds->infile = cmd->next->io_fds->infile;
            cmd->prev->io_fds->in_fd = cmd->next->io_fds->in_fd;
        }
    }
    else
    {
        // If there is no next command, propagate the file descriptor to the previous command
        cmd->prev->io_fds->infile = cmd->io_fds->infile;
        cmd->prev->io_fds->in_fd = cmd->io_fds->in_fd;
    }
} */

/* void	init_append(t_cmd *cmd, t_data *data)
{
    init_io(&cmd->io_fds);
    if (!remove_old_file_ref(cmd->io_fds, false))
        return ;

    // Open the output file in append mode
    cmd->io_fds->outfile = ft_strdup(cmd->argv[1]);
    cmd->io_fds->out_fd = open(cmd->io_fds->outfile, O_RDWR | O_APPEND | O_CREAT, 0644);
    if (cmd->io_fds->out_fd == -1)
    {
        perror("open");
        return ;	
    }

    // Handle the case where there is a next command
    if (cmd->next)
    {
		init_io(&cmd->next->io_fds);
        // If the next command is not a redirection, propagate the file descriptor
        if (cmd->next->type != REDIR_OUT && cmd->next->type != APPEND)
        {
            cmd->prev->io_fds->outfile = cmd->io_fds->outfile;
            cmd->prev->io_fds->out_fd = cmd->io_fds->out_fd;
        }
        else
        {
            // If the next command is a redirection, open the next output file
            cmd->next->io_fds->outfile = ft_strdup(cmd->next->argv[1]);
            cmd->next->io_fds->out_fd = open(cmd->next->io_fds->outfile, O_RDWR | O_APPEND | O_CREAT, 0644);
            if (cmd->next->io_fds->out_fd == -1)
            {
                perror("open");
                return ;
            }
            cmd->prev->io_fds->outfile = cmd->next->io_fds->outfile;
            cmd->prev->io_fds->out_fd = cmd->next->io_fds->out_fd;
        }
    }
    else
    {
        // If there is no next command, propagate the file descriptor to the previous command
        cmd->prev->io_fds->outfile = cmd->io_fds->outfile;
        cmd->prev->io_fds->out_fd = cmd->io_fds->out_fd;
    }
} */
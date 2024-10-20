/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:35:10 by prizmo            #+#    #+#             */
/*   Updated: 2024/10/20 22:49:59 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_infile_outfile(t_io_fds *io)
{
	if (!io || (!io->infile && !io->outfile))
	{
		return (true);
	}
	else if ((io->infile && io->in_fd == -1)
		|| (io->outfile && io->out_fd == -1))
		{
			return (false);
		}
	return (true);
}

void	exec_cmd(char *av, char **env, t_data *data)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	if (cmd[0][0] == '/')
		path = ft_strdup(cmd[0]);
	else
	{
		if (builtin(cmd[0]))
		{
			exec_builtin(data, cmd);
			return ;
		}
		path = get_full_cmd(cmd[0], env);
	}
	if (!path)
		perror(cmd[0]);
	if (execve(path, cmd, env) == -1)
		return ;
}

int	single_command(t_data *data, char *cmd)
{
	t_line	*temp = data->head;
	int pid;

	while (temp)
	{
		if (temp->next && temp->next->type == 7)
			temp = temp->next;
		pid = fork();
		if (pid == -1)
			return (ft_error(1, data));
		if (pid == 0)
			exec_cmd(cmd, data->envp_arr, data);
		waitpid(0, NULL, 0);
		temp = temp->next;
	}
	return (0);
}


void	close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd)
{
	while (cmds)
	{
		if (cmds != skip_cmd && cmds->pipe_fd)
		{
			close(cmds->pipe_fd[0]);
			close(cmds->pipe_fd[1]);
		}
		cmds = cmds->next;
	}
}

bool	set_pipe_fds(t_cmd *cmds, t_cmd *c)
{
	if (!c)
		return (false);
	if (c->prev && c->prev->pipe_output)
		dup2(c->prev->pipe_fd[0], STDIN_FILENO);
	if (c->pipe_output)
		dup2(c->pipe_fd[1], STDOUT_FILENO);
	close_pipe_fds(cmds, c);
	return (true);
}

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

static void	init_io(t_io_fds **io_fds)
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

bool	redirect_io(t_io_fds *io)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	if (io->in_fd != -1)
	{
		ft_putstr_fd("in_fd is not yet set\n", 2);
		if (dup2(io->in_fd, STDIN_FILENO) == -1)
			ft_putstr_fd("dup2 error\n", 2);
	}
	if (io->out_fd != -1)
	{
		ft_putstr_fd("out_fd is not yet set\n", 2);
		if (dup2(io->out_fd, STDOUT_FILENO) == -1)
			ft_putstr_fd("dup2 error\n", 2);
	}
	return (ret);
}

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
	// debug();
	ft_putstr_fd("Reached the execution\n", 2);
	if (ft_strchr(cmd->cmd, '/') == NULL)
	{
		ret = exec_builtin(data, &cmd->cmd);
		if (ret != 127)
			exit(1);
		ret = single_command(data, cmd->cmd);
		if (ret != 127)
			exit(1);
	}
	ret = single_command(data, cmd->cmd);
	return (ret);
}

bool	create_pipes(t_data *data)
{
	int			*fd;
	t_cmd		*tmp;

	tmp = data->cmd;
	while (tmp)
	{
		if (tmp->pipe_fd || (tmp->prev && tmp->prev->pipe_fd))
		{
			fd = malloc(sizeof * fd * 2);
			if (!fd || pipe(fd) != 0)
			{
				return (false);
			}
			tmp->pipe_fd = fd;
		}
		tmp = tmp->next;
	}
	return (true);
}

static int	set_values(t_data *data)
{
	if (!data || !data->cmd)
		return (EXIT_SUCCESS);
	if (!data->cmd->cmd)
	{
		if (data->cmd->io_fds
			&& !check_infile_outfile(data->cmd->io_fds))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!create_pipes(data))
	{
		ft_putstr_fd("Failed to create pipes\n", 2);
		return (EXIT_FAILURE);
	}
	return (127);
}

static int	handle_execute(t_data *data)
{
	t_cmd	*cmd;
	int		pid;

	cmd = data->cmd;
	pid = -1;
	while (pid != 0 && cmd)
	{
		pid = fork();
		if (pid == -1)
			ft_putstr_fd("fork error\n", 2);
		else if (pid == 0)
		{
			execute_command(data, cmd);
		}
		cmd = cmd->next;
	}
	return (1);
}

int execute_cmds(t_cmd *cmd_list, char **envp, t_data *data)
{
	t_cmd	*temp = cmd_list;
	int		ret;

	ret = set_values(data);
	// show_command_info(temp);
	if (check_infile_outfile(temp->io_fds))
	{
		redirect_io(data->cmd->io_fds);
		ret = exec_builtin(data, &temp->cmd);
	}
	if (ret == 127)
		return (ret);
	ft_putstr_fd("\033[31mexecute_cmds function\033[0m\n", 2);
	return (handle_execute(data));
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

void	handle_pipe(t_cmd **cmd, t_data *data)
{
	(*cmd)->pipe_output = 1;
	init_io(&(*cmd)->io_fds);
	(*cmd)->pipe_fd = (int *)malloc(sizeof(int) * 2);
	(*cmd) = (*cmd)->next;
}

static void	open_outfile_trunc(t_io_fds **io, char *file)
{
	if (!remove_old_file_ref((*io), false))
		return ;

	// Check if ft_strdup returns NULL
	(*io)->outfile = ft_strdup(file);
	if ((*io)->outfile == NULL)
	{
		ft_putstr_fd("Ambiguous redirect\n", 2);
		return;
	}

	(*io)->out_fd = open((*io)->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if ((*io)->out_fd == -1)
		ft_putstr_fd("outfile error\n", 2);
}

static void	handle_write_to(t_cmd **cmd, t_data *data)
{
	init_io(&(*cmd)->io_fds);
	open_outfile_trunc(&(*cmd)->io_fds, (*cmd)->argv[1]);
	(*cmd) = (*cmd)->next;  // Move to the next command
}

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

void	change_first_io(t_io_fds **io)
{
	(*io) = (t_io_fds *)malloc(sizeof(t_io_fds));
	(*io)->in_fd = 99;
}

void	change_second_io(t_io_fds **io)
{
	(*io) = (t_io_fds *)malloc(sizeof(t_io_fds));
	(*io)->in_fd = 88;
}

void	init_command(t_cmd *cmd, t_data *data)
{
	init_io(&cmd->io_fds);
	if (cmd->next && cmd->next->type == CMD)
	{
		cmd->pipe_output = true;
	}
}

void	init_write_to(t_cmd *cmd, t_data *data)
{
	init_io(&cmd->io_fds);
	cmd->io_fds->outfile = ft_strdup(cmd->argv[1]);
	cmd->io_fds->out_fd = open(cmd->io_fds->outfile, O_RDONLY | O_TRUNC | O_CREAT, 0644);
}

void	init_read_from(t_cmd *cmd, t_data *data)
{
	init_io(&cmd->io_fds);
	cmd->io_fds->infile = ft_strdup(cmd->argv[1]);
	printf("a;ldksjf: %s\n", cmd->argv[1]);
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

static void	create_files_refined(t_cmd *cmd, t_data *data)
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
		cmd = cmd->next;
	}
}

void	complex_command(t_data *data)
{
	t_line	*temp = data->head;

	if (data->cmd)
	{
		// create_files(&data->cmd, data);
		create_files_refined(data->cmd, data);
		execute_cmds(data->cmd, data->envp_arr, data);
		show_command_info(data->cmd);
	}
	else
		ft_putstr_fd("No command found\n", 2);
}

int	handle_input(t_data *data)
{
	t_line	*temp = data->head;
	char	*cmd;

	int i = count_symbols(data);
	if (i == 0)
	{
		cmd = array_to_string(temp);
		single_command(data, cmd);
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

	while (1)
	{
		head = NULL;
		cmd = NULL;
		data->arg = readline(READLINE_MSG);
		data->envp_arr = set_list_arra(data->envp);
		if (data->arg == NULL || data->arg[0] == '\0')
			reset_shell(data);
		add_history(data->arg);
		parse(data->arg, &head, data->envp_arr, &p_data);
		data->head = head;
		get_final_list(&head, &cmd);
		data->cmd = cmd;
		// show_cmd(data->cmd);
		handle_input(data);
		if (data->status == 0)
			break ;
	}
	return (1);
}

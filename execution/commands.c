/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:21:30 by zelbassa          #+#    #+#             */
/*   Updated: 2024/10/28 18:19:53 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_command(t_cmd *cmd, t_data *data)
{
	init_io(&cmd->io_fds);
	if (cmd->next && cmd->next->type == CMD)
	{
		cmd->pipe_output = true;
	}
}

int	handle_execute(t_data *data)
{
	t_cmd	*cmd;
	int		pid;

	cmd = data->cmd;
	while (data->pid != 0 && cmd)
	{
		if (cmd->type == CMD)
		{
			data->pid = fork();
			if (data->pid == -1)
				ft_putstr_fd("fork error\n", 2);
		}
		if (data->pid == 0 || cmd->type != CMD)
			execute_command(data, cmd);
		cmd = cmd->next;
	}
	return (close_file(data));
}

int	exec_cmd(char *av, char **env, t_data *data)
{
	char	**cmd;
	char	*path;
 
	cmd = ft_split(av, ' ');
	ft_putstr_fd("ENTRING HERE\n", 2);
	if (cmd[0][0] == '/')
		path = ft_strdup(cmd[0]);
	else if (cmd[0][0] != '\0')
	{
		if (builtin(cmd[0]))
		{
			ft_putstr_fd("Builtin indeed\n", 2);
			return (exec_builtin(data, cmd));
		}
		path = get_full_cmd(cmd[0], env);
	}
	if (!path)
		return (ft_error(7, data), 1);
	if (execve(path, cmd, env) == -1)
	{
		perror("execve");
		return (1);
	}
	return (0);
}

int	single_command(t_data *data, char *cmd)
{
	t_line	*temp = data->head;
	int pid;

	while (temp)
	{
		if (temp->next && temp->next->type == 7)
			temp = temp->next;
		data->pid = fork();
		if (data->pid == -1)
			return (ft_error(1, data));
		if (data->pid == 0)
		{
			exec_cmd(cmd, data->envp_arr, data);
		}
		waitpid(0, NULL, 0);
		temp = temp->next;
	}
	return (0);
}

static void	print_cmd_args(t_cmd *cmd)
{
	int	i;

	if (!cmd->argv)
		return ;
	i = 0;
	while (cmd->argv[i])
	{
		printf("\tArgs[%d] = %s\n", i, cmd->argv[i]);
		i++;
	}
}

static void	print_cmd_io(t_cmd *cmd)
{
	if (!cmd->io_fds)
		return ;
	if (cmd->io_fds->infile)
	{
		printf("\tInfile: %s\n", cmd->io_fds->infile);
		printf("\t\tfd_in: %d\n", cmd->io_fds->in_fd);
	}
	if (cmd->io_fds->heredoc_name)
		printf("\tHeredoc delimiter: %s\n", cmd->io_fds->heredoc_name);
	if (cmd->io_fds->outfile)
	{
		printf("\tOutfile: %s\n", cmd->io_fds->outfile);
		printf("\t\tfd_in: %d\n", cmd->io_fds->out_fd);
	}
}

static void	print_cmd_list(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	printf("\n---- COMMAND LIST\n");
	while (cmd)
	{
		printf("--- Command = %s\n", cmd->cmd);
		print_cmd_args(cmd);
		printf("\tPipe_output = %d\n", cmd->pipe_output);
		print_cmd_io(cmd);
		if (cmd->prev == NULL)
			printf("\tprev = NULL\n");
		else
			printf("\tprev = %s\n", cmd->prev->cmd);
		if (cmd->next == NULL)
			printf("\tnext = NULL\n");
		else
			printf("\tnext = %s\n", cmd->next->cmd);
		printf("\n");
		cmd = cmd->next;
	}
	printf("\n");
}

void print_open_fds(t_cmd *cmd)
{
	t_cmd	*temp = cmd;

	while (temp)
	{
		if (temp->io_fds)
		{
			if (temp->io_fds->in_fd != -1)
				printf("Infile: %s\n", temp->io_fds->infile);
			if (temp->io_fds->out_fd != -1)
				printf("Outfile: %s\n", temp->io_fds->outfile);
		}
		temp = temp->next;
	}
}

void	complex_command(t_data *data)
{
	t_line	*temp = data->head;

	if (data->cmd)
	{
		create_files(data->cmd, data);
		// show_command_info(data->cmd);
		execute_cmds(data->cmd, data->envp_arr, data);
	}
	else
		ft_putstr_fd("No command found\n", 2);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:35:10 by prizmo            #+#    #+#             */
/*   Updated: 2024/08/29 14:05:07 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	reset_shell(t_data *data)
{
	// t_data	*data;

	// ft_simple_cmdsclear(&tools->simple_cmds);
	// free(tools->args);
	// if (tools->pid)
	// 	free(tools->pid);
	// free_arr(tools->paths);
	// implement_tools(tools);
	// tools->reset = true;
	data->head = data->head->next;
	minishell(data);
	return (1);
}

int	ft_error(int error, t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (error == 0)
		ft_putstr_fd("syntax error: cannot find a closing quote\n",
			STDERR_FILENO);
	else if (error == 1)
		ft_putstr_fd("error when forking\n",
			STDERR_FILENO);
	else if (error == 2)
		ft_putstr_fd("error finding command\n", STDERR_FILENO);
	else if (error == 3)
		ft_putstr_fd("Could not find corresponding path\n", STDERR_FILENO);
	reset_shell(data);
	return (EXIT_FAILURE);
}

/* static char	*get_full_cmd(char *av, char **env, t_data *data)
{
	int		i;
	char	*result;
	char	*full_cmd;
	char	**path;

	i = 0;
	path = ft_split(getenv("PATH"), ':');
	// printf("%s\n", path[1]);
	if (!path)
		ft_error(3, data);
	while (path[i])
	{
		result = ft_strjoin(path[i], "/");
		full_cmd = ft_strjoin(result, av);
		// printf("full command = %s\n", full_cmd);
		// free(result);
		if (access(full_cmd, X_OK | F_OK) == 0)
		{
			// free_arr(path);
			return (full_cmd);
		}
		// free(full_cmd);
		i++;
	}
	// free_arr(path);
	return (NULL);
} */

/* int	check_quotes(char *arg)
{
	int	i;
	int	k;
	int	l;

	i = 0;
	k = 0;
	l = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
			k++;
		else if (arg[i] == '\"')
			l++;
		i++;
	}
	if (k % 2 != 0)
		return (0);
	if (l % 2 != 0)
		return (0);
	return (1);
} */

void	printa(char *message, char **str)
{
	printf("%s: ", message);
	for (int i = 0; str[i]; i++)
		printf("%s\n", str[i]);
}

/* void	execute_cmd(char **cmd, t_data *data)
{
	char	*full_cmd;

	full_cmd = NULL;
	if (cmd[0][0] == '/')
		full_cmd = ft_strdup(cmd[0]);
	else
		full_cmd = get_full_cmd(cmd[0], data->envp, data);
	if (!full_cmd)
		ft_error(2, data);
	if (execve(full_cmd, cmd, data->envp) == -1)
		ft_error(2, data);
} */

/* void	single_command(t_data *data)
{
	int		pid;
	t_line	*temp;

	pid = fork();
	temp = data->head;
	cmd = NULL;
	if (pid < 0)
		ft_error(1, data);
	if (pid == 0)
	{
		cmd_args = ft_split(cmd, ' ');
		if (!cmd_args)
			ft_error(2, data);
		execute_cmd(cmd_args, data);
	}
	waitpid(pid, &status, 0);
	int err;
	if (WIFEXITED(status))
		err = WEXITSTATUS(status);
	free(cmd);
} */

int	count_pipes(t_data *data)
{
	int	i;
	int	k;
	t_line	*temp;

	i = 0;
	k = 0;
	temp = data->head;
	while (temp)
	{
		while (temp->str[i])
		{
			printf("The alleged pipe: %d", temp->type);
			if (temp->type == 1)
				k++;
			i++;
		}
		temp = temp->next;
	}
	free(temp);
	return (k);
}

int	handle_input(t_data *data)
{
	t_data	*temp;

	temp = (t_data *)malloc(sizeof(t_data));
	// temp = data;
	// data->pipes = count_pipes(temp);
	printf("pipes: %d\n", data->pipes);
	// single_command(data);
	// if (data->pipes == 0)
	// else
		// printf("FOUND PIPE");
	return (0);
}

void	debug()
{
	static int count;
	
	count += 1;
	printf("Here: %d\n", count);
}

void print_temp(t_data *data)
{
	t_line *temp = data->head;
	while (temp)
	{
		printf("Str: ");
		printf("%s", temp->str[0]);
		// if (temp->str)
		// {
		// 	printa("NONE", temp->str);
		// }
		// else
		// {
		// 	printf("(null)");
		// }
		printf("\n-----\ntype: %d\n----\n", temp->type);
		temp = temp->next;
	}
}

int	minishell(t_data *data)
{
	char	*str;

	data->args = readline(READLINE_MSG);
	debug();
	if (data->args == NULL || data->args[0] == '\0')
		return (reset_shell(data));
	debug();
	add_history(data->args);
	parse(data->line, &data->head, data->envp);
	printf("SSSSSSs: %s\n", data->head->str[0]);
	print_temp(data);
	handle_input(data);
	reset_shell(data);
	return (1);
}

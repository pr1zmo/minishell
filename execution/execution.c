/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:35:10 by prizmo            #+#    #+#             */
/*   Updated: 2024/08/29 15:24:03 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	reset_shell(t_data *data)
{
	// data->head = data->head->next;
	if (data->arg)
	{
		// free(data->arg);
		data->arg = NULL;
	}
	rl_clear_history();
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

void	printa(char *message, char **str)
{
	printf("%s: ", message);
	for (int i = 0; str[i]; i++)
		printf("%s\n", str[i]);
}

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
	// free(temp);
	return (k);
}

void	debug()
{
	static int count;
	
	count += 1;
	printf("Here: %d\n", count);
}

static char	*get_full_cmd(char *av, char **env)
{
	int		i;
	char	*result;
	char	*full_cmd;
	char	**path;

	i = 0;
	path = ft_split(getenv("PATH"), ':');
	if (!path)
		perror("Path error");
	while (path[i])
	{
		// result = ft_strjoin(path[i], "/");
		full_cmd = ft_strjoin(ft_strjoin(path[i], "/"), av);
		// free(result);
		if (access(full_cmd, X_OK | F_OK) == 0)
			return (full_cmd);
		// free(full_cmd);
		i++;
	}
	// free_arr(path);
	return (NULL);
}

void	exec_cmd(char *av, char **env)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	if (cmd[0][0] == '/')
		path = ft_strdup(cmd[0]);
	else
		path = get_full_cmd(cmd[0], env);
	if (!path)
	{
		// cmd = NULL;
		// free_arr(cmd);
		perror(cmd[0]);
		exit(1);
	}
	if (execve(path, cmd, env) == -1)
	{
		// cmd = NULL;
		// free_arr(cmd);
		perror("execve");
		return ;
	}
}

int	handle_input(t_data *data)
{
	t_line	*temp = data->head;
	char	*cmd = temp->str[0];
	int		pid;

	while (temp)
	{
		pid = fork();
		if (pid == -1)
			return (ft_error(1, data));
		if (pid == 0)
			exec_cmd(cmd, data->envp);
		waitpid(0, NULL, 0);
		temp = temp->next;
	}
	return (0);
}

int	minishell(t_data *data)
{
	char	*str;

	data->head = NULL;
	data->arg = readline(READLINE_MSG);
	if (data->arg == NULL || data->arg[0] == '\0')
		return (reset_shell(data));
	add_history(data->arg);
	parse(data->arg, &data->head, data->envp);
	// print_temp(data);
	handle_input(data);
	reset_shell(data);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:35:10 by prizmo            #+#    #+#             */
/*   Updated: 2024/08/26 22:22:18 by prizmo           ###   ########.fr       */
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
	else if (error = 2)
		ft_putstr_fd("error finding command\n", STDERR_FILENO);
	else if (error = 3)
		ft_putstr_fd("Could not find corresponding path\n", STDERR_FILENO);
	reset_shell(data);
	return (EXIT_FAILURE);
}

static char	*get_full_cmd(char *av, char **env, t_data *data)
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
}

/* static char	*get_full_cmd(char *av, char **env, t_data *data)
{
	int		i;
	char	*result;
	char	*full_cmd;
	char	**path;

	i = 0;
	path = ft_split(getenv("PATH"), ':');
	printf("path[i] %s\n", path[0]);
	if (!path)
		ft_error(3, data);
	while (path[i])
	{
		printf("1");
		result = ft_strjoin(path[i], "/");
		printf("12");
		full_cmd = ft_strjoin(result, av);
		printf("13");
		free(result);
		printf("14");
		if (access(full_cmd, X_OK | F_OK) == 0)
		{
			printf("Found access! %s\n", full_cmd);
			return (full_cmd);
		}
		printf("15");
		free(full_cmd);
		i++;
		printf("16");
		printf("Starting again\n");
	}
	printf("ZIZI\n");
	free_arr(path);
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

void	execute_cmd(char **cmd, t_data *data)
{
	char	*full_cmd;

	full_cmd = NULL;
	// printf("full command: %s\n", cmd[0]);
	if (cmd[0][0] == '/')
		full_cmd = ft_strdup(cmd[0]);
	else
		full_cmd = get_full_cmd(cmd[0], data->envp, data);
	if (!full_cmd)
		ft_error(2, data);
	if (execve(full_cmd, cmd, data->envp) == -1)
		ft_error(2, data);
}

void	single_command(t_data *data)
{
	int		pid;
	int		status;
	t_line	*temp;

	pid = fork();
	temp = (t_line *)malloc(sizeof(t_line));
	temp = data->head;
	if (pid < 0)
		ft_error(1, data);
	if (pid == 0)
		execute_cmd(temp->str, data);
	waitpid(pid, &status, 0);
	int err;
	if (WIFEXITED(status))
		err = WEXITSTATUS(status);
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
			if (temp->type == 1)
				k++;
			i++;
		}
		temp = temp->next;
	}
	free(temp);
	return (k);
}

// int	count_pipes(t_data *data)
// {
// 	int	i;
// 	int	k;

// 	i = 0;
// 	k = 0;
// 	while (data->head)
// 	{
// 		while (data->head->str[i])
// 		{
// 			printf("str: %s +++++ type: %d\n", data->head->str[i], data->head->type);
// 			if (data->head->type == 1)
// 				k++;
// 			i++;
// 		}
// 		data->head = data->head->next;
// 	}
// 	return (k);
// }

int	handle_input(t_data *data)
{
	data->pipes = count_pipes(data);
	printf("pipes: %d\n", data->pipes);
	single_command(data);
	// if (data->pipes == 0)
	// else
		// printf("FOUND PIPE");
}

int	minishell(t_data *data)
{
	char	*str;

	data->line = readline(READLINE_MSG);
	if (data->line == NULL || data->line[0] == '\0')
		return (reset_shell(data));
	add_history(data->line);
	parse(data->line, &data->head, data->envp);
	while (data->head)
	{
		for (int i = 0; data->head->str[i]; i++)
			printf("str: %s type:%d\n--------------------------\n", data->head->str[i], data->head->type);
		data->head = data->head->next;
	}
	handle_input(data);
	reset_shell(data);
	return (1);
}

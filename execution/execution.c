/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:35:10 by prizmo            #+#    #+#             */
/*   Updated: 2024/10/01 23:53:47 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printa(char *message, char **arr);

// char	**realloc_env(t_data *data, int size)
// {
// 	char	**new_env;
// 	int		i;

// 	new_env = malloc((size + 1) * sizeof * new_env);
// 	if (!new_env)
// 		return (NULL);
// 	i = 0;
// 	while (data->envp[i] && i < size)
// 	{
// 		new_env[i] = ft_strdup(data->envp[i]);
// 		if (data->envp[i])
// 		{
// 			free(data->envp[i]);
// 			data->envp[i] = NULL;
// 		}
// 		i++;
// 	}
// 	free(data->envp);
// 	return (new_env);
// }

char *ft_getenv(char *name, t_data *data)
{
	int 	i;
	t_list	*temp = data->envp;

	if (!name || !data || !data->envp)
		return NULL;
	i = 0;
	while (temp)
	{
		if (ft_strncmp(temp->content, name, ft_strlen(name)))
			return (ft_strdup(temp->content));
		temp = temp->next;
	}
	return (NULL);
}

int	reset_shell(t_data *data)
{
	// data->head = data->head->next;
	if (data->arg)
	{
		free(data->arg);
		data->arg = NULL;
	}
	// rl_clear_history();
	minishell(data);
	return (1);
}

int	modify_env_value(char *name, char *new_value, t_data *data)
{
	char *str;

	str = getenv(name);
	if (!str)
		perror("getenv");
	else
		set_list_var(data, name, new_value);
	return (1);
}

int	builtin(char *cmd)
{
	char	*builtin[8];
	int		i;

	i = 0;
	builtin[0] = "echo";
	builtin[1] = "cd";
	builtin[2] = "pwd";
	builtin[3] = "export";
	builtin[4] = "unset";
	builtin[5] = "env";
	builtin[6] = "exit";
	builtin[7] = NULL;
	while (i < 7)
	{
		if (ft_strncmp(builtin[i], cmd, 0) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	exec_builtin(t_data *data, char **cmd)
{
	int	res;

	res = 0;
	printf("Executing the builtins\n");
	if (ft_strncmp(cmd[0], "pwd", 0) == 0)
		res = ft_pwd(data, cmd);
	else if (ft_strncmp(cmd[0], "env", 0) == 0)
		res = ft_env(data, cmd);
	else if (ft_strncmp(cmd[0], "echo", 0) == 0)
		res = ft_echo(data, cmd);
	else if (ft_strncmp(cmd[0], "cd", 0) == 0)
		res = ft_cd(data, cmd);
 
	else if (ft_strncmp(cmd[0], "export", 0) == 0)
		res = ft_export(data, cmd);
	return (res);
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

void	debug();

void set_list_var(t_data *data, char *name, char *new_value)
{
	int 	len;
	t_list *current;
	char	*temp;

	len = ft_strlen(name);
	current = data->envp;
	while (current)
	{
		if (ft_strncmp(current->content, name, len) == 0)
		{
			free(current->content);
			current->content = NULL;
			temp = ft_strjoin(name, "=");
			current->content = ft_strjoin(temp, new_value);
			if (!current->content)
			{
				ft_putstr_fd("Error: Memory allocation failed\n", STDERR_FILENO);
				return;
			}
			break;
		}
		current = current->next;
	}
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
	// char	*result;
	char	*full_cmd;
	char	**path;

	i = 0;
	(void)env;
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
	{
		// cmd = NULL;
		// free_arr(cmd);
		perror(cmd[0]);
		// exit(1);
	}
	// printf("here ;");
	if (execve(path, cmd, env) == -1)
	{
		// cmd = NULL;
		// free_arr(cmd);
		// perror("execve");
		return ;
	}
}

char	*array_to_string(t_line *temp)
{
	size_t total_length = 0;
	char *cmd;
	size_t cmd_size;
	t_line *current = temp;

	// Calculate the total length needed
	while (current && current->str[0][0] != '|' && current->str[0][0] != '>' && current->str[0][0] != '<')
	{
		for (size_t i = 0; current->str[i]; i++)
			total_length += strlen(current->str[i]) + 1;
		current = current->next;
	}

	// Allocate memory for the result string
	cmd_size = total_length + 1; // +1 for the null terminator
	cmd = (char *)malloc(cmd_size);
	if (!cmd)
	{
		perror("malloc");
		return NULL;
	}
	cmd[0] = '\0'; // Initialize the result string

	// Concatenate each element with a space
	current = temp;
	while (current && current->str[0][0] != '|' && current->str[0][0] != '>' && current->str[0][0] != '<')
	{
		for (size_t i = 0; current->str[i]; i++)
		{
			ft_strlcat(cmd, current->str[i], cmd_size);
			if (current->str[i + 1] || (current->next && 
				(current->next->type == 7 || current->next->type == 8)))
				ft_strlcat(cmd, " ", cmd_size);
		}
		current = current->next;
	}
	return cmd;
}

int	count_symbols(t_data *data)
{
	int		i;
	t_line	*temp = data->head;

	i = 0;
	while (temp)
	{
		if (temp->type >= 1 && temp->type <= 5)
			i++;
		temp = temp->next;
	}
	return (i);
}

char	*new_strjoin(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !s2)
	{
		if (s1)
			return (ft_strdup(s1));
		if (s2)
			return (ft_strdup(s2));
		else
			return (NULL);
	}
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	while (*s1)
		*result++ = *s1++;
	*result = ' ';
	result++;
	while (*s2)
		*result++ = *s2++;
	*result = '\0';
	return (result);
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

char	*ft_strcat(char *s1, char *s2)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1 && *s1)
		*dest++ = *s1++;
	while(s2 && *s2)
		*dest++ = *s2++;
	*dest = '\0';
	return (dest);
}

void execute_command(t_cmd *cmd, char **envp)
{
	if (cmd->input_file)
	{
		int fd = open(cmd->input_file, O_RDONLY);
		if (fd < 0)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		// dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->output_file)
	{
		int fd = open(cmd->output_file, O_WRONLY | O_CREAT | (cmd->type==4 ? O_APPEND : O_TRUNC), 0644);
		if (fd < 0)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		// dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	execve(cmd->argv[0], cmd->argv, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

t_cmd	*build_cmd_list(t_line *data)
{
	t_cmd	*cmd = NULL;
	t_cmd	*head = NULL;
	t_cmd	*new_node;
	int		i;

	i = 0;
	while (data)
	{
		new_node = (t_cmd *)malloc(sizeof(t_cmd));
		if (!new_node)
		{
			perror("malloc");
			return (NULL);
		}
		new_node->argv = data->str;
		new_node->type = data->type;
		new_node->next = NULL;
		if (!cmd)
			head = new_node;
		else
			cmd->next = new_node;
		cmd = new_node;
		while (data)
		{
			if (data->type == 7 || data->type == 8)
			{
				data = data->next;
				i++;
			}
			else
			{
				data = data->next;
				break;
			}
		}
	}
	return (head);
}

void	show_cmd(t_cmd *cmd_list)
{
	int	i = 0;
	t_cmd	*temp = cmd_list;
	while (temp)
	{
		printf("Count: %d\n----------------------------\n", i);
		printa("The command", temp->argv);
		printf("The command: %s\nThe output file: %s\nThe input file %d\n", temp->output_file, temp->input_file, temp->type);
		temp = temp->next;
		i++;
	}
}

int execute_cmds(t_cmd *cmd_list, char **envp, t_data *data) {
	int	pid;
	int	pipefd[2];
	int	in_fd;

	(void)envp;
	in_fd = STDIN_FILENO;
	while (cmd_list)
	{
		if (cmd_list->next && cmd_list->next->type == PIPE)
			pipe(pipefd);
		else
			pipefd[1] = STDOUT_FILENO;

		pid = fork();
		if (pid == -1)
			return ft_error(1, data);
		if (pid == 0)
		{
			dup2(in_fd, STDIN_FILENO);
			if (pipefd[1] != STDOUT_FILENO)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			// show_cmd(cmd_list);
			// execute_command(cmd_list, envp);
		}
		else
		{
			waitpid(pid, NULL, 0);
			close(pipefd[1]);
			in_fd = pipefd[0];
		}
		cmd_list = cmd_list->next;
	}
	return 0;
}

void	complex_command(t_data *data)
{
	t_cmd	*cmd_list;
	t_line	*temp = data->head;

	cmd_list = build_cmd_list(temp);
	show_cmd(cmd_list);
	if (cmd_list)
		execute_cmds(cmd_list, data->envp_arr, data);
}

int	handle_input(t_data *data)
{
	t_line	*temp = data->head;
	char	*cmd;

	int i = count_symbols(data);
	cmd = array_to_string(temp);
	if (i == 0)
		single_command(data, cmd);
	else
		complex_command(data);
	return (0);
}

char	**set_list_arra(t_list *env)
{
	char	**result;
	t_list	*temp = env;
	
	int i = ft_lstsize(env);
	result = malloc(sizeof(char *) * (i + 1));
	if (!result)
		return NULL;
	result[i] = NULL; // Null-terminate the array
	i = 0;
	while (temp)
	{
		result[i] = temp->content;
		temp = temp->next;
		i++;
	}
	return (result);
}

int	minishell(t_data *data)
{
	while (1)
	{
		data->head = NULL;
		data->arg = readline(READLINE_MSG);
		data->envp_arr = set_list_arra(data->envp);
		if (data->arg == NULL || data->arg[0] == '\0')
			reset_shell(data);
		add_history(data->arg);
		parse(data->arg, &data->head, data->envp_arr);
		handle_input(data);
		if (data->status == 0)
			break ;
	}
	return (1);
}

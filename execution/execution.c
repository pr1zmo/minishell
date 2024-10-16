/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:35:10 by prizmo            #+#    #+#             */
/*   Updated: 2024/10/15 14:11:23 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printa(char *message, char **arr);

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
	if (ft_strncmp(cmd[0], "pwd", 0) == 0)
		res = ft_pwd(data, cmd);
	else if (ft_strncmp(cmd[0], "env", 0) == 0)
		res = ft_env(data, cmd);
	else if (ft_strncmp(cmd[0], "echo", 0) == 0)
		res = ft_echo(data, cmd);
	else if (ft_strncmp(cmd[0], "cd", 0) == 0)
		res = ft_cd(data, cmd);
	else if (ft_strncmp(cmd[0], "unset", 0) == 0)
		res = ft_unset(data, cmd);
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
	int	i;

	i = 0;
	printf("%s: ", message);
	while (str[i])
	{
		printf("%s ", str[i]);
		i++;
	}
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

	if (!count)
		count = 0;
	printf("Here: %d\n", count);
	count++;
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
		perror(cmd[0]);
	printa("The command:", cmd);
	if (execve(path, cmd, env) == -1)
		return ;
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

void show_cmd(t_cmd *cmd_list)
{
    int 	i = 0;
    t_cmd	*temp = cmd_list;

	while (temp)
	{
		// printf("The command is: %s\n", temp->cmd);
		for (int i = 0; temp->argv[i]; i++)
			printf("The argv is: %s\n", temp->argv[i]);
		printf("The type is: %i\n", temp->type);
		temp = temp->next;
	}
}

char	*ft_strcat(char *s1, char *s2)
{
	char	*dest;
	int		i;

	i = 0;
	if (!s1 || !s2)
	{
		if (s1)
			return (ft_strdup(s1));
		if (s2)
			return (ft_strdup(s2));
		else
			return (NULL);
	}
	dest = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1 && *s1)
		*dest++ = *s1++;
	while(s2 && *s2)
		*dest++ = *s2++;
	*dest = '\0';
	return (dest);
}

char	*to_str(char **arr)
{
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	while (arr[i])
	{
		result = ft_strcat(result, arr[i]);
		if (arr[i + 1])
			result = ft_strcat(result, " ");
		i++;
	}
	return (result);
}

void	execute_command(t_data *data, t_cmd *cmd)
{
	int		pid;
	char	*cmd_str;

	cmd_str = to_str(cmd->argv);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
		exec_cmd(cmd_str, data->envp_arr, data);
	waitpid(0, NULL, 0);
}

int execute_cmds(t_cmd *cmd_list, char **envp, t_data *data)
{
	while (cmd_list)
	{
		if (cmd_list->type == CMD)
			execute_command(data, cmd_list);
		cmd_list = cmd_list->next;
	}
	return 0;
}

void	init_io(t_cmd *cmd)
{
	if (!cmd->io_fds)
	{
		cmd->io_fds = malloc(sizeof * cmd->io_fds);
		if (!cmd->io_fds)
			return ;
		cmd->io_fds->infile = NULL;
		cmd->io_fds->outfile = NULL;
		cmd->io_fds->heredoc_name = NULL;
		cmd->io_fds->in_fd = 0;
		cmd->io_fds->out_fd = 1;
	}
}

static void	pipe_init(t_cmd **cmd)
{
	int		pipe_fds[2];

	if (!cmd || !(*cmd) || !(*cmd)->next)
		return ;
	return ;
	init_io(*cmd);
	if (pipe(pipe_fds) == -1)
		return ;
	if ((*cmd)->next)
	{
		init_io((*cmd)->next);
		if (dup2(pipe_fds[1], (*cmd)->io_fds->out_fd) == -1)
		{
			perror("dup2");
			return ;
		}
		if (dup2(pipe_fds[0], (*cmd)->next->io_fds->in_fd) == -1)
		{
			perror("dup2");
			return ;
		}
		close(pipe_fds[0]);
		close(pipe_fds[1]);
	}
	return ;
}

void	create_files(t_cmd **cmd)
{
	t_cmd	*temp = *cmd;

	while (temp)
	{
		if (temp->next)
			pipe_init(&temp);
		temp = temp->next;
	}
}

void	show_cmds(t_cmd *cmd)
{
	int	i = 0;
	t_cmd *temp = cmd;
	while (temp && i < 10)
	{
		printf("The full command is: %s\n", temp->cmd);
		printf("End of the node\n");
		temp = temp->next;
		i++;
	}
}

void	init_cmd(t_cmd *cmd)
{
	cmd->argv = NULL;
	cmd->pipe_fd = NULL;
	cmd->io_fds = NULL;
	cmd->type = 0;
	cmd->next = NULL;
	cmd->prev = NULL;
}

void	show_head(t_line *head, t_data *data, t_cmd **cmd)
{
	if (!data->status && head)
		get_final_list(&head, cmd);
	while (head)
	{
		printf("this is a node\n");
		printf("------------------\n");
		for (int i = 0;head->str[i];i++)
			printf("str: %s\n", head->str[i]);
		printf("type: %i\n", head->type);
		head = head->next;
	}
	free_line(&head);
}

void ft_putstr_color_fd(char *str, int fd, char *color_code)
{
	ft_putstr_fd(color_code, fd);  // Set color
	ft_putstr_fd(str, fd);         // Print string
	ft_putstr_fd("\033[0m", fd);   // Reset color
	ft_putchar_fd('\n', fd);
}

t_cmd *build_cmd_list(t_line *data)
{
	t_cmd	*cmd = NULL;
	t_cmd	*head = NULL;
	t_cmd	*new_node;
	t_line	*temp = data;
	int		i;

	while (temp)
	{
		new_node = (t_cmd *)malloc(sizeof(t_cmd));
		if (!new_node)
		{
			perror("malloc");
			return NULL;
		}
		init_cmd(new_node);
		if (!temp->str)
			return (free(new_node), NULL);
		new_node->argv = (char **)malloc(sizeof(char *) * 2);
		if (!new_node->argv)
		{
			perror("malloc");
			free(new_node);
			return NULL;
		}
		i = 0;
		new_node->type = temp->type;
		char type_str[10];
		// ft_putstr_color_fd(type_str, 1, "\033[1;32m");
		printf("Str type: ");
		printf("%s\n\033[1;32m", type_str);
		while (temp && temp->type != PIPE)
		{
			new_node->argv = (char **)realloc(new_node->argv, sizeof(char *) * (i + 2));
			if (!new_node->argv)
			{
				perror("realloc");
				free(new_node);
				return NULL;
			}
			new_node->argv[i] = ft_strdup(temp->str[0]);
			if (!new_node->argv[i])
			{
				for (int j = 0; j < i; j++)
					free(new_node->argv[j]);
				free(new_node->argv);
				free(new_node);
				return NULL;
			}
			ft_putstr_color_fd(new_node->argv[i], 1, "\033[1;32m");
			i++;
			temp = temp->next;
		}
		new_node->argv[i] = NULL;
		new_node->cmd = to_str(new_node->argv);
		ft_putstr_color_fd(new_node->cmd, 1, "\033[1;32m");
		if (!head)
		{
			head = new_node;
			char head_str[20];
			ft_putstr_color_fd(head_str, 1, "\033[1;32m");
		}
		else
		{
			t_cmd *current = head;
			while (current->next)
				current = current->next;
			current->next = new_node;
			new_node->prev = current;
			char new_node_str[20];
			ft_putstr_color_fd(new_node_str, 1, "\033[1;32m");
		}
		if (temp && temp->type == PIPE)
			temp = temp->next;
	}
	char head_final_str[20];
	ft_putstr_color_fd(head_final_str, 1, "\033[1;32m");
	return head;
}

void	complex_command(t_data *data)
{
	t_line	*temp = data->head;

	// data->cmd = build_cmd_list(temp);
	get_final_list(&temp, &data->cmd);
	if (data->cmd)
		show_cmd(data->cmd);
	else
		printf("Bro....\n");
	if (data->cmd)
	{
		create_files(&data->cmd);
	}
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
	t_line	*head;
	t_parse	p_data;
	t_cmd	*cmd;

	while (1)
	{
		head = NULL;
		data->arg = readline(READLINE_MSG);
		data->envp_arr = set_list_arra(data->envp);
		if (data->arg == NULL || data->arg[0] == '\0')
			reset_shell(data);
		add_history(data->arg);
		parse(data->arg, &head, data->envp_arr, &p_data);
		data->head = head;
		get_final_list(&head, &cmd);
		// data->cmd = cmd;
		// show_cmd(data->cmd);
		show_cmd(cmd);
		handle_input(data);
		if (data->status == 0)
			break ;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:35:10 by prizmo            #+#    #+#             */
/*   Updated: 2024/10/19 02:44:07 by zelbassa         ###   ########.fr       */
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

bool	check_infile_outfile(t_io_fds *io)
{
	// io = (t_io_fds *)malloc(sizeof(t_io_fds));
	if (!io || (!io->infile && !io->outfile))
		return (true);
	if ((io->infile && io->in_fd == -1)
		|| (io->outfile && io->out_fd == -1))
		return (false);
	return (true);
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
		{
			return (full_cmd);
		}
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
		printf("The command is: %s\n", temp->cmd);
		printf("The type is: %i\n", temp->type);
		temp = temp->next;
	}
}

char *ft_strcat(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL); // Both are NULL
	if (!s1)
		return (strdup(s2)); // s1 is NULL, return a copy of s2
	if (!s2)
		return (strdup(s1)); // s2 is NULL, return a copy of s1
	len1 = strlen(s1);
	len2 = strlen(s2);
	char *dest = malloc(len1 + len2 + 1);
	if (!dest)
		return (NULL); // Check for allocation failure
	memcpy(dest, s1, len1);
	memcpy(dest + len1, s2, len2);
	dest[len1 + len2] = '\0';
	return (dest); // Return the pointer to the new string
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

static void	init_io(t_io_fds *io_fds)
{
	io_fds->in_fd = STDIN_FILENO;
	io_fds->out_fd = STDOUT_FILENO;
	io_fds->infile = NULL;
	io_fds->outfile = NULL;
	io_fds->heredoc_name = NULL;
}

bool	redirect_io(t_io_fds *io)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	// io = (t_io_fds *)malloc(sizeof(t_io_fds));
	// init_io(io);
	if (io->in_fd != -1)
	{
		if (dup2(io->in_fd, STDIN_FILENO) == -1)
			ft_putstr_fd("dup2 error\n", 2);
	}
	if (io->out_fd != -1)
	{
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
	// if (!cmd || !cmd->cmd)
	// 	ft_putstr_fd("Command not found\n", 2);
	if (!check_infile_outfile(cmd->io_fds))
		exit(1);
	set_pipe_fds(data->cmd, cmd);
	redirect_io(cmd->io_fds);
	close_fds(data->cmd, false);
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

void	show_command_info(t_cmd *cmd)
{
	ft_putstr_fd("Command: ", 2);
	ft_putstr_fd(cmd->cmd, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("The fd in is: ", 2);
	ft_putnbr_fd(cmd->io_fds->in_fd, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("The fd out is: ", 2);
	ft_putnbr_fd(cmd->io_fds->out_fd, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("Type: ", 2);
	ft_putnbr_fd(cmd->type, 2);
	ft_putchar_fd('\n', 2);
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
		return (EXIT_FAILURE);
	return (127);
}

static int	handle_execute(t_data *data)
{
	t_cmd	*cmd;
	int		pid;

	cmd = data->cmd;
	while (pid != 0 && cmd)
	{
		pid = fork();
		if (pid == -1)
			ft_putstr_fd("fork error\n", 2);
		else if (pid == 0)
			execute_command(data, cmd);
		cmd = cmd->next;
	}
	return (1);
}

int execute_cmds(t_cmd *cmd_list, char **envp, t_data *data)
{
	t_cmd	*temp = cmd_list;
	int		ret;

	ret = set_values(data);
	// if (ret == 127)
	// 	return (ft_putstr_fd("Command not found\n", 2), 0);
	// if (temp->io_fds)
	// {
	// 	ft_putstr_fd("The ios are set\n", 2);
	// 	ft_putstr_fd("The read file of the next command: ", 2);
	// 	if (temp->io_fds->in_fd != -1)
	// 		ft_putnbr_fd(temp->io_fds->in_fd, 2);
	// 	else
	// 		ft_putstr_fd("No read file\n", 2);
	// 	ft_putchar_fd('\n', 2);
	// }
	if (check_infile_outfile(temp->io_fds))
	{
		redirect_io(data->cmd->io_fds);
		ret = exec_builtin(data, &temp->cmd);
	}
	if (ret == 127)
		return (ret);
	return (handle_execute(data));
}

static void	show_io_fds(t_io_fds *io_fds)
{
	ft_putstr_fd("in_fd: ", 2);
	ft_putnbr_fd(io_fds->in_fd, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("out_fd: ", 2);
	ft_putnbr_fd(io_fds->out_fd, 2);
	ft_putchar_fd('\n', 2);
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
	else if (infile == false && io->outfile)
	{
		if (io->out_fd == -1 || (io->infile && io->in_fd == -1))
			return (false);
		free(io->outfile);
		close(io->out_fd);
	}
	return (true);
}

static void	open_outfile_trunc(t_io_fds *io, char *file)
{
	if (!remove_old_file_ref(io, false))
		return ;
	io->outfile = ft_strdup(file);
	if (io->outfile == '\0')
	{
		ft_putstr_fd("Ambigious redirect\n", 2);
		return ;
	}
	io->out_fd = open(io->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (io->out_fd == -1)
		ft_putstr_fd("outfile error\n", 2);
}

static void	handle_write_to(t_cmd **cmd, t_data *data)
{
	(*cmd)->io_fds = (t_io_fds *)malloc(sizeof(t_cmd));
	init_io((*cmd)->io_fds);
	// printf("The command to run: %s\n", (*cmd)->cmd);
	open_outfile_trunc((*cmd)->io_fds, (*cmd)->argv[1]);
	(*cmd) = (*cmd)->next;
}

void	handle_pipe(t_cmd **cmd, t_data *data)
{
	(*cmd)->pipe_output = 1;
	(*cmd) = (*cmd)->next;
}

void create_files(t_cmd **cmd, t_data *data)
{
	t_cmd	*temp = *cmd;

	while (temp)
	{
		if (temp->type == REDIR_OUT)
		{
			handle_write_to(&temp, data);
		}
		else if (temp->type == CMD && temp->next->type == CMD)
		{
			handle_pipe(&temp, data);
		}
		else
			temp = temp->next;
	}
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

void ft_putstr_color_fd(char *str, int fd, char *color_code)
{
	ft_putstr_fd(color_code, fd);  // Set color
	ft_putstr_fd(str, fd);         // Print string
	ft_putstr_fd("\033[0m", fd);   // Reset color
	ft_putchar_fd('\n', fd);
}

void	complex_command(t_data *data)
{
	t_line	*temp = data->head;

	if (data->cmd)
	{
		create_files(&data->cmd, data);
		if (data->cmd->io_fds)
		{
			ft_putstr_fd("The read file of the next command: ", 2);
			ft_putnbr_fd(data->cmd->next->io_fds->in_fd, 2);
			ft_putchar_fd('\n', 2);
			// show_io_fds(data->cmd->io_fds);
		}
		execute_cmds(data->cmd, data->envp_arr, data);
	}
}

void set_cmd_strings(t_cmd *cmd)
{
    t_cmd	*current = cmd;
	int		i;
	size_t	total_length;

    while (current != NULL)
	{
        total_length = 0;
		i = 0;
		while (current->argv[i] != NULL)
		{
			total_length += ft_strlen(current->argv[i]) + 1;
			i++;
		}
        current->cmd = malloc(total_length * sizeof(char));
        if (current->cmd == NULL)
		{
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
        current->cmd[0] = '\0';
		i = 0;
        while (current->argv[i] != NULL)
		{
            strcat(current->cmd, current->argv[i]);
            if (current->argv[i + 1] != NULL)
                strcat(current->cmd, " ");
			i++;
        }
        current = current->next;
    }
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

char	**set_list_arra(t_list *env)
{
	char	**result;
	t_list	*temp = env;

	int i = ft_lstsize(env);
	result = malloc(sizeof(char *) * (i + 1));
	if (!result)
		return NULL;
	result[i] = NULL;
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

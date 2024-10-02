/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:50:28 by prizmo            #+#    #+#             */
/*   Updated: 2024/10/02 11:43:15 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>      // printf, perror
# include <stdlib.h>     // malloc, free, exit
# include <unistd.h>     // read, write, access, open, close, fork, execve, getcwd, chdir, unlink, dup, dup2, pipe, isatty, ttyname, ttyslot
# include <fcntl.h>      // open, O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, O_TRUNC
# include <string.h>     // strerror
# include <sys/types.h>  // fork, wait, waitpid, wait3, wait4, stat, lstat, fstat, kill, opendir, readdir, closedir
# include <sys/stat.h>   // stat, lstat, fstat, open
# include <sys/wait.h>   // wait, waitpid, wait3, wait4
# include <signal.h>     // signal, sigaction, sigemptyset, sigaddset, kill
# include <dirent.h>     // opendir, readdir, closedir
# include <termios.h>    // tcsetattr, tcgetattr, ioctl
# include <curses.h>     // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <term.h>       // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <errno.h>      // errno
# include <sys/ioctl.h>  // ioctl
# include <readline/readline.h>    // readline, add_history
# include <readline/history.h>     // rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
# include "parsing.h"
# include "builtins.h"
# include "styles.h"

# define MAX_PATH 4096

typedef struct s_token t_line;

typedef struct s_builtin
{
	char		*command;
	int			has_args;
	char		*argument;
}				t_builtin;

typedef struct s_cmd {
	char			**argv;
	char			*input_file;  
	char			*output_file;
	int				type;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_data
{
	t_line		*head;
	char		*arg;
	int			status;
	t_list		*envp;
	char		**envp_arr;
	char		*curr_dir;
	char		*old_dir;
	int			pipe_count;
}				t_data;

int		minishell(t_data *data);
void	free_arr(char **arr);
int		ft_pwd(t_data *data, char **cmd);
int		ft_env(t_data *data, char **cmd);
int		ft_echo(t_data *data, char **cmd);
int		ft_cd(t_data *data, char **cmd);
int		ft_exit(t_data *data, char **cmd);
int		ft_export(t_data *data, char **cmd);
int		ft_unset(t_data *data, char **cmd);
int		modify_env_value(char *name, char *new_value, t_data *data);
void	set_env_var(t_data *data, char *value, char *old_value);
char	*ft_getenv(char *name, t_data *data);
void	create_env_value(t_data *data, char *key);
void	set_list_var(t_data *data, char *name, char *new_value);
char	*find_value(char *name, t_list *envp);
char	*new_substr(const char *str, int c);

#endif

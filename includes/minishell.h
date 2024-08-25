/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:50:28 by prizmo            #+#    #+#             */
/*   Updated: 2024/08/25 14:14:52 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
#include <stdio.h>      // printf, perror
#include <stdlib.h>     // malloc, free, exit
#include <unistd.h>     // read, write, access, open, close, fork, execve, getcwd, chdir, unlink, dup, dup2, pipe, isatty, ttyname, ttyslot
#include <fcntl.h>      // open, O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, O_TRUNC
#include <string.h>     // strerror
#include <sys/types.h>  // fork, wait, waitpid, wait3, wait4, stat, lstat, fstat, kill, opendir, readdir, closedir
#include <sys/stat.h>   // stat, lstat, fstat, open
#include <sys/wait.h>   // wait, waitpid, wait3, wait4
#include <signal.h>     // signal, sigaction, sigemptyset, sigaddset, kill
#include <dirent.h>     // opendir, readdir, closedir
#include <termios.h>    // tcsetattr, tcgetattr, ioctl
#include <curses.h>     // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
#include <term.h>       // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
#include <errno.h>      // errno
#include <sys/ioctl.h>  // ioctl
#include <readline/readline.h>    // readline, add_history
#include <readline/history.h>     // rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
# include "parsing.h"
# include "builtins.h"

# define RESET	"\x1b[0m"
# define BOLD	"\x1b[1m"
# define RED	"\x1b[31m"
# define GREEN	"\x1b[32m"
# define YELLOW	"\x1b[93m"
# define CYAN	"\x1b[36m"

typedef struct s_token t_line;

typedef	struct s_command
{
	char				*symbol;
	char				*command;
	struct s_command	*left;
	struct s_command	*rigth;
}						t_command;

typedef struct s_tree
{
    struct s_tree	*left;
    struct s_tree	*right;
    char			*data;
}					t_tree;

typedef struct s_data
{
	t_command	*command;
	t_list		*env;
	t_tree		*tree;
	t_line		*head;
	int			status;
}				t_data;

int	minishell(t_data *data);

#endif

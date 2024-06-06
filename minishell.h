/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:50:28 by prizmo            #+#    #+#             */
/*   Updated: 2024/06/06 15:45:00 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_list
{
	struct s_list	*next;
	char			*data;
}					t_list;

int		ft_env(t_list *lst);
int		handle_command(char *str, t_list *env);
t_list	*get_env(char **env);

#endif
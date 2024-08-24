/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prizmo <prizmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:18:15 by prizmo            #+#    #+#             */
/*   Updated: 2024/08/24 20:23:18 by prizmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <dirent.h>
# include "minishell.h"

typedef struct s_builtins
{
	
}	t_builtins;

void	update_path(t_data *data);
int		ft_echo(t_data *data, t_builtins *simple_cmd);
int		ft_cd(t_data *data, t_builtins *simple_cmd);
int		ft_pwd(t_data *data, t_builtins *simple_cmd);
int		ft_export(t_data *data, t_builtins *simple_cmd);
int		ft_unset(t_data *data, t_builtins *simple_cmd);
int		ft_env(t_data *data, t_builtins *simple_cmd);
int		ft_exit(t_data *data, t_builtins *simple_cmd);
// int		ft_continue(t_data *data, t_builtins *simple_cmd);
// size_t	equal_sign(char *str);
// int		check_valid_identifier(char c);

#endif
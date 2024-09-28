/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:43:22 by zelbassa          #+#    #+#             */
/*   Updated: 2024/09/28 09:58:20 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_path(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
		return (0);
	return (1);
}

int	ft_cd(t_data *data, char **arg)
{
	char	*old_pwd;
	if (!arg[1])
		return (printf("cd: too few arguments\n"));
	if (!is_valid_path(arg[1]))
		return (printf("cd: no such file or directory: %s\n", arg[1]));
	old_pwd = getenv("PWD");
	modify_env_value("PWD", arg[1], data);
	modify_env_value("OLDPWD", old_pwd, data);
	return (0);
}

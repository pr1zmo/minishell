/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:43:22 by zelbassa          #+#    #+#             */
/*   Updated: 2024/09/28 14:52:35 by zelbassa         ###   ########.fr       */
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
	char	*buff;
	char	*new_pwd;

	buff = NULL;
	if (!arg[1])
		return (printf("cd: too few arguments\n"));
	if (!is_valid_path(arg[1]))
		return (printf("cd: no such file or directory: %s\n", arg[1]));
	old_pwd = getenv("PWD");
	chdir(arg[1]);
	new_pwd = getcwd(buff, 1096); 
	printf("The old pwd: %s\nThe new pwd: %s\n", old_pwd, new_pwd);
	modify_env_value("PWD", new_pwd, data);
	modify_env_value("OLDPWD", old_pwd, data);
	return (0);
}

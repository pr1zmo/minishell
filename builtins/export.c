/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:47:56 by prizmo            #+#    #+#             */
/*   Updated: 2024/09/30 20:50:05 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char	*find_value(char *name, char **envp)
{
	int		i;
	char	*key;

	i = 0;
	key = ft_strchr(name, '=');
	while (envp[i])
	{
		if (ft_strncmp(key, envp[i], ft_strlen(key)) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

void	add_env_value(t_data *data, char *key, char *value)
{
	// need some understanding
	int		i;
	char	**new_env;
	char	*temp;
	char	*old_value;

	// if (!value)
}

int ft_export(t_data *data, char **cmd)
{
	char	*value;

	if (!cmd[1])
		ft_env(data, cmd);
	value = find_value(cmd[1], data->envp);
	add_env_value(data, cmd[1], value);
	// add_env_value(data, cmd[1]);
	// value = find_value(cmd[1], data->envp);
	return (0);
}
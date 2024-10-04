/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:46:48 by prizmo            #+#    #+#             */
/*   Updated: 2024/10/04 13:16:29 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void delete_env_var(char *name, t_list **envp)
{
	t_list	*temp = *envp;
	t_list	*prev;
	size_t	name_len;

	prev = NULL;
	name_len = strlen(name);
	while (temp != NULL)
	{
		if (strncmp(name, temp->content, name_len) == 0
			&& ((char*)temp->content)[name_len] == '=')
		{
			if (prev == NULL)
				*envp = temp->next;
			else
				prev->next = temp->next;
			free(temp->content);
			free(temp);
			return;
		}
		prev = temp;
		temp = temp->next;
	}
}

int ft_unset(t_data *data, char **cmd)
{
	if (!cmd[1])
		return (0);
	delete_env_var(cmd[1], &(data->envp));
	return (0);
}
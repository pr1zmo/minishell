#include "../includes/parsing.h"

void	ft_free(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

void	free_line(t_line **head)
{
	t_line	*tmp;
	int		i;

	i = 0;
	tmp = (*head);
	while (*head)
	{
		i = 0;
		while ((*head)->str[i])
			free((*head)->str[i++]);
		free((*head)->str);
		tmp = (*head)->next;
		free(*head);
		*head = tmp;
	}
}

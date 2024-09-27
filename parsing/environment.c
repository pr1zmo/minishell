#include "parsing.h"

void	get_env(t_line **head, char **env)
{
	int		i;
	char	**tmp;
	t_line	*line;

	i = 0;
	line = *head;
	while (env[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		tmp[i] = ft_strdup(env[i]);
		i++;
	}
	tmp[i] = NULL;
	while (line)
	{
		line->env = tmp;
		line = line->next;
	}
}

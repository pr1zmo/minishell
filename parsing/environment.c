#include "parsing.h"

void	init(t_parse *data, char **env)
{
	int		i;

	i = 0;
	data->SHLVL = 1;
	while (env[i])
		i++;
	data->env = malloc(sizeof(char *) * (i + 1));
	if (!data->env)
		return ;
	i = 0;
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		i++;
	}
	data->env[i] = NULL;
}

#include "parsing.h"

int	find(char *str, int k,char **env)
{
	int	i;
	int	j;

	i = 0;
	j = k + 1;
	while (str[j] && !is_space(str[j]) && str[j] != '\"' && str[j] != '\'')
		j++;
	while (env[i])
	{
		if (!ft_strncmp(env, str, j))
			return (i);
		i++;
	}
	return (0);
}

char	*replace(str, i,env, j)
{
	char	*tmp;
	int		len;

	len = 0;
	while (str[len])
}

char 	*find_and_replace(char *str, int i,char **env)
{
	char	*tmp;
	int		condition;

	condition = find(str, i , env);
	if (condition)
		tmp = replace(str, i, env, condition);
	else if (!condition)
		tmp = delete(str, i)
	return (tmp);
}

void	expand(char **str, char **env)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == -1 && (str[i + 1] == ' ' || \
			get_token(str[i + 1]) || str[i + 1] == '$'))
				str[i][j] == '$';
			else if (str[i][j] == -1 && find())
			j++;
		}
		i++;
	}
}

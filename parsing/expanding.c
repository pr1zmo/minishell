#include "parsing.h"

static int	check_case(char *str, int i)
{
	if (!str[i] || isspace(str[i]) || str[i] == '=' \
	|| str[i] == '\'' || str[i] == '\"')
		return (1);
	if (check_token(str[i]))
		return (1);
	return (0);
}

int	find(char *tmp, int i, t_env *env, int *size)
{
	int	j;

	j = 0;
	*size = 0;
	i++;
	while (!check_case(tmp, i + *size))
		*size += 1;
	tmp += i;
	while (env)
	{
		if (!ft_strncmp(tmp, env->content, *size) && env->content[*size] == '=')
			return (j);
		env = env->next;
		j++;
	}
	return (-1);
}

char	*replace(char *tmp, int k, t_env *env, int size)
{
	char	*new;
	int		i;
	int		j;
	int		env_len;

	i = 0;
	env_len = 0;
	while (k--)
		env = env->next;
	while (env->content[env_len] && env->content[env_len] != '=')
		env_len++;
	env_len++;
	new = malloc(ft_strlen(tmp) + ft_strlen(env->content + env_len) - size + 1);
	if (!new)
		return (NULL);
	while (tmp[i] && tmp[i] != -1)
	{
		new[i] = tmp[i];
		i++;
	}
	j = i + size + 1;
	while (env->content[env_len])
		new[i++] = env->content[env_len++];
	while (tmp[j])
		new[i++] = tmp[j++];
	new[i] = '\0';
	free(tmp);
	return (new);
}

char	*delete(char *tmp, int size)
{
	char	*new;
	int		j;
	int		i;

	new = malloc(ft_strlen(tmp) - size + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (tmp[i] && tmp[i] != -1)
	{
		new[i] = tmp[i];
		i++;
	}
	j = i;
	i = i + size + 1;
	while (tmp[i])
		new[j++] = tmp[i++];
	new[j] = '\0';
	free(tmp);
	return (new);
}

char	*find_and_replace(char *str, t_env *env)
{
	int		i;
	int		size;
	int		ca;
	char	*tmp;

	tmp = ft_strdup(str);
	i = 0;
	while (str[i])
	{
		if (str[i] == -1)
		{
			ca = find(str, i, env, &size);
			if (ca >= 0)
				tmp = replace(tmp, ca, env, size);
			else
				tmp = delete(tmp, size);
		}
		i++;
	}
	free(str);
	return (tmp);
}

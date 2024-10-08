#include "parsing.h"

static void	env_lstadd_back(t_env **head, t_env *new)
{
	t_env	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	set_env(t_env **head, char **envp)
{
	t_env	*new;
	int		i;

	i = 0;
	while (envp[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return ;
		new->content = ft_strdup(envp[i]);
		new->next = NULL;
		env_lstadd_back(head, new);
		i++;
	}
}

t_env	*get_pwd(void)
{
	t_env	*env;
	char	*tmp;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	tmp = malloc(sizeof(char) * PATH_MAX + 1);
	if (!tmp)
		return (free(env), NULL);
	if (!getcwd(tmp, PATH_MAX))
		return (free(env), free(tmp), NULL);
	env->content = ft_strjoin("PWD=", tmp);
	env->next = NULL;
	free(tmp);
	return (env);
}

t_env	*get_shlvl(void)
{
	t_env	*tmp;

	tmp = malloc(sizeof(t_env));
	if (!tmp)
		return (NULL);
	tmp->content = malloc(8);
	if (!tmp->content)
		return (free(tmp), NULL);
	tmp->content[0] = '\0';
	ft_strlcat(tmp->content, "SHLVL=1", 8);
	return (tmp);
}

void	create_env(t_env **head)
{
	env_lstadd_back(head, get_pwd());
	env_lstadd_back(head, get_shlvl());
}

void	init(t_env **data, char **env)
{
	int		i;

	i = 0;
	if (!env[0])
		create_env(data);
	else
		set_env(data, env);
	if (!data)
		return ;
}

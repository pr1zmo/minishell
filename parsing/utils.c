#include "parsing.h"

int	check_token(int c)
{
	if (c == '|')
		return (0);
	if (c == '<')
		return (0);
	if (c == '>')
		return (0);
}

int	quotes_open(char *s, int i)
{
	int	quotes[2];
	int	j;

	ft_bzero(quotes, 2 * 4);
	j = 0;
	while (s[j] && j < i)
	{
		if (s[i] == '\'' && !(quotes[1] % 2))
			quotes[0]++;
		else if (s[i] == '\"' && !(quotes[0] % 2))
			quotes[1]++;
		j++;
	}
	if (quotes[0] % 2)
		return (1);
	else if (quotes[1] % 2 || quotes[2] % 2)
		return (2);
	else
		return (0);
}

int	checkquotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && quotes_open(line, i) != 1)
			line[i] == -1;
		i++;
	}
	if (quotes_open(line, i) == 1)
		return (ft_putstr_fd("minishell: syntax error near unexpected token '\''\n", 2),0);
	if (quotes_open(line, i) == 2)
		return (ft_putstr_fd("minishell: syntax error near unexpected token '\"'\n", 2),0);
	return (1);
}

int	checkspaces(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
		i++;
	if (!line[i])
		return (0);
	return (1);
}

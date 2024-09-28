#include "parsing.h"

int	check_token(int c)
{
	if (c == '|')
		return (1);
	if (c == '<' || c == '>')
		return (2);
	return (0);
}

int	checkspaces(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (is_space(line[i]))
		i++;
	if (!line[i])
		return (0);
	return (1);
}

int	checkquotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && quotes_open(line, i) != 1)
			line[i] = -1;
		i++;
	}
	printf("%s\n", line)
	if (quotes_open(line, i) == 1)
		return (ft_putstr_fd("minishell: syntax error near unexpected token '\''\n", 2),0);
	if (quotes_open(line, i) == 2)
		return (ft_putstr_fd("minishell: syntax error near unexpected token '\"'\n", 2),0);
	return (1);
}

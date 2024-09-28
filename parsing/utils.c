#include "parsing.h"

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

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
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
		if (s[j] == '\'' && !(quotes[1] % 2))
			quotes[0]++;
		else if (s[j] == '\"' && !(quotes[0] % 2))
			quotes[1]++;
		j++;
	}
	if (quotes[0] % 2)
		return (1);
	else if (quotes[1] % 2 || quotes[0] % 2)
		return (2);
	else
		return (0);
}

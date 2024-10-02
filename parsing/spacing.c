#include "parsing.h"

int	left_space(char *line, int i)
{
	if (line[i] == '<' && line[i - 1] == '<')
		return (0);
	if (line[i] == '>' && line[i - 1] == '>')
		return (0);
	if (check_token(line[i]) && !quotes_open(line, i) && !is_space(line[i - 1]))
		return (1);
	return (0);
}

int	right_space(char *line, int i)
{
	if (line[i + 1] == 0)
		return (0);
	if (line[i] == '>' && line[i + 1] == '>')
		return (0);
	if (line[i] == '<' && line[i + 1] == '<')
		return (0);
	if (check_token(line[i]) && !quotes_open(line, i) && !is_space(line[i + 1]))
		return (1);
	return (0);
}

int	count_spaced_string(char *line)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (line[i])
	{
		if (i && left_space(line, i) && check_token(line[i - 1] != 2))
			size++;
		size++;
		if (right_space(line, i) && check_token(line[i + 1] != 2))
			size++;
		i++;
	}
	return (size);
}

char	*spacing(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(count_spaced_string(line) + 1);
	if (!str)
		return (NULL);
	while (line[i])
	{
		if (i && left_space(line, i))
			str[j++] = ' ';
		str[j++] = line[i];
		if (right_space(line, i))
			str[j++] = ' ';
		i++;
	}
	str[j] = '\0';
	free(line);
	return (str);
}

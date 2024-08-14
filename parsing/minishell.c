#include "minishell.h"

int	special_char(char *str, int i)
{
	if (str[i] == '&' || str[i] == ';')
		return (1);
	if (str[i] == '|' && str[i + 1] == '|')
		return (1);
	return (0);
}

int	checkquotes(char *line)
{
	int	i;
	int	quotes[2];

	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !(quotes[1] % 2))
			quotes[0]++;
		else if (line[i] == '\"' && !(quotes[0] % 2))
			quotes[1]++;
		else if (special_char(line, i) && !(quotes[0] % 2) && !(quotes[1] % 2))
		{
			write (2, "Parsing error near '", 20);
			write (2, &line[i], 1);
			write (2, "'\n", 2);
			return (0);
		}
		i++;
	}
	if ((quotes[0] % 2) || (quotes [1] % 2))
		return (ft_putstr_fd("Parsing error: missing closing quotation\n", 2),0);
	return (1);
}

int	checkspaces(char *line)
{
	int	i;

	i = 0;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
		i++;
	if (!line[i])
		return (0);
	return (1);
}

t_line	*parse(char *line)
{
	char	**arg;
	t_line	*head;

	if (!checkspaces(line))
		return (NULL);
	if (!checkquotes(line))
		return (NULL);
	head = NULL;
	arg = ft_split(line, ' ');
	if (!arg)
		return (NULL);
	lexer(arg, head);
	return (head);
}

int main(int ac, char **av)
{
	char	*line;
	t_line	*head;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		head = parse(line);
		printf("%p\n", head);
		free(line);
	}
}

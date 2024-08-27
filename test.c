#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int ac, char **av, char **env)
{
	char	*str[10] = {"echo", av[1]};
	execve("/bin/echo", str, env);
	return (0);
}

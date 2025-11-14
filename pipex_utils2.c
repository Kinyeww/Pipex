#include "pipex.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	check_file(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 1)
		return (0);
	return (1);
}

char	**assign_arg(char *av)
{
	char	**cmd;

	cmd = ft_split(av, ' ');
	if (!cmd)
		return (NULL);
	return (cmd);
}

char	*find_abs_path(char *paths, char *cmd1)
{
	char	*abs_path;
	char	**splitted_path;
	int		i;

	i = 0;
	splitted_path = ft_split(paths, ':');
	while (splitted_path[i])
	{
		splitted_path[i] = my_strjoin(splitted_path[i], cmd1);
		if (access(splitted_path[i], X_OK) == 0)
		{
			abs_path = splitted_path[i];
			return (abs_path);
		}
		free(splitted_path[i]);
		i++;
	}
	return (NULL);
}

void	close_program(char **cmd1, char **cmd2)
{
	int	i;

	i = 0;
	while (cmd1[i])
	{
		free(cmd1[i]);
		i++;
	}
	free (cmd1);
	i = 0;
	while (cmd2[i])
	{
		free(cmd2[i]);
		i++;
	}
	free(cmd2);
}

void	call_first_child(char **cmd, int pipefd[2], char **envp, char **av)
{
	first_child(cmd, pipefd, envp, av);
	exit(0);
}
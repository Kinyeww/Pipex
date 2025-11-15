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
	char	**splitted_path;
	char	*abs_path;
	int		i;

	if (!paths || !cmd1)
		return (NULL);	
	i = 0;
	splitted_path = ft_split(paths, ':');
	while (splitted_path[i])
	{
		abs_path = my_strjoin(splitted_path[i], cmd1);
		if (access(abs_path, X_OK) == 0)
		{
			free_arr(splitted_path);
			return (abs_path);
		}
		free(abs_path);
		i++;
	}
	free_arr(splitted_path);
	return (NULL);
}

void	close_program(t_pipex *pipex)
{
	int	i;

	if (pipex->cmd1)
	{
		i = 0;
		while (pipex->cmd1[i])
			free(pipex->cmd1[i++]);
		free (pipex->cmd1);
	}
	if (pipex->cmd2)
	{
		i = 0;
		while (pipex->cmd2[i])
			free(pipex->cmd2[i++]);
		free(pipex->cmd2);
	}
}

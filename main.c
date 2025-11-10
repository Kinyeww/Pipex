#include "pipex.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s1cpy;

	i = 0;
	while (s1[i] != '\0')
		i++;
	s1cpy = malloc(sizeof(char) * (i + 1));
	if (!s1cpy)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s1cpy[i] = s1[i];
		i++;
	}
	s1cpy[i] = '\0';
	return (s1cpy);
}

int	check_file(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 1)
		return (0);
	return (1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*find_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_strdup(envp[i] + 5));
		i++;
	}
	printf("path finding failed, returning null\n");
	return (NULL);
}

char	*my_strjoin(char *str1, char *str2)
{
	char	*tmp;
	int	i;
	int	k;

	if (!str1 || !str2)
		return (NULL);
	i = 0;
	k = 0;
	while (str1[i])
		i++;
	while (str2[k])
		k++;
	tmp = malloc(sizeof(char) * ((i + k) + 2));
	i = 0;
	while (str1[i])
	{
		tmp[i] = str1[i];
		i++;
	}
	tmp[i] = '/';
	i++;
	k = 0;
	while (str2[k])
	{
		tmp[i + k] = str2[k];
		k++;
	}
	tmp[i + k] = '\0';
	return (tmp);
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

void	first_child(char **cmd1, int pipefd[2], char **envp, char **av)
{
	char	*abs_path;
	char	*paths;
	int		infile;

	printf("at first child\n");
	infile = open(av[1], O_RDONLY);
	if (infile < 0)
		return ;
	printf("infile = %d\n", infile);
	paths = find_path(envp);
	abs_path = find_abs_path(paths, cmd1[0]);
	printf("abs_path =%s\n", abs_path);
	if (!paths || !abs_path)
		printf("failed creating path\n");
	dup2(infile, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	close(infile);
	execve(abs_path, cmd1, envp);
	perror("execve1 failed\n");
}

void	second_child(char **cmd2, int pipefd[2], char **envp, char **av)
{
	int		outfile;
	char	*path;
	char	*abs_path;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		return ;
	printf("outfile = %d\n", outfile);
	path = find_path(envp);
	abs_path = find_abs_path(path, cmd2[0]);
	printf("cmd2 =%s\n", abs_path);
	dup2(outfile, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	close(outfile);
	execve(abs_path, cmd2, envp);
	perror("execve2 failed\n");
}

void	exepipe(char **cmd1, char **cmd2, char **envp, char **av)
{
	int		pipefd[2];
	int		pid1;
	int		pid2;

	if (pipe(pipefd) == -1)
	{
		printf("pipe failed");
		return ;
	}
	pid1 = fork();
	if (pid1 == 0)
		first_child(cmd1, pipefd, envp, av);
	pid2 = fork();
	if (pid2 == 0)
		second_child(cmd2, pipefd, envp, av);
}

int	check_arg(int ac, char **av, char **envp)
{
	char	**cmd1;
	char	**cmd2;

	if (ac == 5)
	{
		cmd1 = ft_split(av[2], ' ');
		cmd2 = ft_split(av[3], ' ');
		if (!cmd1 || !cmd2)
		{
			printf("invalid command, cmd1 = %s, cmd2 = %s\n", cmd1[0], cmd2[0]);
			return (0);
		}
		exepipe(cmd1, cmd2, envp, av);
		return (1);
	}
	else
		printf("error argument\n usage: <input files> \"cmd1\" \"cmd2\" <output files>\n");
}

int	main(int ac, char **av, char **envp)
{
	if (!(check_arg(ac, av, envp)))
	{
		printf("parsing failed\n");
		return (1);
	}
	return (0);
}

#include "pipex.h"
#include "ft_printf/ft_printf.h" 
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
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
	return (NULL);
}

char	*my_strjoin(char *str1, char *str2)
{
	char	*tmp;
	int		i;
	int		k;

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

	infile = open(av[1], O_RDONLY);
	if (infile < 0)
	{
		perror(av[1]);
		exit(1);
	}
	paths = find_path(envp);
	abs_path = find_abs_path(paths, cmd1[0]);
	if (!abs_path)
	{
		perror("invalid command 1");
		return ;
	}
	dup2(infile, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	close(infile);
	execve(abs_path, cmd1, envp);
	perror("execve1 failed");
}

void	second_child(char **cmd2, int pipefd[2], char **envp, char **av)
{
	int		outfile;
	char	*path;
	char	*abs_path;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
	{
		perror("file error");
		return ;
	}
	path = find_path(envp);
	abs_path = find_abs_path(path, cmd2[0]);
	if (!abs_path)
	{
		perror("invalid command 2");
		return ;
	}
	dup2(outfile, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	close(outfile);
	execve(abs_path, cmd2, envp);
	perror("execve2 failed");
}

void	close_program(char **cmd1, char **cmd2)
{
	int	i;

	i = 0;
	while (cmd1[i])
	{
		free (cmd1[i]);
		i++;
	}
	free (cmd1);
	i = 0;
	while (cmd2[i])
	{
		free (cmd2[i]);
		i++;
	}
	free(cmd2);
}

void	exepipe(char **cmd1, char **cmd2, char **envp, char **av)
{
	int		pipefd[2];
	int		pid1;
	int		pid2;

	if (pipe(pipefd) == -1)
	{
		perror("pipe failed");
		exit(1);
	}
	pid1 = fork();
	if (pid1 == 0)
	{
		first_child(cmd1, pipefd, envp, av);
		exit (0);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		second_child(cmd2, pipefd, envp, av);
		exit (0);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	close_program(cmd1, cmd2);
}

char	**check_arg(char *av)
{
	char	**cmd;

	cmd = ft_split(av, ' ');
	if (!cmd)
		return (NULL);
	return (cmd);
}

int	main(int ac, char **av, char **envp)
{
	char	**cmd1;
	char	**cmd2;

	if (ac != 5)
	{
		ft_printf("Error\nUsage: ./pipex infile cmd1 cmd2 outfile\n");
	}
	if (!av[2][0] || !av[3][0])
	{
		ft_printf("Error: Empty command\n");
		return (1);
	}
	cmd1 = check_arg(av[2]);
	cmd2 = check_arg(av[3]);
	exepipe(cmd1, cmd2, envp, av);
	return (0);
}

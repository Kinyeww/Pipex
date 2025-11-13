#include "pipex.h"
#include "ft_printf/ft_printf.h" 
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

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
	cmd1 = assign_arg(av[2]);
	cmd2 = assign_arg(av[3]);
	exepipe(cmd1, cmd2, envp, av);
	return (0);
}

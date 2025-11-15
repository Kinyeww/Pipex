/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckin-yew <ckin-yew@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:23:24 by ckin-yew          #+#    #+#             */
/*   Updated: 2025/11/15 15:56:07 by ckin-yew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf/ft_printf.h" 
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

void	first_child(t_pipex *pipex, int pipefd[2], char **envp)
{
	char	*abs_path;
	char	*paths;

	paths = find_path(envp);
	abs_path = find_abs_path(paths, pipex->cmd1[0]);
	if (!abs_path)
	{
		close_program(pipex);
		free(paths);
		free(abs_path);
		perror("invalid command 1");
		exit(127);
	}
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	execve(abs_path, pipex->cmd1, envp);
	perror("execve1 failed");
	exit(1);
}

void	second_child(t_pipex *pipex, int pipefd[2], char **envp)
{
	char	*path;
	char	*abs_path;

	path = find_path(envp);
	abs_path = find_abs_path(path, pipex->cmd2[0]);
	if (!abs_path)
	{
		close_program(pipex);
		free(abs_path);
		free(path);
		perror("invalid command 2");
		exit(127);
	}
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	execve(abs_path, pipex->cmd2, envp);
	perror("execve2 failed");
	exit(1);
}

void	exepipe(t_pipex *pipex, char **envp, char **av)
{
	int		pipefd[2];
	int		pid1;
	int		pid2;
	int		status1;
	int		status2;

	if (pipe(pipefd) == -1)
		pipe_failed(pipex);
	pid1 = fork();
	if (pid1 == 0)
		call_first_child(pipex, pipefd, envp, av);
	pid2 = fork();
	if (pid2 == 0)
		call_second_child(pipex, pipefd, envp, av);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	close_program(pipex);
	if (WIFEXITED(status2))
		exit(WEXITSTATUS(status2));
	exit(1);
}

void	call_first_child(t_pipex *pipe, int pipefd[2], char **envp, char **av)
{
	int	infile;

	infile = open(av[1], O_RDONLY);
	if (infile < 0)
	{
		perror(av[1]);
		close_program(pipe);
		exit(1);
	}
	dup2(infile, STDIN_FILENO);
	close (infile);
	first_child(pipe, pipefd, envp);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
	{
		ft_printf("Error\nUsage: ./pipex infile cmd1 cmd2 outfile\n");
		return (1);
	}
	if (!av[2][0] || !av[3][0])
	{
		ft_printf("Error: Empty command\n");
		return (1);
	}
	pipex.cmd1 = assign_arg(av[2]);
	pipex.cmd2 = assign_arg(av[3]);
	exepipe(&pipex, envp, av);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckin-yew <ckin-yew@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:23:33 by ckin-yew          #+#    #+#             */
/*   Updated: 2025/11/15 15:54:12 by ckin-yew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

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

void	call_second_child(t_pipex *pipe, int pipefd[2], char **envp, char **av)
{
	int	outfile;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
	{
		perror(av[4]);
		close_program(pipe);
		exit(1);
	}
	dup2(outfile, STDOUT_FILENO);
	close (outfile);
	second_child(pipe, pipefd, envp);
}

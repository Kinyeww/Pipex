/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckin-yew <ckin-yew@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:51:18 by ckin-yew          #+#    #+#             */
/*   Updated: 2025/11/15 15:55:46 by ckin-yew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>

void	pipe_failed(t_pipex *pipex)
{
	perror("pipe failed");
	close_program(pipex);
	exit(1);
}

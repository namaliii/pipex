/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:18:45 by anamieta          #+#    #+#             */
/*   Updated: 2024/05/03 16:20:18 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	limiter_loop(char *limiter, int *fd_pipe)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			close(fd_pipe[1]);
			exit(EXIT_FAILURE);
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			close(fd_pipe[1]);
			free(line);
			get_next_line(-1);
			exit(EXIT_SUCCESS);
		}
		write(fd_pipe[1], line, ft_strlen(line));
		free(line);
	}
}

static void	exit_status_check(int *fd_pipe, int status)
{
	if (WEXITSTATUS(status) == EXIT_FAILURE)
	{
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		exit(EXIT_FAILURE);
	}
}

void	here_doc(char *limiter, int argc)
{
	pid_t	reader;
	int		fd_pipe[2];
	int		status;

	if (argc < 6)
		args_error();
	if (pipe(fd_pipe) == -1)
		pipe_error(fd_pipe);
	reader = fork();
	if (reader == 0)
	{
		close(fd_pipe[0]);
		limiter_loop(limiter, fd_pipe);
	}
	else
	{
		wait(&status);
		exit_status_check(fd_pipe, status);
		close(fd_pipe[1]);
		dup2(fd_pipe[0], STDIN_FILENO);
		close(fd_pipe[0]);
	}
}

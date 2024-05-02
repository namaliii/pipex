/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:18:45 by anamieta          #+#    #+#             */
/*   Updated: 2024/05/02 20:05:15 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	limiter_loop(char *limiter, char *line, int *fd_pipe)
{
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			exit(EXIT_FAILURE);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			exit(EXIT_SUCCESS);
		write(fd_pipe[1], line, ft_strlen(line));
	}
}

void	here_doc(char *limiter, int argc)
{
	pid_t	reader;
	int		fd_pipe[2];
	char	*line;
	int		status;

	line = NULL;
	if (argc < 6)
		args_error();
	pipe_check(fd_pipe);
	reader = fork();
	if (reader == 0)
	{
		close(fd_pipe[0]);
		limiter_loop(limiter, line, fd_pipe);
	}
	else
	{
		wait(&status);
		if (WEXITSTATUS(status) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		close(fd_pipe[1]);
		dup2(fd_pipe[0], STDIN_FILENO);
		close(fd_pipe[0]);
	}
}

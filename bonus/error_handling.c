/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:14:49 by anamieta          #+#    #+#             */
/*   Updated: 2024/05/02 18:15:26 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	args_error(void)
{
	perror("Wrong number of args");
	exit(1);
}

void	pipe_check(int *fd_pipe)
{
	if (pipe(fd_pipe) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

void	fork_check(pid_t pid)
{
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
}

void	cmd_error(char *cmd, char **arg)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putchar_fd('\n', 2);
	free(cmd);
	free_array(arg);
	exit(127);
}

void	error_handling(char *file)
{
	if (errno == EACCES)
	{
		ft_putstr_fd("pipex: permission denied: ", 2);
		ft_putstr_fd(file, 2);
		ft_putchar_fd('\n', 2);
	}
	else if (errno == ENOENT)
	{
		ft_putstr_fd("pipex: no such file or directory: ", 2);
		ft_putstr_fd(file, 2);
		ft_putchar_fd('\n', 2);
	}
	else
	{
		ft_putstr_fd("pipex: failed to open the file: ", 2);
		ft_putstr_fd(file, 2);
		ft_putchar_fd('\n', 2);
	}
	exit(EXIT_FAILURE);
}

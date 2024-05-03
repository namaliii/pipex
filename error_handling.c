/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:08:58 by anamieta          #+#    #+#             */
/*   Updated: 2024/05/03 19:13:12 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	args_check(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("pipex: wrong number of args\n", 2);
		exit(1);
	}
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

void	error_handling(char *file, int exit_code)
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
	exit(exit_code);
}

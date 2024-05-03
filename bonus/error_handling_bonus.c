/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:14:49 by anamieta          #+#    #+#             */
/*   Updated: 2024/05/03 22:23:54 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	args_error(void)
{
	ft_putstr_fd("pipex: wrong number of args\n", 2);
	exit(1);
}

void	pipe_error(int *fd_pipe)
{
	perror("pipe");
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	exit(1);
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
	if (cmd == NULL)
	{
		ft_putstr_fd("pipex: command not found/n", 2);
		free(cmd);
		free_array(arg);
		exit(127);
	}
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

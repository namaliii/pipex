/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:14:49 by anamieta          #+#    #+#             */
/*   Updated: 2024/05/02 21:09:51 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	args_error(void)
{
	ft_putstr_fd("pipex: wrong number of args\n", 2);
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

void	error_handling(char *file, int exit_code)
{

	ft_putstr_fd("_pipex: _", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);

	// if (errno == EACCES)
	// {
	// 	ft_putstr_fd("pipex: permission denied: ", 2);
	// 	ft_putstr_fd(file, 2);
	// 	ft_putchar_fd('\n', 2);
	// 	strerror(errno);
	// }
	// else if (errno == ENOENT)
	// {
	// 	ft_putstr_fd("pipex: ", 2);
	// 	ft_putstr_fd(file, 2);
	// 	ft_putstr_fd(": No such file or directory\n", 2);
	// }
	// else
	// {
	// 	ft_putstr_fd("pipex: ", 2);
	// 	ft_putstr_fd(file, 2);
	// 	ft_putstr_fd(": Failed to open the file\n", 2);
	// }
	exit(exit_code);
}

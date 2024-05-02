/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:20:27 by anamieta          #+#    #+#             */
/*   Updated: 2024/05/02 18:20:48 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

static void	execute(char *cmd, char **arg, char **envp)
{
	if (execve(cmd, arg, envp) == -1)
	{
		free(cmd);
		free_array(arg);
		perror("pipex");
		exit(1);
	}
}

static void	last_child_status(pid_t pid, bool last_child)
{
	int	status;

	status = 0;
	if (last_child)
		waitpid(pid, &status, 0);
	else
		waitpid(pid, NULL, 0);
}

void	child(char *argv, char **envp, bool last_child)
{
	char	**arg;
	int		fd_pipe[2];
	pid_t	pid;
	char	*cmd;


	// pipe_check(fd_pipe);
	if (pipe(fd_pipe) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	fork_check(pid);
	arg = ft_split(argv, ' ');
	cmd = find_path(envp, arg[0]);
	if (cmd == NULL)
		cmd_error(cmd, arg);
	if (pid == 0)
	{
		close(fd_pipe[0]);
		dup2(fd_pipe[1], STDOUT_FILENO);
		execute(cmd, arg, envp);
	}
	else
	{
		close(fd_pipe[1]);

		dup2(fd_pipe[0], STDIN_FILENO);
		close(fd_pipe[0]);
		last_child_status(pid, last_child);
	}
}
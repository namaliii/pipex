/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:20:27 by anamieta          #+#    #+#             */
/*   Updated: 2024/05/03 18:06:49 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

	if (pipe(fd_pipe) == -1)
		pipe_error(fd_pipe);
	pid = fork();
	fork_check(pid);
	arg = ft_split(argv, ' ');
	cmd = find_path(envp, arg[0]);
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

void	last_child_check(int argc, char **argv, char **envp, int i)
{
	if (i == argc - 3)
		child(argv[i], envp, true);
	else
		child(argv[i], envp, false);
}

static void	helper(int argc, char **argv, char **envp, int *fileout)
{
	int		i;
	int		filein;

	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		i = 3;
		*fileout = open_file(argv[argc - 1], 3);
		here_doc(argv[2], argc);
	}
	else
	{
		i = 2;
		filein = open_file(argv[1], 1);
		dup2(filein, STDIN_FILENO);
		close(filein);
		*fileout = open_file(argv[argc - 1], 2);
	}
	while (i < argc - 2)
	{
		last_child_check(argc, argv, envp, i);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fileout;
	char	*cmd;
	char	**arg;

	arg = NULL;
	if (argc >= 5)
	{
		helper(argc, argv, envp, &fileout);
		arg = ft_split(argv[argc - 2], ' ');
		cmd = find_path(envp, arg[0]);
		cmd_error(cmd, arg);
		dup2(fileout, STDOUT_FILENO);
		close(fileout);
		execute(cmd, arg, envp);
	}
	args_error();
}

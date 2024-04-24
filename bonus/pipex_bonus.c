/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:15:21 by anamieta          #+#    #+#             */
/*   Updated: 2024/04/24 15:37:18 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1(int *fd_pipe, char **argv, char **envp)
{
	char	**arg;
	char	*cmd;
	int		fd1;

	arg = ft_split(argv[2], ' ');
	close(fd_pipe[0]);
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1)
		error_handling(argv[1]);
	dup2(fd1, STDIN_FILENO);
	close(fd1);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[1]);
	cmd = find_path(envp, arg[0]);
	if (cmd == NULL)
		cmd_error(cmd, arg);
	if (execve(cmd, arg, envp) == -1)
	{
		free(cmd);
		free_array(arg);
		perror("pipex");
		exit(1);
	}
}

void	child2(int *fd_pipe, char **argv, char **envp)
{
	char	**arg;
	char	*cmd;
	int		fd2;

	arg = ft_split(argv[3], ' ');
	fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd2 == -1)
		error_handling(argv[4]);
	dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[0]);
	dup2(fd2, STDOUT_FILENO);
	close(fd2);
	cmd = find_path(envp, arg[0]);
	if (cmd == NULL)
		cmd_error(cmd, arg);
	if (execve(cmd, arg, envp) == -1)
	{
		free(cmd);
		free_array(arg);
		perror("pipex");
		exit(1);
	}
}

int	open_file(char *argv, int i)
{
	int file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (i == 1)
		fil
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int 	filein;
	int		fileout;
	int		fd_pipe[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i = 3;
			fileout = open_file
		}
	}
	else
		args_error(argc);

	pipe_check(fd_pipe);
	pid1 = fork();
	fork_check(pid1);
	if (pid1 == 0)
		child1(fd_pipe, argv, envp);
	close(fd_pipe[1]);
	pid2 = fork();
	fork_check(pid2);
	if (pid2 == 0)
		child2(fd_pipe, argv, envp);
	close(fd_pipe[0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	exit(WEXITSTATUS(status));
}

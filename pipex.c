/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:15:21 by anamieta          #+#    #+#             */
/*   Updated: 2024/04/21 14:39:36 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <fcntl.h>

int	path_index(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T'
			&& envp[i][3] == 'H' && envp[i][4] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	**splitting_paths(char **envp)
{
	int		i;
	char	**paths;

	i = path_index(envp);
	paths = ft_split(envp[i] + 5 , ':');
	return (paths);
}

char	*find_path(char **envp, char *argv)
{
	char	**paths;
	char	*cmd;
	char	*aux;
	int		i;

	i = 0;
	paths = splitting_paths(envp);
	while (paths[i])
	{
		cmd = ft_strjoin(paths[i], "/");
		aux = cmd;
		cmd = ft_strjoin(cmd, argv);
		free(aux);
		if (access(cmd, X_OK) == 0)
		{
			write(2, cmd, ft_strlen(cmd));
			write(2, "\n", 1);
			return (cmd);
		}
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	char	**arg2;
	char	**arg3;
	int		fd_pipe[2];
	pid_t	pid;
	pid_t	pid2;
	int		status;
	int		fd1;
	int		fd2;
	int 	i;

	i = 0;
	arg2 = ft_split(argv[2], ' ');
	arg3 = ft_split(argv[3], ' ');
	if (argc != 5)
	{
		printf("Wrong number of args"); // change for ft_printf
		return (1);
	}
	if (pipe(fd_pipe) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		close(fd_pipe[0]);
		fd1 = open(argv[1], O_RDONLY);
		if (fd1 == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd1, STDIN_FILENO);
		close(fd1);
		dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[1]);
		cmd = find_path(envp, argv[2]);
		if (cmd == NULL)
		{
			printf("Command not found %s\n", argv[2]);
			exit(EXIT_FAILURE);
		}
		while (arg2[i])
		{
			execve(cmd, &arg2[i], envp);
			i++;
		}
	}
	close(fd_pipe[1]);
	pid2 = fork();
	if (pid2 == 0)
	{
		fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd2 == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd_pipe[0], STDIN_FILENO);
		close(fd_pipe[0]);
		dup2(fd2, STDOUT_FILENO);
		close(fd2);
		cmd = find_path(envp, argv[3]);
		if (cmd == NULL)
		{
			printf("Command not found %s\n", argv[2]);
			exit(EXIT_FAILURE);
		}
		i = 0;
		while (arg3[i])
		{
			execve(cmd, &arg3[i], envp);
			i++;
		}
	}
	waitpid(pid, NULL, 0);
	waitpid(pid2, &status, 0);
	exit(WEXITSTATUS(status));
}

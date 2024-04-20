/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:15:21 by anamieta          #+#    #+#             */
/*   Updated: 2024/04/20 19:47:13 by anamieta         ###   ########.fr       */
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
	paths = NULL;
	paths = ft_split(envp[i] + 5 , ':');
	return (paths);
}

char	*find_path(char **envp, char **argv)
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
		cmd = ft_strjoin(cmd, argv[2]);
		free(aux);
		if (access(cmd, X_OK) == 0)
			return (cmd);
		free(cmd);
		free(paths[i]);
		paths[i] = NULL;
		i++;
	}
	free(paths);
	paths = NULL;
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	int		fd[2];
	int		id;
	int		f1;
	int		f2;

	if (argc != 5)
	{
		printf("Wrong number of args"); // change for ft_printf
		return (1);
	}
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	id = fork();
	if (id < 0)
	{
		perror("fork");
		return (1);
	}
	if (id == 0)
	{
		printf("BOBER KURWA");
		f1 = open(argv[1], O_RDONLY);
		if (f1 == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(f1, STDOUT_FILENO);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(f1);
		cmd = find_path(envp, argv);
		if (cmd == NULL)
		{
			printf("Command not found %s\n", argv[2]);
			exit(EXIT_FAILURE);
		}
		execve(cmd, &cmd, envp);
	}
	else
	{
		waitpid(id, NULL, 0);
		f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (f2 == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		close(fd[1]);
		dup2(f2, STDOUT_FILENO);
		close(f2);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

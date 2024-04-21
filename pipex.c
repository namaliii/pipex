/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:15:21 by anamieta          #+#    #+#             */
/*   Updated: 2024/04/21 18:22:02 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	if (i == -1)
		return (NULL);
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
		aux = ft_strjoin(paths[i], "/");
		cmd = ft_strjoin(aux, argv);
		free(aux);
		write(2, cmd, ft_strlen(cmd));
		write(2, "\n", 1);
		if (access(cmd, X_OK) == 0)
		{
			return (cmd);
		}
		free(cmd);
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	char	**arg;
	int		fd_pipe[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;
	int		fd1;
	int		fd2;
	int 	i;
	int		j;

	i = 0;
	j = 0;
	cmd = NULL;
	if (argc != 5)
	{
		perror("Wrong number of args");
		return (1);
	}
	if (pipe(fd_pipe) == -1)
		exit(-1);
	pid1 = fork();
	if (pid1 < 0)
		exit(-1);
	if (pid1 == 0)
	{
		arg = ft_split(argv[2], ' ');
		close(fd_pipe[0]);
		fd1 = open(argv[1], O_RDONLY);
		if (fd1 == -1)
			error_handling(argv[1]);
		dup2(fd1, STDIN_FILENO); // duplicating it into stdin
		close(fd1); // so its not necessary anymore
		dup2(fd_pipe[1], STDOUT_FILENO); // writing from pipe into stdout
		close(fd_pipe[1]); //closing pipe write end
		cmd = find_path(envp, arg[0]);
		if (cmd == NULL)
		{
			cmd_error(cmd);
			exit(127);
		}
		execve(cmd, arg, envp);
	}
	close(fd_pipe[1]);
	pid2 = fork();
	if (pid2 < 0)
		exit(1);
	if (pid2 == 0)
	{
		arg = ft_split(argv[3], ' ');
		fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd2 == -1)
			error_handling(argv[4]);
		dup2(fd_pipe[0], STDIN_FILENO);  //the read end of pipe donates its data to file descriptor 0
		close(fd_pipe[0]);
		dup2(fd2, STDOUT_FILENO); //duplicating from the file2 to stdout
		close(fd2);
		cmd = find_path(envp, arg[0]);
		if (cmd == NULL)
		{
			cmd_error(cmd);
			exit(127);
		}
		i = 0;
		execve(cmd, arg, envp);
	}
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	exit(WEXITSTATUS(status));
}

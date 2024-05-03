/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:20:27 by anamieta          #+#    #+#             */
/*   Updated: 2024/05/03 22:15:47 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child(char *argv, char **envp)
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
	}
}

static void	helper(int argc, char **argv, char **envp, int *fileout)
{
	int	i;
	int	filein;

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
		child(argv[i], envp);
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

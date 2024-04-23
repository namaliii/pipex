/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:15:21 by anamieta          #+#    #+#             */
/*   Updated: 2024/04/23 13:31:18 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1(int *fd_pipe, char **argv, char **envp)
{
	char	**arg;
	char	*cmd;
	int		fd1;

	arg = ft_split(argv[2], ' ');
	close(fd_pipe[0]); // closing the read end (we're not gonna read)
	fd1 = open(argv[1], O_RDONLY); // opening file1 in read only
	if (fd1 == -1)
		error_handling(argv[1]);
	dup2(fd1, STDIN_FILENO); // duplicating file1 fd into STDIN fd, so now the STDIN contains the file1 content
	close(fd1);
	dup2(fd_pipe[1], STDOUT_FILENO); // duplicating write end of the pipe into the STDIN fd
	close(fd_pipe[1]);
	cmd = find_path(envp, arg[0]);
	if (cmd == NULL)
		cmd_error(cmd, arg);
	if (execve(cmd, arg, envp) == -1) // executing command 1 using the content of file1 (is needs input)
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
	fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644); // file2 if doesn't exist - create,
	// the file should be for reading and writing (why not only for writing? :),
	// O_TRUNC - if not empty, make it 0 (erase), 0644 owner: read&write, others(group and others): read
	if (fd2 == -1)
		error_handling(argv[4]);
	dup2(fd_pipe[0], STDIN_FILENO); // duplicating from the read end of the pipe into STDIN
	close(fd_pipe[0]);
	dup2(fd2, STDOUT_FILENO); // duplicating from file2 into the STDOUT
	close(fd2);
	cmd = find_path(envp, arg[0]);
	if (cmd == NULL)
		cmd_error(cmd, arg);
	if (execve(cmd, arg, envp) == -1) // executing command 2 using the content of the pipe read
	//(that contains the output of command one executed on file1)
	{
		free(cmd);
		free_array(arg);
		perror("pipex");
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fd_pipe[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	args_check(argc);
	pipe_check(fd_pipe);
	pid1 = fork();
	fork_check(pid1);
	if (pid1 == 0)
		child1(fd_pipe, argv, envp);
	close(fd_pipe[1]); // closing the write end
	pid2 = fork();
	fork_check(pid2);
	if (pid2 == 0)
		child2(fd_pipe, argv, envp);
	waitpid(pid1, NULL, 0); // why not collecting the status here also?
	waitpid(pid2, &status, 0); //waits for the pid2 to terminate and collects its exit status
	exit(WEXITSTATUS(status)); //exits with the exit status from pid2
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:15:21 by anamieta          #+#    #+#             */
/*   Updated: 2024/04/17 21:00:16 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	fd[2];
	int	id;

	if (pipe(fd) == -1)
		return (1);// error
	id = fork();
	if (id < 0)
		error
	its the same
	if (id == -1)
		return (2);

	if read or write == -1
		return error
	if (id == 0) // then its a child process
	{
		dup2(fd[1], STDOUT_FILENO)
		sth with STDIN for the parent proces
		close(fd[0]);
		close(fd[1]);
		execve
	}
	else // parent process
	waitpid(id, NULL, 0);
}

seach for the PATH in the executable
search in each directory the command given
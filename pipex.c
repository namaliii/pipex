/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:15:21 by anamieta          #+#    #+#             */
/*   Updated: 2024/04/20 18:09:43 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

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
	int i;
	char **paths;

	i = path_index(envp);
	paths = NULL;
	paths = ft_split(envp[i] + 5 , ':');
	return (paths);
}

int	execute_command(char **envp, char **argv)
{
	char	**paths;
	int	i;

	paths = splitting_paths(envp);
	while (paths[i])
	{
		char *cmd = ft_strjoin(paths[i], "/");
		char *aux = cmd;
		cmd = ft_strjoin(cmd, argv[1]);
		free(aux);
		if (access(cmd, X_OK) == 0)
		{
			printf("cmd = %s\n", cmd);
			execve(cmd, &cmd, envp);
		}
		free(cmd);
		i++;
	}
	return (-1);
}

int	main(int argc, char **argv, char **envp)
{
	int exec;

	exec = execute_command(envp, argv);
	printf("exec: %d\n", exec);
	// printf("i: %d", i);
	// char *args[3]; // Increase the array size to hold additional arguments
	// args[0] = "/usr/bin/wc"; // Full path to the "ls" executable
	// args[1] = "-l"; // Specify the "-l" option to list files in long format
	// args[2] = NULL; // Terminate the array with NULL
	// //args = {"/usr/bin/wc", "-l" , NULL};
	// execve(args[0], args, NULL);
	// int	fd[2];
	// int	id;
	// int x;
	// int y;

// 	if (pipe(fd) == -1)
// 		return (1);// error
// 	id = fork();
// 	// if (id < 0)
// 	// 	error
// 	if (id == 0) // then its a child process
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[1]);
// 		// sth with STDIN for the parent proces
// 		// if (write(fd[1], &x, sizeof(int)) == -1);
// 		// 	return (1); //error
// 		char *args[3]; // Increase the array size to hold additional arguments
// 		args[0] = "/bin/ls"; // Full path to the "ls" executable
// 		args[1] = "-l"; // Specify the "-l" option to list files in long format
// 		args[2] = NULL; // Terminate the array with NULL
// 		if (execve(args[0], args, NULL) == -1)
// 		{
// 			exit(1);
// 		}
// 	}
// 	else // parent process
// 	{
// 		close(fd[1]);
// 		waitpid(id, NULL, 0); // in parent process?
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		char *args[3]; // Increase the array size to hold additional arguments
// 		args[0] = "/usr/bin/wc"; // Full path to the "ls" executable
// 		args[1] = "-l"; // Specify the "-l" option to list files in long format
// 		args[2] = NULL; // Terminate the array with NULL
// 		execve(args[0], args, NULL);
// 	}
// 		printf("hello from parent \n");
}

// seach for the PATH in the executable
// search in each directory the command given
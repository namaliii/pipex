/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:03:25 by anamieta          #+#    #+#             */
/*   Updated: 2024/05/03 21:49:13 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute(char *cmd, char **arg, char **envp)
{
	if (execve(cmd, arg, envp) == -1)
	{
		free(cmd);
		free_array(arg);
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd("command not found", 2);
		ft_putchar_fd('\n', 2);
		exit(1);
	}
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	open_file(char *argv, int filetype)
{
	int	file;

	file = 0;
	if (filetype == 1)
		file = open(argv, O_RDONLY);
	else if (filetype == 2)
		file = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (filetype == 3)
		file = open(argv, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (file == -1)
		error_handling(argv, 0);
	return (file);
}

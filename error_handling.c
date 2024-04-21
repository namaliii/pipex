/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:08:58 by anamieta          #+#    #+#             */
/*   Updated: 2024/04/21 19:06:07 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_error(char *cmd)
{
	ft_putstr("zsh: command not found: ");
	ft_putstr(cmd);
	ft_putchar('\n');
}

void	error_handling(char *file)
{
	if (errno == EACCES)
	{
		ft_putstr("Permission denied for file: ");
		ft_putstr(file);
		ft_putchar('\n');
	}
	else if (errno == ENOENT)
	{
		ft_putstr("zsh: no such file or directory: ");
		ft_putstr(file);
		ft_putchar('\n');
	}
	else
	{
		ft_putstr("Failed to open the file: ");
		ft_putstr(file);
		ft_putchar('\n');
	}
	exit(EXIT_FAILURE);
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

// echo $?
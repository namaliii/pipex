/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:19:50 by anamieta          #+#    #+#             */
/*   Updated: 2024/05/03 21:48:42 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

char	*find_path(char **envp, char *argv)
{
	char	**paths;
	char	*cmd;
	char	*aux;
	int		i;

	if (access(argv, X_OK) == 0)
	{
		cmd = argv;
		return (cmd);
	}
	i = 0;
	paths = splitting_paths(envp);
	while (paths[i])
	{
		aux = ft_strjoin(paths[i], "/");
		cmd = ft_strjoin(aux, argv);
		free(aux);
		if (access(cmd, X_OK) == 0)
			return (free_array(paths), cmd);
		free(cmd);
		i++;
	}
	return (free_array(paths), NULL);
}

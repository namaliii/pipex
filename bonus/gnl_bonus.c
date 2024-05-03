/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:17:28 by anamieta          #+#    #+#             */
/*   Updated: 2024/05/03 14:55:10 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*read_and_concatenate(int *bytes_read, int fd, char *line)
{
	char	*buffer;
	char	*concatenated;

	if (!line)
		line = ft_calloc(1, sizeof(char));
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while (*bytes_read > 0)
	{
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*bytes_read == -1)
			return (free(buffer), NULL);
		buffer[*bytes_read] = '\0';
		concatenated = ft_strjoin(line, buffer);
		free (line);
		line = concatenated;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free (buffer);
	return (line);
}

static int	get_line_len(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i])
		i++;
	return (i);
}

static char	*get_result(char *line, int bytes_read)
{
	char	*result;
	int		i;

	i = 0;
	if (!line[i])
		return (NULL);
	result = ft_calloc(bytes_read + 2, sizeof(char));
	if (!result)
		return (NULL);
	while (line[i] != '\n' && line[i])
	{
		result[i] = line[i];
		i++;
	}
	if (line[i] == '\n' && line[i])
		result[i] = '\n';
	return (result);
}

static char	*allocate_new_line(char *line, int bytes_read)
{
	char	*new_line;
	int		i;

	i = 0;
	if (!line[bytes_read])
	{
		free(line);
		return (NULL);
	}
	new_line = ft_calloc((ft_strlen(line) - bytes_read + 1), sizeof(char));
	if (!new_line)
		return (NULL);
	bytes_read++;
	while (line[bytes_read])
	{
		new_line[i] = line[bytes_read];
		i++;
		bytes_read++;
	}
	free (line);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*result;
	int			bytes_read;

	bytes_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	line = read_and_concatenate(&bytes_read, fd, line);
	if (!line)
		return (NULL);
	bytes_read = get_line_len(line);
	result = get_result(line, bytes_read);
	if (!result)
		return (NULL);
	line = allocate_new_line(line, bytes_read);
	if (!line)
		return (NULL);
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:29:10 by anamieta          #+#    #+#             */
/*   Updated: 2024/05/02 18:29:19 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		error_handling(argv);
	return (file);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if (i == n)
		i--;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0' && *s == '\0')
	{
		return ((char *)s);
	}
	return (NULL);
}

static void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)b;
	while (i < len)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	totalsize;
	void	*ptr;

	totalsize = count * size;
	ptr = malloc(totalsize);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, totalsize);
	return (ptr);
}

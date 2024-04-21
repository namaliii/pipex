/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:51:01 by anamieta          #+#    #+#             */
/*   Updated: 2024/04/20 20:39:42 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(const char *str)
{
	int	length;

	length = 0;
	while (str[length] != '\0')
		length++;
	return (length);
}

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (n == 0)
// 		return (0);
// 	while (i < n && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
// 		i++;
// 	if (i == n)
// 		i--;
// 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }
// void	ft_strcpy(char )
// {

// }

// unsigned int	ft_strlcpy(char *dst, const char *src, size_t dstsize)
// {
// 	unsigned int	i;

// 	i = 0;
// 	while (dstsize > 0 && i < dstsize - 1 && src[i] != '\0')
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	if (dstsize > 0)
// 		dst[i] = '\0';
// 	while (src[i] != '\0')
// 		i++;
// 	return (i);
// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*constr;
	size_t	lens1;
	size_t	lens2;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	constr = (char *)calloc((lens1 + lens2 + 1), sizeof(char));
	if (constr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		constr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		constr[i] = s2[j];
		i++;
		j++;
	}
	return (constr);
}

// ft_putstr
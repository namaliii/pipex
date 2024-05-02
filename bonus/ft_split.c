/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:16:12 by anamieta          #+#    #+#             */
/*   Updated: 2024/05/02 18:17:12 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	word_count(char const *s, char delimiter)
{
	int	word_count;
	int	i;

	i = 0;
	word_count = 0;
	while (s[i] != 0)
	{
		if (s[i] != delimiter && (s[i + 1] == 0 || s[i + 1] == delimiter))
			word_count++;
		i++;
	}
	return (word_count);
}

static char	*extract_word(char *s, char delimiter)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] != 0 && s[i] != delimiter)
		i++;
	word = (char *)ft_calloc(i + 1, sizeof(char));
	if (word == 0)
		return (0);
	i = 0;
	while (s[i] != 0 && s[i] != delimiter)
	{
		word[i] = s[i];
		i++;
	}
	return (word);
}

void	cleanup(char **word_array, int word_index)
{
	while (word_index >= 0)
	{
		free(word_array[word_index]);
		word_array[word_index] = 0;
		word_index--;
	}
	free(word_array);
	word_array = 0;
}

int	parse_words(char **words, char *s, char delimiter, int word_index)
{
	while (*s != 0 && *s == delimiter)
		s++;
	while (*s != 0)
	{
		words[word_index] = extract_word(s, (unsigned char)delimiter);
		if (words[word_index] == 0)
		{
			cleanup(words, word_index);
			return (0);
		}
		word_index++;
		while (*s != 0 && *s != delimiter)
			s++;
		while (*s != 0 && *s == delimiter)
			s++;
	}
	return (word_index);
}

char	**ft_split(char const *s, char c)
{
	int		counter;
	char	**words;
	int		word_index;

	if (s == 0)
		return (0);
	word_index = 0;
	counter = word_count(s, c);
	words = (char **)ft_calloc(counter + 1, sizeof(char *));
	if (words == 0)
		return (0);
	if (counter > 0)
	{
		word_index = parse_words(words, (char *)s, c, word_index);
		if (word_index == 0)
			return (0);
	}
	return (words);
}

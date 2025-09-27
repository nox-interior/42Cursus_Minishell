/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:13:57 by amarroyo          #+#    #+#             */
/*   Updated: 2024/05/08 13:59:45 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static void	ft_free(size_t i, char **str)
{
	while (i > 0)
	{
		i--;
		free(*(str + i));
	}
	free(str);
}

static size_t	ft_substr_count(char const *s, char c)
{
	size_t	i;
	size_t	substr_nbr;

	i = 0;
	substr_nbr = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			substr_nbr++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (substr_nbr);
}

static char	*ft_extract_substr(char const *s, char c, size_t *start)
{
	size_t	end;
	char	*word;

	while (s[*start] && s[*start] == c)
		(*start)++;
	end = *start;
	while (s[end] && s[end] != c)
		end++;
	word = ft_substr(s, *start, end - *start);
	if (!word)
		return (NULL);
	*start = end;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	i;
	size_t	words;
	size_t	start;

	i = 0;
	start = 0;
	if (!s)
		return (NULL);
	words = ft_substr_count(s, c);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	while (i < words)
	{
		array[i] = ft_extract_substr(s, c, &start);
		if (!array[i])
		{
			ft_free(i, array);
			return (NULL);
		}
		i++;
	}
	array[i] = NULL;
	return (array);
}

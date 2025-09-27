/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:58:37 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/10 13:02:57 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"
#include "../../inc/libft.h"

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substring;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substring = (char *)malloc(len + 1);
	if (!substring)
		return (NULL);
	while (i < len)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*result_string;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	result_string = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!s2 || !result_string)
		return (NULL);
	if (s1)
	{
		while (s1[i] != '\0')
		{
			result_string[i] = s1[i];
			i ++;
		}
	}
	while (s2[j] != '\0')
	{
		result_string[i + j] = s2[j];
		j ++;
	}
	result_string[i + j] = '\0';
	return (result_string);
}

char	*ft_join_and_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin_gnl(s1, s2);
	free(s1);
	s1 = NULL;
	return (result);
}

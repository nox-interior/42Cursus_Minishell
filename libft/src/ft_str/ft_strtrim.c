/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:21:53 by amarroyo          #+#    #+#             */
/*   Updated: 2024/05/08 14:00:41 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

// Deletes all the characters from 'set', from the beginning and
// from the end of 's1' (to be trimmed), until it finds a character that 
// is not included in 'set'.
// Return: the new trimmed string , allocated with malloc.
// Return: NULL if memory allocation fails. 

static void
	ft_rm_char(const char *s1, const char *set, size_t *start, size_t *end)
{
	size_t	start_i;
	size_t	end_i;

	start_i = *start;
	end_i = *end;
	while (s1[start_i] != '\0' && (ft_strchr(set, s1[start_i])
			|| ft_strrchr(set, s1[end_i - 1])))
	{
		if (ft_strchr(set, s1[start_i]))
			start_i++;
		if (ft_strrchr(set, s1[end_i - 1]))
			end_i--;
	}
	*start = start_i;
	*end = end_i;
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	size_t	len_trim;
	char	*str_trim;

	str_trim = NULL;
	if (s1 != NULL && set != NULL)
	{
		start = 0;
		end = ft_strlen(s1);
		ft_rm_char(s1, set, &start, &end);
		if (end > start)
			len_trim = end - start;
		else
			len_trim = 0;
		str_trim = (char *)malloc(len_trim + 1);
		if (str_trim != NULL)
			ft_strlcpy(str_trim, &s1[start], len_trim + 1);
	}
	return (str_trim);
}

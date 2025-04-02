/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:52:08 by amarroyo          #+#    #+#             */
/*   Updated: 2024/05/08 14:00:45 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

// Allocates memory with malloc and returns a substring of the string s
// The substring starts from the index 'start' and
// has length max 'len'
// Return: the resulting substring
// Return: NULL if memory allocation fails

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	substr_length;

	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	substr_length = ft_strlen(s + start);
	if (substr_length < len)
		len = substr_length;
	substring = (char *)malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (NULL);
	ft_strlcpy(substring, (s + start), (len + 1));
	return (substring);
}

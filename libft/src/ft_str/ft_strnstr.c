/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:22:17 by amarroyo          #+#    #+#             */
/*   Updated: 2024/05/08 14:00:30 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

// Locate substring, where not more than 'len' characters are searched.
// Find the first occurrence of the substring 'needle' in the string 'haystack'
// Return: a pointer to the first occurrence of the needle in the haystack
// Return: NULL if the needle is not found within the first len characters.
// If needle is an empty string, haystack is returned.

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == needle[0])
		{
			j = 1;
			while (needle[j] != '\0' && haystack[i + j] == needle[j]
				&& (i + j) < len)
				++j;
			if (needle[j] == '\0')
				return ((char *)&haystack[i]);
		}
		++i;
	}
	return (NULL);
}

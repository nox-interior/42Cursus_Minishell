/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:31:21 by amarroyo          #+#    #+#             */
/*   Updated: 2024/05/08 14:00:08 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

// Concatenates two strings with a specified maximum size.
// Return: the total length of the string they tried to create.
// concatenate the src string to the end of the dest buffer,
// while ensuring that the resulting string is null-terminated
// and does not exceed the size of the dest buffer.

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dest_len;

	dest_len = 0;
	while (dest[dest_len] != '\0' && dest_len < dstsize)
	{
		dest_len++;
	}
	i = dest_len;
	while (src[dest_len - i] != '\0' && dest_len + 1 < dstsize)
	{
		dest[dest_len] = src[dest_len - i];
		dest_len++;
	}
	if (i < dstsize)
		dest[dest_len] = '\0';
	return (i + ft_strlen(src));
}

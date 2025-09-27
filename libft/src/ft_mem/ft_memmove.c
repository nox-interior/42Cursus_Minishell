/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 10:29:54 by amarroyo          #+#    #+#             */
/*   Updated: 2024/05/08 13:59:10 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

// copies len bytes from string src to string dst.
// The two strings may overlap; the copy is always done in a 
// non-destructive manner.
// Return: the original value of dst.
// Deals with memcpy problems when source and destination addresses overlap
// so, it is used when memory blocks overlap.

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;
	size_t			i;

	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	if (dest < source)
	{
		i = 0;
		while (i < len)
		{
			dest[i] = source[i];
			i++;
		}
	}
	else
	{
		i = len;
		while (i--)
			dest[i] = source[i];
	}
	return (dst);
}
